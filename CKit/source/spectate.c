#include "defines.h"

int currentMario = 0;
int previousInput = 0;

void spectateMode() {
    __asm("mflr 0");
    __asm("stw 0, 0x4 (1)");
    __asm("stwu 1, -0xB0 (1)");
    __asm("stw 3, 0x8 (1)");
	__asm("stw 4, 0xC (1)");
	__asm("stw 5, 0x10 (1)");
	__asm("stw 6, 0x14 (1)");
	__asm("stw 7, 0x18 (1)");
	__asm("stw 8, 0x1C (1)");
	__asm("stw 9, 0x20 (1)");
	__asm("stw 10, 0x24 (1)");
    u32 input = marios[0][0x4FC / 4][0x18 / 4];
    input = input & 0x00000003;
    if (input != 0 && previousInput == 0) {
        int marioIndex = selectMarioIndex(input);
        u32* marioU32 = marios[marioIndex];
        u16* marioU16 = marios[marioIndex];
        SDAstoreword(-0x60B4, marioU32 + (0x10 / 4));   // gpMarioPos
        SDAstoreword(-0x60B0, marioU32 + (0x94 / 4));   // gpMarioAngleX
        SDAstoreword(-0x60AC, marioU16 + (0x96 / 2));   // gpMarioAngleY
        SDAstoreword(-0x60A8, marioU32 + (0x98 / 4));   // gpMarioAngleZ
        SDAstoreword(-0x60A4, marioU32 + (0xA4 / 4));   // gpMarioSpeedX
        SDAstoreword(-0x60A0, marioU32 + (0xA8 / 4));   // gpMarioSpeedY
        SDAstoreword(-0x609C, marioU32 + (0xAC / 4));   // gpMarioSpeedZ
    }
    previousInput = input;
    __asm("lwz 3, 0x8 (1)");
	__asm("lwz 4, 0xC (1)");
	__asm("lwz 5, 0x10 (1)");
	__asm("lwz 6, 0x14 (1)");
	__asm("lwz 7, 0x18 (1)");
	__asm("lwz 8, 0x1C (1)");
	__asm("lwz 9, 0x20 (1)");
	__asm("lwz 10, 0x24 (1)");
	__asm("addi 1, 1, 0xB0");
	__asm("lwz 0, 0x4 (1)");
	__asm("mtlr 0");
}

int selectMarioIndex(u32 input) {
    if (input == 0x00000002) {
        for (int i = 0; i < pNum; i++) {
            currentMario += 1;
            if (currentMario >= pNum) currentMario = 0;
            if (marios[currentMario][0x7C / 4] != 0x133F) return currentMario;
        }
    } else if (input == 0x00000001) {
        for (int i = 0; i < pNum; i++) {
            currentMario -= 1;
            if (currentMario < 0) currentMario = (pNum - 1);
            if (marios[currentMario][0x7C / 4] != 0x133F) return currentMario;
        }
    }
    return 0;
}