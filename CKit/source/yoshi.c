// This file deals with any functions that are related to yoshi
#include "defines.h"

// this function stops the code from reading TMarioGamepad for dummy marios
void yoshi1() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0 (15)");
	__asm("cmpw 15, 30");
	__asm("bne 0x8");
	__asm("lwz 0, 0x00D4 (3)");
	__asm("b yOne");
}

// this function stops the code from reading TMarioGamepad for dummy marios, and returns a 0 in r0 in that case
void yoshi2() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0 (15)");
	__asm("cmpw 15, 4");
	__asm("bne 0xC");
	__asm("lwz 0, 0x00D4 (3)");
	__asm("b 0x8");
	__asm("li 0, 0");
	__asm("b yTwo");
}

// this function stops the code from reading TMarioGamepad for dummy marios
void yoshi3() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0 (15)");
	__asm("cmpw 15, 30");
	__asm("bne 0x8");
	__asm("lwz 0, 0x00D0 (3)");
	__asm("b yThree");
}

// this function stops the code from reading TMarioGamepad for dummy marios
void yoshi4() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0 (15)");
	__asm("cmpw 15, 5");
	__asm("bne 0x8");
	__asm("lwz 0, 0x00D0 (3)");
	__asm("b yFour");
}

// this function stops the code from reading TMarioGamepad for dummy marios
void yoshi5() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0 (15)");
	__asm("cmpw 15, 5");
	__asm("bne 0x8");
	__asm("lwz 0, 0x00D0 (3)");
	__asm("b yFive");
}

// this prevents dummy mario yoshis from updating their flutter state in-game (its done through the script)
void yoshi6() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0 (15)");
	__asm("lwz 15, 0x3F0 (15)");
	__asm("cmpw 15, 31");
	__asm("bne 0x8");
	__asm("stb 0, 0x00B8 (31)");
	__asm("b ySix");
}

// this function stops the code from reading TMarioGamepad for dummy marios
void yoshi7() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0 (15)");
	__asm("cmpw 15, 30");
	__asm("bne 0x8");
	__asm("lwz 0, 0x00D0 (3)");
	__asm("b ySeven");
}

// if the main mario's yoshi is not being ridden, then the water color can be changed, otherwise we blr
void yoshi8() {
	__asm("lis 17, 0x8040");
	__asm("ori 17, 17, 0xE0E8");
	__asm("lwz 17, 0x0 (17)");
	__asm("lwz 17, 0x3f0 (17)");
	__asm("lbz 17, 0x0 (17)");
	__asm("cmpwi 17, 0x0008");
	__asm("bne 0x8");
	__asm("blr");
	__asm("stb 0, 0x5D5F (3)"); // this line stores the color of water
	__asm("b yEight");
}

// if r0 is not 0, we store the water color
void yoshi9() {
	__asm("cmpwi 0, 0x0");
	__asm("beq 0x8");
	__asm("stb 0, 0x5D5F(3)");
	__asm("b yNine");
}

// if r0 is not 0, we store the water color
void yoshi10() {
	__asm("cmpwi 0, 0x0");
	__asm("beq 0x8");
	__asm("stb 0, 0x5D5F(3)");
	__asm("b yTen");
}