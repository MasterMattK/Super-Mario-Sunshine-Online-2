// This file is responsible for all of the functions that deal with the tag gamemode
#include "defines.h"

int gamemode = 0;
int clientTagTime = 0;
int savedFlags = 0;
bool isTagger = false, isTimerOnscreen = false, connected = false, previouslyConnected = false, tagBool = false, fluddRefills = false, tagReset = false;

// function prototypes (the first 2 are for in-game funcs)
int checkDistance(float* xyz1, float* xyz2, float one, float two, float three, float four);
u64 OSCheckStopwatch(u32);
bool isTimerRunning();

// this function branches to all of the tag functions that need to run every frame
void tagMain() {
	checkIfReset();
	checkIfTagged();
	checkStartTimer();
	checkStopTimer();
	checkChangeTimer();
	checkTaggerFlags();
}

// this function checks if a reset has been requested by the GUI
void checkIfReset() {
	if (tagReset) {
		tagBool = false;

		if (isTimerRunning())
			stopTimer();

		clientTagTime = 0;
		insertTimer();

		tagReset = false;
	}
}

// this function is what kills your mario when he is tagged
void checkIfTagged() {
	if (gamemode != 1 || !tagBool)
		return;

	u32* currentMario = fromRegister(30);
	u32* realMario = SDAword(-0x60D8);

	// if the current mario is a dummy mario, we continue
	if (currentMario != realMario) {
		u8* mario_u8 = currentMario;
		u8* realMario_u8 = realMario;

        // tagger marios will have the shine shirt flag (0x119), so we check to see that the dummy
        // mario is a tagger, and that your mario isn't
		if ((mario_u8[0x119] << 3) >= 128 && (realMario_u8[0x119] << 3) < 128) {
			float* mario_pos = currentMario + 4;
			float* realMario_pos = realMario + 4;

            // checkDistance is an in-game function that sees if 2 hitboxes are colliding. I send in the positions
            // of the marios, as well as the dimensions of the hitboxes (radius and height) to see if they are colliding.
            // I also make sure that your mario isn't already in the dying state before continuing
			if (checkDistance(mario_pos, realMario_pos, 120, 90, 82, 170) == 1 && realMario[0x7C / 4] != 0x20467) {
				loserExec(realMario);   // this is the kill function
			}
		}
	}
}

// this function starts the timer for the tag gamemode
void checkStartTimer() {
	if (gamemode != 1)
	{
		if (isTimerOnscreen)
			removeTimer();
			
		return;
	}

    // if the gamemode is activated (tagBool) and the timer isn't running and your mario isn't a tagger, start the timer
	if (tagBool && !isTagger && !isTimerRunning()) {
		startTimer();
	}
    // if tagBool isn't 1 but tag is still the gamemode, we put the timer on screen without starting it
	else if (!isTimerOnscreen) {
		insertTimer();
	}
}

void checkStopTimer() {
	if (gamemode != 1) return;

	u8* marDirectorU8 = SDAword(-0x6048);
	u8 gameState = marDirectorU8[0x64];

	u8 stage = marDirectorU8[0x7C];
	if (stage == 0xF) return;       // returns if on title screen

	u32* marDirector = SDAword(-0x6048);
	if (tagBool) {
		if (!isTagger) {

            // if your mario is dead (7) or the stage is changing (9), stop the timer and store the current time
			if (gameState == 7 || gameState == 9) {
				stopTimer();
				u32* TGCConsole2 = marDirector[0x74 / 0x4];
				clientTagTime = TGCConsole2[0x500 / 0x4];
			}

            // if the client has gotten disconnected, stop the timer and store the current time
			if (!connected && previouslyConnected) {
				stopTimer();
				u32* TGCConsole2 = marDirector[0x74 / 0x4];
				clientTagTime = TGCConsole2[0x500 / 0x4];
			}
		}
	}
	else {

        // if the timer is still running after tagBool is 0, stop the timer and store the current time
		if (isTimerRunning()) {
			stopTimer();
			u32* TGCConsole2 = marDirector[0x74 / 0x4];
			clientTagTime = TGCConsole2[0x500 / 0x4];
		}
	}
	previouslyConnected = connected;
}

void checkChangeTimer() {
	if (gamemode != 1) return;

	u32* mario = SDAword(-0x60D8);
	u16* gamepad = mario[0x4FC / 4];
	u16 buttons = gamepad[0x1A / 2];
	u32* marDirector = SDAword(-0x6048);
	u32* TGCConsole2 = marDirector[0x74 / 0x4];
	s32 timer = TGCConsole2[0x500 / 0x4];

	// if L and D-pad Up are hit, increase the timer
	if (buttons == 0x48) {
		clientTagTime += 0x5;

		// if the timer is frozen, we have to call setTimer for it to visually update
		if (!isTimerRunning()) {
			setTimer(TGCConsole2, clientTagTime);
		}
	}
	// if L and D-pad Down are hit, decrease the timer
	else if (buttons == 0x44) {
		if ((timer - 0x5) > 0)
			clientTagTime -= 0x5;
		else
			clientTagTime = 0;

		if (!isTimerRunning()) {
			setTimer(TGCConsole2, clientTagTime);
		}
	}
}

void checkTaggerFlags() {
	u8* mario = SDAword(-0x60D8);
	u8 shirtFlag = mario[0x119];
	u8* marioCap = ((u32*)mario)[0x3E0 / 4];
	if (isTagger && !(shirtFlag & 16)) {
		shirtFlag += 0x10;
		mario[0x119] = shirtFlag;
		marioCap[0x5] = 5;
	}
	else if (!isTagger && shirtFlag & 16) {
		shirtFlag -= 0x10;
		mario[0x119] = shirtFlag;
		marioCap[0x5] = 1;
	}
}

void startTimer() {
	insertTimer();
	u32* TMarDirector = SDAword(-0x6048);
	u64 stopWatch = OSCheckStopwatch(TMarDirector + 232 / 4);
	u32 stopWatch1 = (u32)(stopWatch >> 32);
	u32 stopWatch2 = (u32)(stopWatch & 0xffffffff);
	TMarDirector[0xC8 / 4] = stopWatch1;
	TMarDirector[0xCC / 4] = stopWatch2;
	startMoveTimer(TMarDirector[0x74 / 4], 1);
}

// inserts a stopped timer onto screen
void insertTimer() {
	isTimerOnscreen = true;
	u32* TMarDirector = SDAword(-0x6048);
	u32 TGCConsole2 = TMarDirector[0x74 / 4];
	startAppearTimer(TGCConsole2, 0, 1);
}

void removeTimer() {
	isTimerOnscreen = false;
	u32* TMarDirector = SDAword(-0x6048);
	u32 TGCConsole2 = TMarDirector[0x74 / 4];
	startDisappearTimer(TGCConsole2);
}

void stopTimer() {
	u32* TMarDirector = SDAword(-0x6048);
	stopMoveTimer(TMarDirector[0x74 / 4]);
}

bool isTimerRunning() {
	u32* marDirector = SDAword(-0x6048);
	u8* TGCConsole2 = marDirector[0x74 / 0x4];
	u8 timerState = TGCConsole2[0x4A];
	if (timerState == 1) return true;
	else return false;
}

// when a stage changes, we need to make sure this variable is set to 0
void onChangeStage() {
	isTimerOnscreen = false;
}

// this function sends clientTagTime into the setTimer function if gamemode is 1
void setTimerSetup(u32* TGCConsole2, u32 r4) {
	if (gamemode == 1) {
		setTimer(TGCConsole2, clientTagTime);
	} else {
        setTimer(TGCConsole2, r4);
    }
}

// add the clientTagTime onto the timer visually, and restore the vanilla code
void addPreviousTime(u32 incomingTime) {
	u32 newTime = incomingTime + clientTagTime;
	toRegister(30, newTime);
}

// if tag is the gamemode, this function makes it so you respawn in the current stage rather than delfino plaza
void tagRespawnStage() {
	if (gamemode == 1) {
		__asm("lis 14, 0x803E");
		__asm("ori 14, 14, 0x970E");
		__asm("lbz 0, 0x0 (14)");
	}
	else {
		__asm("li 0, 1");
	}
}

// same as tagRespawnStage, except for the current episode
void tagRespawnEpisode() {
	if (gamemode == 1) {
		__asm("lis 3, 0x803E");
		__asm("ori 3, 3, 0x970F");
		__asm("lbz 3, 0x0 (3)");
	}
	else {
		__asm("li 3, 255");
	}
}

// same as the 2 functions above, except this is for when mario dies in a secret. It respawns mario in the previous
// stage rather than the secret stage (for example, a death in bianco secret respawns in bianco)
void tagRespawnStageSecret() {
	if (gamemode == 1) {
		__asm("lis 14, 0x803E");
		__asm("ori 14, 14, 0x970A");
		__asm("lbz 0, 0x0 (14)");
	}
	else {
		__asm("lbz 0, 0 (28)");
	}
}

// same as tagRespawnStageSecret except for the episode
void tagRespawnEpisodeSecret(u8* nextStage) {
	if (gamemode == 1) {
		u8* TApplication = 0x803E9700;
		nextStage[1] = TApplication[0xB];
	}
	else {
		__asm("stb 0, 0x0001 (3)");
	}
}

// if tag is the gamemode, mario deaths don't decrease the 1up count
void freezeLives() {
	if (gamemode != 1) {
		__asm("stw 0, 0x0078 (3)");
	}
}

void checkForTagger(u32* mario) {
	if (fluddRefills && !isTagger && tagBool) {
		int currentFlags = mario[0x118 / 4];
		int maskedFlags = currentFlags & 0x00030000;
		if (maskedFlags != 0) {
			savedFlags = currentFlags;
			fromRegister(3)[0x118 / 4] = currentFlags - maskedFlags;
		}
	}
	gunExec(mario);
}

void checkForTagger_Restore() {
	if (savedFlags != 0) {
		fromRegister(30)[0x118 / 4] = savedFlags;
		savedFlags = 0;
	}
}

void stopRefill29() {
	if (fluddRefills && !isTagger && tagBool) return;
	else __asm("stw 0, 0x1C80 (29)");
}

void stopRefill30() {
	if (fluddRefills && !isTagger && tagBool) return;
	else __asm("stw 0, 0x1C80 (30)");
}

void stopRefill31() {
	if (fluddRefills && !isTagger && tagBool) return;
	else __asm("stw 0, 0x1C80 (31)");
}