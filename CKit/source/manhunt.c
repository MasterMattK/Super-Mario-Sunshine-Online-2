// This file is responsible for all of the functions that deal with the manhunt gamemode
#include "defines.h"

bool isHunter = false, manhuntActive = false, manhuntReset = false, sendDamageSound = false, receiveDamageSound = false, isTalking = false;
unsigned int cooldown = 0, cooldownStarted = 0;

// function prototypes (the first 2 are for in-game funcs)
int checkDistance(float* xyz1, float* xyz2, float one, float two, float three, float four);
void floorDamageExec(int *mario, int damage, int type, int emitcount, int tremble);

// this function branches to all of the manhunt functions that need to run every frame
void manhuntMain() {
	//printNumber(currentTime - cooldownStarted);
	manhunt_checkIfReset();
	refreshCooldownIfLoading();
	refreshCooldownIfCutscene();
	manhunt_checkIfTagged();
	checkHunterFlags();
	manhunt_checkGoAppear();
	checkIfReceiveDamageSound();
}

// this function checks if a reset has been requested by the GUI
void manhunt_checkIfReset() {
	if (manhuntReset) {
		manhuntActive = false;
		manhuntReset = false;
	}
}

// this function is what kills your mario when he is tagged
void manhunt_checkIfTagged() {
	if (gamemode != 2 || !manhuntActive)
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
			if (checkDistance(mario_pos, realMario_pos, 120, 90, 82, 170) == 1 && realMario[0x7C / 4] != 0x20467 && !isInCooldown()) {
				floorDamageExec(realMario, 2, 3, 0, 0xf);
				sendDamageSound = true;
				setCooldown(2);
			}
		}
	}
}

void checkHunterFlags() {
	if (gamemode != 2)
		return;

	u8* mario = SDAword(-0x60D8);
	u8 shirtFlag = mario[0x119];
	u8* marioCap = ((u32*)mario)[0x3E0 / 4]; // mariocap is used for sunglasses
	if (isHunter && !(shirtFlag & 16)) {
		shirtFlag += 0x10;
		mario[0x119] = shirtFlag;
		marioCap[0x5] = 5;
	}
	else if (!isHunter && shirtFlag & 16) {
		shirtFlag -= 0x10;
		mario[0x119] = shirtFlag;
		marioCap[0x5] = 1;
	}
}

// refreshes the manhunt cooldown from loading into a stage if the runner is in the "particle load-in" state(0x1337) in order to avoid shorter effective cooldowns
void refreshCooldownIfLoading() {
	int *mario = SDAword(-0x60D8);
	if (mario[0x7C / 4] == 0x00001337) {
		setCooldown(2);
	}
}

// refreshes manhunt cooldown if hunter is in a cutscene(not fmv)
void refreshCooldownIfCutscene() {
	u16 *TMarDirector = SDAword(-0x6048);
	if (cutsceneCooldownPending) {
		setCooldown(1);		// 5 is for debug, change to 1
		cutsceneCooldownPending = false;
	} else if (TMarDirector[0x4C / 2] & 0x0040) {
		setCooldown(1);		// 5 is for debug, change to 1
	}
}

void checkIfTalking() {
	isTalking = true;
}

void setCooldown(int time) {
	cooldown = time;
	cooldownStarted = currentTime;
}

int isInCooldown() {
	if (isTalking) {		// temp solution
		isTalking = false;
		return true;
	}

	if (currentTime - cooldown >= cooldownStarted) {
		return false;
	}
	else
		return true;
}

void manhunt_onStageLoad() {
	setCooldown(2);
}

void manhunt_checkGoAppear() {
	static bool previousManhuntActive = false;
	static bool playStartSoundPending = false;

	if (previousManhuntActive == false && manhuntActive == true) {
		u32 **marDirector = SDAword(-0x6048);
		u32 *GCConsole2 = marDirector[0x74 / 4];
		u32 ConsoleStr = GCConsole2[0x94 / 4];
		startAppearGo(ConsoleStr);
		playStartSoundPending = true;
	}

	if (playStartSoundPending && playVoice(0x4851))
		playStartSoundPending = false;

	previousManhuntActive = manhuntActive;
}

// if the gui sets receiveDamageSound to true, play the damage sound and set it back to false
void checkIfReceiveDamageSound() {
	static bool playedFirstSound = false;

	if (!playedFirstSound && (receiveDamageSound && playVoice(0x7819))) {		// mario 64 oof sound
		playedFirstSound = true;
	}
	else if (playedFirstSound && (receiveDamageSound && playSound(0x292E))) {	// damage sound
		receiveDamageSound = false;
		playedFirstSound = false;
	}
}