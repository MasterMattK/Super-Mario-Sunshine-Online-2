// This file is responsible for custom model support in conjunction with the client script.
// Sorry if the system is a little hard to understand (I don't know if I explained it super well)
#include "defines.h"

u32* modelIndex[realpNum] = { [0 ... (realpNum-1)] = -1 };
u32 currentModelIndex;

// there are sixteen model slots here. For each slot, there are ten more slots for pointers of each bmd for the model
// 0 = mdl1, 1 = cap1, 2 = cap3, 3 = hnd2r, 4 = hnd2l, 5 = hnd3r, 6 = hnd3l, 7 = hnd4r, 8 = glass1, 9 = extra
u32** bmdPointers[16][10] = {[0 ... 15][0 ... 9] = -1};

// ma_mdl1 is the main mario model
u32 mdl1(u32* mario, u32* stack) {

    // this section sets up the stack and backs up registers 3 to 10
	__asm("mflr 0");
	__asm("stw 0, 0x4 (1)");
	__asm("stwu 1, -0x30 (1) ");
	__asm("lis 4, 0x1010");
	__asm("stw 3, 0x8 (1)");
	__asm("stw 4, 0xC (1)");
	__asm("stw 5, 0x10 (1)");
	__asm("stw 6, 0x14 (1)");
	__asm("stw 7, 0x18 (1)");
	__asm("stw 8, 0x1C (1)");
	__asm("stw 9, 0x20 (1)");
	__asm("stw 10, 0x24 (1)");
	__asm("mr 3, 31");  // i'm putting mario's address in r3

    // we figure out which mario's model we're dealing with
	for (int i = 0; i < pNum; i++) {
		if (mario == marios[i]) {
			currentModelIndex = modelIndex[i];
		}
	} 

    // -1 is the default value for currentModelIndex and bmdPointers, so
    // we check to make sure they've actually changed before loading them
	if (currentModelIndex != -1 && bmdPointers[currentModelIndex][0] != -1) {

        // r1 is the stack pointer, but in order for the interpretter to store something there,
        // I have to move it to r4 manually (you can see I have 'u32* stack' as an argument to this function).
        // I'm storing the current mario's bmd pointer 0x8 from the stack pointer. The bmd pointer comes from 
        // the client script when the bmd's are injected
		__asm("mr 4, 1");
		stack[0x8 / 4] = bmdPointers[currentModelIndex][0];
	}

    // this section restores the values we put onto the stack earlier (r3 will be a different pointer if
    // the 'if' statement above was true)
	__asm("lwz 3, 0x8 (1)");
	__asm("lwz 4, 0xC (1)");
	__asm("lwz 5, 0x10 (1)");
	__asm("lwz 6, 0x14 (1)");
	__asm("lwz 7, 0x18 (1)");
	__asm("lwz 8, 0x1C (1)");
	__asm("lwz 9, 0x20 (1)");
	__asm("lwz 10, 0x24 (1)");
	__asm("addi 1, 1, 0x30");
	__asm("lwz 0, 0x4 (1)");
	__asm("mtlr 0");
}

// refer to the comments on mdl1 to understand this function
u32 cap1(u32* mario, u32* stack) {
	__asm("mflr 0");
	__asm("stw 0, 0x4 (1)");
	__asm("stwu 1, -0x30 (1) ");
	__asm("lis 4, 0x1010");
	__asm("stw 3, 0x8 (1)");
	__asm("stw 4, 0xC (1)");
	__asm("stw 5, 0x10 (1)");
	__asm("stw 6, 0x14 (1)");
	__asm("stw 7, 0x18 (1)");
	__asm("stw 8, 0x1C (1)");
	__asm("stw 9, 0x20 (1)");
	__asm("stw 10, 0x24 (1)");
	__asm("lwz 3, 0x1A8 (1)");  // puts the mario address in r3
	for (int i = 0; i < pNum; i++) {
		if (mario == marios[i]) {
			currentModelIndex = modelIndex[i];
		}
	} 
	if (currentModelIndex != -1 && bmdPointers[currentModelIndex][1] != -1) {
		__asm("mr 4, 1");
		stack[0x8 / 4] = bmdPointers[currentModelIndex][1];
	}
	__asm("lwz 3, 0x8 (1)");
	__asm("lwz 4, 0xC (1)");
	__asm("lwz 5, 0x10 (1)");
	__asm("lwz 6, 0x14 (1)");
	__asm("lwz 7, 0x18 (1)");
	__asm("lwz 8, 0x1C (1)");
	__asm("lwz 9, 0x20 (1)");
	__asm("lwz 10, 0x24 (1)");
	__asm("addi 1, 1, 0x30");
	__asm("lwz 0, 0x4 (1)");
	__asm("mtlr 0");
}

// refer to the comments on mdl1 to understand this function
u32 cap3(u32* mario, u32* stack) {
	__asm("mflr 0");
	__asm("stw 0, 0x4 (1)");
	__asm("stwu 1, -0x30 (1) ");
	__asm("lis 4, 0x1010");
	__asm("stw 3, 0x8 (1)");
	__asm("stw 4, 0xC (1)");
	__asm("stw 5, 0x10 (1)");
	__asm("stw 6, 0x14 (1)");
	__asm("stw 7, 0x18 (1)");
	__asm("stw 8, 0x1C (1)");
	__asm("stw 9, 0x20 (1)");
	__asm("stw 10, 0x24 (1)");
	__asm("lwz 3, 0x1A8 (1)");  // puts the mario address in r3
	for (int i = 0; i < pNum; i++) {
		if (mario == marios[i]) {
			currentModelIndex = modelIndex[i];
		}
	} 
	if (currentModelIndex != -1 && bmdPointers[currentModelIndex][2] != -1) {
		__asm("mr 4, 1");
		stack[0x8 / 4] = bmdPointers[currentModelIndex][2];
	}
	__asm("lwz 3, 0x8 (1)");
	__asm("lwz 4, 0xC (1)");
	__asm("lwz 5, 0x10 (1)");
	__asm("lwz 6, 0x14 (1)");
	__asm("lwz 7, 0x18 (1)");
	__asm("lwz 8, 0x1C (1)");
	__asm("lwz 9, 0x20 (1)");
	__asm("lwz 10, 0x24 (1)");
	__asm("addi 1, 1, 0x30");
	__asm("lwz 0, 0x4 (1)");
	__asm("mtlr 0");
}

// refer to the comments on mdl1 to understand this function
u32 glass1(u32* mario, u32* stack) {
	__asm("mflr 0");
	__asm("stw 0, 0x4 (1)");
	__asm("stwu 1, -0x30 (1) ");
	__asm("lis 4, 0x1010");
	__asm("stw 3, 0x8 (1)");
	__asm("stw 4, 0xC (1)");
	__asm("stw 5, 0x10 (1)");
	__asm("stw 6, 0x14 (1)");
	__asm("stw 7, 0x18 (1)");
	__asm("stw 8, 0x1C (1)");
	__asm("stw 9, 0x20 (1)");
	__asm("stw 10, 0x24 (1)");
	__asm("lwz 3, 0x1A8 (1)");  // puts the mario address in r3
	for (int i = 0; i < pNum; i++) {
		if (mario == marios[i]) {
			currentModelIndex = modelIndex[i];
		}
	} 
	if (currentModelIndex != -1 && bmdPointers[currentModelIndex][8] != -1) {
		__asm("mr 4, 1");
		stack[0x8 / 4] = bmdPointers[currentModelIndex][8];
	}
	__asm("lwz 3, 0x8 (1)");
	__asm("lwz 4, 0xC (1)");
	__asm("lwz 5, 0x10 (1)");
	__asm("lwz 6, 0x14 (1)");
	__asm("lwz 7, 0x18 (1)");
	__asm("lwz 8, 0x1C (1)");
	__asm("lwz 9, 0x20 (1)");
	__asm("lwz 10, 0x24 (1)");
	__asm("addi 1, 1, 0x30");
	__asm("lwz 0, 0x4 (1)");
	__asm("mtlr 0");
}

// refer to the comments on mdl1() to understand this function
// (I added comments for the differences in this function)
u32 hands(u32* mario, u32 number, u32* stack) {
	__asm("mflr 0");
	__asm("stw 0, 0x4 (1)");
	__asm("stwu 1, -0x30 (1) ");
	__asm("mr 4, 30");
	__asm("stw 3, 0x8 (1)");
	__asm("stw 4, 0xC (1)");
	__asm("stw 5, 0x10 (1)");
	__asm("stw 6, 0x14 (1)");
	__asm("stw 7, 0x18 (1)");
	__asm("stw 8, 0x1C (1)");
	__asm("stw 9, 0x20 (1)");
	__asm("stw 10, 0x24 (1)");
	__asm("mr 3, 31");

    // there are 5 different hand models, so I use this register to identify them (set by the handBranch functions)
	__asm("mr 4, 14");
	__asm("li 14, 0");

	for (int i = 0; i < pNum; i++) {
		if (mario == marios[i]) {
			currentModelIndex = modelIndex[i];
		}
	} 

    // i check which hand model is being sent in
	if (number == 3 || number == 4 || number == 5 || number == 6 || number == 7) {
		if (currentModelIndex != -1 && bmdPointers[currentModelIndex][number] != -1) {
			__asm("mr 5, 1");
			stack[0x8 / 4] = bmdPointers[currentModelIndex][number];
		}
	}
	__asm("lwz 3, 0x8 (1)");
	__asm("lwz 4, 0xC (1)");
	__asm("lwz 5, 0x10 (1)");
	__asm("lwz 6, 0x14 (1)");
	__asm("lwz 7, 0x18 (1)");
	__asm("lwz 8, 0x1C (1)");
	__asm("lwz 9, 0x20 (1)");
	__asm("lwz 10, 0x24 (1)");
	__asm("addi 1, 1, 0x30");
	__asm("lwz 0, 0x4 (1)");
	__asm("mtlr 0");
}

// the following 5 functions identify which hand model to load
void handBranchOne() {
	__asm("li 14, 3");
	__asm("lis 4, 0x1010");
}
void handBranchTwo() {
	__asm("li 14, 4");
	__asm("lis 4, 0x1010");
}
void handBranchThree() {
	__asm("li 14, 5");
	__asm("lis 4, 0x1010");
}
void handBranchFour() {
	__asm("li 14, 6");
	__asm("lis 4, 0x1010");
}
void handBranchFive() {
	__asm("li 14, 7");
	__asm("lis 4, 0x1010");
}

// using custom models sometimes spits out errors in-game, so these 3 functions prevent those errors
void __attribute__((noinline)) customModelFix1() {
	__asm("cmpwi 4, 0");
	__asm("li 0, 0");
	__asm("beq 0x8");
	__asm("lhz 0, 0x18 (4)");
	__asm("b cMF1");
}
void __attribute__((noinline)) customModelFix2() {
	__asm("cmpwi 6, 0");
	__asm("li 10, 0");
	__asm("beq 0x8");
	__asm("lwz 10, 0x38 (6)");
	__asm("b cMF2");
}
void __attribute__((noinline)) customModelFix3() {
	__asm("cmpwi 5, 0");
	__asm("li 9, 0");
	__asm("beq 0x8");
	__asm("lwz 9, 0x38 (5)");
	__asm("b cMF3");
}