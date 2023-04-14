#include <stdarg.h>

// Player number and mario list
#define realpNum 8
extern int pNum;
extern unsigned int********* marios[realpNum];

#define SDA 0x803e4d20

#define ADDR_FONT 0x81693cd8
#define ADDR_GFX 0x81729c40

#define DecToColor(r, g, b, a) (((r + 0x100) * 0x100 + g) * 0x100 + b) * 0x100 + a
#define DGXGraphics__texturePrintf(gfxunk, font, x, y, fmt, ...) 	DGXGraphics__texturePrintf(gfxunk, font, x, y, fmt __VA_OPT__(, ) __VA_ARGS__)
#define OSReport(...)  OSReport(__VA_ARGS__)

typedef unsigned char bool;
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif

#ifndef nullptr
#define nullptr 0
#endif

#define u64 unsigned long long int
#define u32 unsigned int
#define s32 signed int
#define u16 unsigned short
#define s16 signed short
#define u8 unsigned char
#define s8 signed char

// Custom typedefs

typedef struct
{
	float x;
	float y;
	float z;
} Vector3f;

u32* alloc(int allocsize);
void ct_Mario(u32* mario);
void load_Mario(u32* mario, u32* unk);
/*
void memclear(char* zone, int size) {
	for (int i = 0; i < size; i++) {
		zone[i] = 0;
	}
}
void memcpy(char* paste, char* copy, int size) {
	for (int i = 0; i < size; i++) {
		paste[i] = copy[i];
	}
}
*/
inline void halt() {
	__asm("b 0");
}

inline int* fromRegister(int reg) {
	int toReturn;
	__asm("mr %0, %1" : "=r" (toReturn) : "X" (reg));
	return toReturn;
}
inline void toRegister(int reg, int val) {
	__asm("mr %0, %1" :: "X" (reg), "r" (val));
}

inline int SDAword(int offset) {
	int toReturn;
	__asm("lwz %0, %1(13)" : "=r" (toReturn) : "X" (offset));
	return toReturn;
}
inline int SDAshort(int offset) {
	int toReturn;
	__asm("lhz %0, %1(13)" : "=r" (toReturn) : "X" (offset));
	return toReturn;
}
inline int SDAbyte(int offset) {
	int toReturn;
	__asm("lbz %0, %1(13)" : "=r" (toReturn) : "X" (offset));
	return toReturn;
}
inline void SDAstoreword(int offset, int val) {
	__asm("stw %0, %1(13)" :: "r" (val), "X" (offset));
}
inline void SDAstorehalf(int offset, int val) {
	__asm("sth %0, %1(13)" :: "r" (val), "X" (offset));
}
inline void SDAstorebyte(int offset, int val) {
	__asm("stb %0, %1(13)" :: "r" (val), "X" (offset));
}

inline int TOCword(int offset) {
	int toReturn;
	__asm("lwz %0, %1(2)" : "=r" (toReturn) : "X" (offset));
	return toReturn;
}
inline int TOCshort(int offset) {
	int toReturn;
	__asm("lhz %0, %1(2)" : "=r" (toReturn) : "X" (offset));
	return toReturn;
}
inline int TOCbyte(int offset) {
	int toReturn;
	__asm("lbz %0, %1(2)" : "=r" (toReturn) : "X" (offset));
	return toReturn;
}
inline void TOCstoreword(int offset, int val) {
	__asm("stw %0, %1(2)" :: "r" (val), "X" (offset));
}
inline void TOCstorefloat(int offset, float val) {
	__asm("stfs %0, %1(2)" :: "r" (val), "X" (offset));
}
inline void TOCstorehalf(int offset, int val) {
	__asm("sth %0, %1(2)" :: "r" (val), "X" (offset));
}
inline void TOCstorebyte(int offset, int val) {
	__asm("stb %0, %1(2)" :: "r" (val), "X" (offset));
}