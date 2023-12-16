// This file is responsible for all of the functions that deal with the manhunt gamemode
#include "defines.h"

bool isHunter = false, manhuntBool = false, manhuntReset = false;
unsigned int cooldown = 0, cooldownStarted = 0;

// function prototypes (the first 2 are for in-game funcs)
int checkDistance(float* xyz1, float* xyz2, float one, float two, float three, float four);
void floorDamageExec(int *mario, int damage, int type, int emitcount, int tremble);

// this function branches to all of the manhunt functions that need to run every frame
void manhuntMain() {
	manhunt_checkIfReset();
	manhunt_checkIfTagged();
	checkHunterFlags();
}

// this function checks if a reset has been requested by the GUI
void manhunt_checkIfReset() {
	if (manhuntReset) {
		manhuntBool = false;
		manhuntReset = false;
	}
}

// this function is what kills your mario when he is tagged
void manhunt_checkIfTagged() {
	if (gamemode != 2 || !manhuntBool)
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

void setCooldown(int time) {
	cooldown = time;
	cooldownStarted = currentTime;
}

int isInCooldown() {
	if (currentTime - cooldown >= cooldownStarted) {
		return false;
	}
	else
		return true;
}

void manhunt_onStageLoad() {
	setCooldown(3);
}