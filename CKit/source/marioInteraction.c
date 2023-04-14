// This file deals with any functions that alter the way marios interact with one another
#include "defines.h"

// if we're trying to pick up something, make sure it's not one of the dummy marios first
u32* isTakeSituation_Mario(u32* mario, u32* otherObj) {
	for (int i = 1; i < pNum; i++) {
		if (otherObj == marios[i]) {
			return 0;
		}
	}
	return isTakeSituation(mario, otherObj);
}

// this function makes it so dummy marios can't touch any object other than other marios
void marioHitActors(u32* TObjHitCheck, u32* THitActorOne, u32* THitActorTwo) {
	for (int i = 0; i < pNum; i++) {
		if (THitActorOne == marios[i]) {
			for (int i = 0; i < pNum; i++) {
				if (THitActorTwo == marios[i]) {
					if (THitActorOne[0x7C / 0x4] != 0x133F && THitActorTwo[0x7C / 0x4] != 0x133F) {
						suffererIsInAttackArea(TObjHitCheck, THitActorOne, THitActorTwo);
					}
					else return TObjHitCheck;
				}
				else if (i == pNum - 1) {
					if (THitActorOne == marios[0]) {
						suffererIsInAttackArea(TObjHitCheck, THitActorOne, THitActorTwo);
					}
					else return TObjHitCheck;
				}
			}
		}
		else if (i == pNum - 1) {
			for (int i = 1; i < pNum; i++) {
				if (THitActorTwo == marios[i]) {
					return TObjHitCheck;
				}
				else if (i == pNum - 1) {
					suffererIsInAttackArea(TObjHitCheck, THitActorOne, THitActorTwo);
				}
			}
		}
	}
}

// if two marios collide, then this function calls hitNormal(), which is the function that is used
// to see if mario is on top of objects like nozzle boxes
void headJump1() {
	__asm("mr 3, 31");
	__asm("mr 4, 30");
	__asm("li 15, 1");
	__asm("lis 14, 0x8028");
	__asm("ori 14, 14, 0x25E8");
	__asm("mtctr 14");
	__asm("bctrl");
	__asm("lwz 0, 0x006C (31)");
	__asm("b hjOne");
}

// this automatically returns a 1 in trample exec if it's a mario that's getting jumped on, otherwise it carries on normally
void headJump2(u16* mario) {
	__asm("mr 14, 3");
	__asm("mr 3, 31");
	if (mario[0x8 / 2] == 0xB863) {
		__asm("li 3, 1");
		__asm("b hjTwoTwo");
	}
	__asm("mr 3, 14");
	__asm("mtlr 12");
	__asm("b hjTwo");
}

// if hitNormal has found that a mario is above another mario, then this function checks to see if the top
// mario is groundpounding, in which case it bonks the bottom mario
void __attribute__((noinline)) headJump3() {
	__asm("cmpwi 15, 0x1");
	__asm("bne 0x20");
	__asm("lis 15, 0x0080");
	__asm("ori 15, 15, 0x08A9");
	__asm("cmpw 15, 3");
	__asm("bne 0x10");
	__asm("lis 15, 0x0002");
	__asm("ori 15, 15, 0x08B0");
	__asm("stw 15, 0x7C(31)");
	__asm("li 15, 0");
	__asm("subis 0, 3, 128");
	__asm("b hjThree");
}