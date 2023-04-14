// This file deals with any functions related to fludd
#include "defines.h"

// each water particle in SMS has some data tied to it. if the particle came from a dummy mario,
// this function inserts a 1 at the end of that data (there's normally a 0)
void fluddId1() {
	__asm("lis 14, 0x8040");
	__asm("ori 14, 14, 0xE0E8");
	__asm("lwz 14, 0x0(14)");
	__asm("lwz 14, 0x3E4(14)");
	__asm("lwz 14, 0x374(14)");
	__asm("lwz 14, 0x1D0C(14)");
	__asm("stfs 0, 0x0014 (3)");
	__asm("cmpw 14, 30");
	__asm("bne 0x8");
	__asm("b 0xC");
	__asm("li 14, 1");
	__asm("stb 14, 0x0017 (3)");
	__asm("b ftOne");
}

// this function is able to access the info on each water particle. if there is anything other than 0 at
// the end of the water particle data, the function skips over the particle's collision detection.
// This makes it so dummy marios' water doesn't interact with objects. This is to avoid desync issues,
// but we may remove this in the future
void fluddId2() {
	__asm("addi 14, 19, 0x800");
	__asm("li 18, 0x3");
	__asm("divw 18, 19, 18");
	__asm("sub 14, 14, 18");
	__asm("sub 14, 26, 14");
	__asm("lwz 14, 0x0(14)");
	__asm("rlwinm 14, 14, 0, 16, 31");
	__asm("cmpwi 14, 0");
	__asm("beq 0x14");
	__asm("lis 14, 0x8027");
	__asm("ori 14, 14, 0xeb24");
	__asm("mtctr 14");
	__asm("bctrl");
	__asm("lwz 3, 0 (3)");
	__asm("b ftTwo");
}

// This prevents fludd's angle from being changed in-game for dummy marios (the script does it)
void fluddAngle1() {
	__asm("lis 14, 0x8040");
	__asm("ori 14, 14, 0xE0E8");
	__asm("lwz 14, 0x0(14)");
	__asm("lwz 14, 0x3E4(14)");
	__asm("addi 14, 14, 0xC");
	__asm("cmpw 14, 30");
	__asm("bne 0x8");
	__asm("sth 0, 0x36E(31)");
	__asm("b faOne");
}

// This prevents fludd's angle from being changed in-game for dummy marios (the script does it)
void fluddAngle2() {
	__asm("lis 14, 0x8040");
	__asm("ori 14, 14, 0xE0E8");
	__asm("lwz 14, 0x0(14)");
	__asm("lwz 14, 0x3E4(14)");
	__asm("addi 14, 14, 0xC");
	__asm("cmpw 14, 30");
	__asm("bne 0x8");
	__asm("sth 0, 0x36E(31)");
	__asm("b faTwo");
}

// this function makes it so no dummy marios or dummy yoshis can set their spam state to 0 (done by script)
void spamSpray1() {
	__asm("lis 14, 0x8000");
	__asm("cmpwi 3, 0x0");
	__asm("bgt 0x44");
	__asm("lwz 14, 0x3E4(3)");
	__asm("lbz 14, 0x1C84 (14)");
	__asm("cmpwi 14, 0x0"); // spray nozzle
	__asm("beq 0xC");
	__asm("cmpwi 14, 0x3"); // yoshi nozzle
	__asm("bne 0x2C");
	__asm("lis 14, 0x8040");
	__asm("ori 14, 14, 0xE0E8");
	__asm("lwz 14, 0x0(14)");
	__asm("lwz 14, 0x3E4(14)");
	__asm("addi 15, 14, 0x390");
	__asm("addi 16, 14, 0x11B8");
	__asm("cmpw 29, 15");
	__asm("beq 0xC");
	__asm("cmpw 29, 16");
	__asm("bne 0x8");
	__asm("stb 0, 0x0385 (29)");
	__asm("b ssOne");
}

// this function makes it so no dummy marios or dummy yoshis can set their spam state to 1 (done by script)
void spamSpray2() {
	__asm("lis 14, 0x8000");
	__asm("cmpwi 3, 0x0");
	__asm("bgt 0x44");
	__asm("lwz 14, 0x3E4(3)");
	__asm("lbz 14, 0x1C84 (14)");
	__asm("cmpwi 14, 0x0");
	__asm("beq 0xC");
	__asm("cmpwi 14, 0x3");
	__asm("bne 0x2C");
	__asm("lis 14, 0x8040");
	__asm("ori 14, 14, 0xE0E8");
	__asm("lwz 14, 0x0(14)");
	__asm("lwz 14, 0x3E4(14)");
	__asm("addi 15, 14, 0x390");
	__asm("addi 16, 14, 0x11B8");
	__asm("cmpw 29, 15");
	__asm("beq 0xC");
	__asm("cmpw 29, 16");
	__asm("bne 0x8");
	__asm("stb 0, 0x0385 (29)");
	__asm("b ssTwo");
}

// this function makes it so no dummy marios or dummy yoshis can set their spam state to 2 (done by script)
void spamSpray3() {
	__asm("lis 14, 0x8040");
	__asm("ori 14, 14, 0xE0E8");
	__asm("lwz 14, 0x0(14)");
	__asm("lwz 14, 0x3E4(14)");
	__asm("addi 15, 14, 0x390");
	__asm("addi 16, 14, 0x11B8");
	__asm("cmpw 29, 15");
	__asm("beq 0xC");
	__asm("cmpw 29, 16");
	__asm("bne 0x8");
	__asm("stb 0, 0x0385 (29)");
	__asm("b ssThree");
}

// This function doesn't allow dummy marios to change the angle of fludd in sidestep mode (this is done by script)
void sideStepFluddAng() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0x0(15)");
	__asm("lwz 16, 0x108(15)"); // TMarioController
	__asm("lwz 15, 0x3E4(15)");
	__asm("addi 17, 15, 0xE34");// TNozzleDeform for yoshi nozzle
	__asm("addi 15, 15, 0xC");  // TNozzleDeform for spray nozzle
	__asm("cmpw 17, 30");
	__asm("beq 0x14");
	__asm("cmpw 15, 30");
	__asm("beq 0xC");
	__asm("cmpw 16, 30");
	__asm("bne 0x8");
	__asm("lfs 1, 0x00AC (3)");
	__asm("b cFive");
}