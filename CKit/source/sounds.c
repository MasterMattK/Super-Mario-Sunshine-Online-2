// This file is responsible for any functions that alter the sound system in-game
#include "defines.h"

//						   singJump    doubJump    tripJump    groundPnd   dive        rollOut     wallJump    bounceJump  sideFlip    backFlip    rocketJump  turboJump
u32 soundStateList[12] = { 0x02000880, 0x02000881, 0x00000882, 0x008008A9, 0x0080088A, 0x02000889, 0x02000886, 0x000008A4, 0x00000887, 0x00000883, 0x0000088D, 0x00000888 };
u32 soundIdList[12] = 	 { 0x000078ab, 0x000078b1, 0x000078b6, 0x0000788f, 0x00007884, 0x000078b1, 0x000078b1, 0x000078b6, 0x000078b6, 0x000078b6, 0x000078b9, 0x000078b1 };
u32* playSoundBools[realpNum] = { [0 ... (realpNum-1)] = 1 };
u32* previousState[realpNum] = { [0 ... (realpNum-1)] = -3 };

// this function fixes the problem of some sounds not playing for dummy marios. It checks their states and calls the startVoice fucntion.
// it also makes it so nozzle sounds aren't global
void sounds() {

	// I don't fully understand how this section works, but I essentially found some memory values that stem from MSGBasic
	// which dictate some of the properties of sounds in SMS. I just took the properties of a sound that wasn't global
	// and applied it to the nozzle charge up sound, and now the volume varies based on distance. This is so that different
	// marios are able to generate the nozzle charge up sound at different volumes
	u32* MSGBasic = SDAword(-0x7160);
	u32* MSGBasicTwo = MSGBasic[0];
	u32* NozzleSoundTypeU32 = MSGBasicTwo[0xC8 / 4];
	u8* NozzleSoundTypeU8 = NozzleSoundTypeU32;
	NozzleSoundTypeU32[0x220 / 4] = 0x00000030;
	NozzleSoundTypeU8[0x224] = 0x80;

	for (int i = 1; i < pNum; i++) {	// iterates through the dummy marios
		u32 marioIndex = i;
		u32* mario = marios[i];

		// if the dummy mario's state has changed, it sets the corresponding playsound value to 1
		if (previousState[marioIndex] != mario[0x7c / 4]) {
			previousState[marioIndex] = mario[0x7c / 4];
			playSoundBools[marioIndex] = 1;
		}

		// if the mario's state is in the soundStateList and playSoundBools is 1, it sends in the corresponding
		// sound id to startVoice()
		for (int i = 0; i < 12; i++) {
			if (mario[0x7c / 4] == soundStateList[i] && playSoundBools[marioIndex] == 1) {
				if (soundStateList[i] == 0x0000088D) {
					u8* TWaterGun = mario[0x3E4];
					if (TWaterGun[0x1C84] == 1) {
						playSoundBools[marioIndex] = 0;
						startVoice(mario, soundIdList[i]);
					}
				} else {
					playSoundBools[marioIndex] = 0;
					startVoice(mario, soundIdList[i]);
				}
			}
		}
	}
}

// these 5 functions intercept the sounds that mario makes and attaches the correct mario position to them.
// the position that a sound is played from (at least for mario sounds) is determined by a pointer that is
// 0xB0 away from the gpMSound, which is why I store the pointer there
void soundFixOne() {
	__asm("addi 29, 29, 16");
	__asm("stw 29, 0xB0 (3)");
	__asm("addi 4, 30, 0");
}
void soundFixTwo() {
	__asm("addi 14, 31, 16");
	__asm("lwz 15, -0x6044 (13)");
	__asm("stw 14, 0xB0 (15)");
	__asm("li 6, 4");
}
void soundFixThree() {
	__asm("lwz 4, -0x6044 (13)");
	__asm("addi 15, 3, 16");
	__asm("stw 15, 0xB0 (4)");
}
void soundFixFour() {
	__asm("lwz 14, -0x6044 (13)");
	__asm("lwz 15, -0x60D8 (13)");
	__asm("addi 15, 15, 16");
	__asm("stw 15, 0xB0 (14)");
	__asm("mtlr 0");
}
void soundFixFive() {
	__asm("addi 15, 29, 16");
	__asm("stw 15, 0xB0 (3)");
	__asm("addi 4, 30, 0");
}

float musicVolume = 0;			// the python scripts increments this by 1 to tell the asm to execute
float musicVolumeStatus = 0;	// this is what the asm uses to tell if setVolume has changed or not
int setTrackVolume(int one, int two, int three, float four);
void setMusicVolume(float vol) {

	// if the musicVolume has changed (it changes depending on the slider in the client script GUI),
	// then we call setTrackVolume 3 times with the volume. The reason we call it 3 times I'm not
	// completely sure, but I think it may be because there are 3 different tracks in-game.
	if (musicVolume != musicVolumeStatus) {
		__asm("mflr 0");
		__asm("stw 0, 0x4 (1)");
		__asm("stwu 1, -0x9C (1)");
		__asm("stmw 3, 0x10 (1)");
		musicVolumeStatus = musicVolume;
		for (int i = 0; i < 3; i++) {
			setTrackVolume(i, 10, 3, musicVolume);
		}
		__asm("lmw 3, 0x10 (1)");
		__asm("addi 1, 1, 0x9C");
		__asm("lwz 0, 0x4 (1)");
		__asm("mtlr 0");
	}
}
// we fix the vanilla code
void volumeAsmRestore() {
	__asm("lfs 0, 0x0104 (4)");
	__asm("fmuls 0, 0, 31");
}

// plays the mario voice of soundId as long as the gate is open
bool playVoice(int soundId)
{
    int* MSound = SDAword(-0x6044);
    bool gateOpen = gateCheck(MSound, 0);
    if (gateOpen)
    {
        u32 *mario = SDAword(-0x60D8);
		startVoice(mario, soundId);
        return true;
    }
    else
        return false;
}

// plays the sound of soundId as long as the gate is open
bool playSound(int soundId)
{
    int* MSound = SDAword(-0x6044);
    bool gateOpen = gateCheck(MSound, 0);
    if (gateOpen)
    {
		startSoundSystemSE(soundId, 0, 0, 0, 0);
        return true;
    }
    else
        return false;
}