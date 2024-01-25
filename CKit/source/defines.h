#include <stdarg.h>

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

typedef float Mtx[3][4];

typedef enum gamemodes {
	DEFAULT,
	TAG,
	MANHUNT,
} gamemodes;

// Player number and mario list
#define realpNum 6
extern int pNum;
extern unsigned int********* marios[realpNum];
extern gamemodes gamemode;
extern unsigned int currentTime;
extern bool isTagger, isHunter, tagActive, manhuntActive;
extern bool cutsceneCooldownPending;

// List of global functions to execute
extern void tag_onStageLoad();
extern void manhunt_onStageLoad();
extern void printString(char *);
extern void printNumber(int);
extern bool playVoice(int soundId);
extern bool playSound(int soundId);
extern void initPrint(u32* j2dprint, u32 color, int fontSize);
extern void tagMain();
extern void manhuntMain();

static const u32 WHITE = 0xffffff88;
static const u32 RED = 0xff0000ff;
static const u32 PURPLE = 0xff00ffff;
static const u32 GREEN = 0x00ff00fff;
static const u32 GRAY = 0x777777ff;

static u32 gPrint[(0x90 / 4)] = { [0 ... 0x80 / 4] = 0xff0000ff };  // stuff for printing (thx brocoli)

#define SDA 0x803e4d20

#define ADDR_FONT 0x81693cd8
#define ADDR_GFX 0x81729c40

u32* alloc(int allocsize);
void ct_Mario(u32* mario);
void load_Mario(u32* mario, u32* unk);

inline int* fromRegister(int reg) {
	int toReturn;
	__asm("mr %0, %1" : "=r" (toReturn) : "X" (reg));
	return toReturn;
}
inline void toRegister(int reg, int val) {
	__asm("mr %0, %1" :: "X" (reg), "r" (val));
}

inline float fromRegisterF(int reg) {
	float toReturn;
	__asm("fmr %0, %1" : "=r" (toReturn) : "X" (reg));
	return toReturn;
}
inline void toRegisterF(int reg, float val) {
	__asm("fmr %0, %1" :: "X" (reg), "r" (val));
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

inline void GXFIFO_Add(int val) {
	__asm("stw %0, -0x8000(%1)" :: "r" (val), "r" (0xCC010000));
}
inline void GXFIFO_Addb(char val) {
	__asm("stb %0, -0x8000(%1)" :: "r" (val), "r" (0xCC010000));
}
inline void GXFIFO_Addf(float val) {
	__asm("stfs %0, -0x8000(%1)" :: "f" (val), "r" (0xCC010000));
}