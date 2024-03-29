#include "defines.h"

unsigned int currentTime = 0;
// first index indicates the type of flag. 0 = shine, 1 = blue, 2 = other
// second index is the id to send into the set funcitons
int flagToUpdate[2] = {-1, 0};
bool bResetFlags = false;

// updates the currentTimeSec variable every 1/4 frame
void updateSeconds()
{
	static int repeat = 0;
    
    u32** TMario = 0x8040E0E8;
    u32 realM3UModelMario = TMario[0][0x3A8 / 4];
    u32 currentM3UModelMario = fromRegister(31);

    // we only want to increment with the original mario
    if (realM3UModelMario != currentM3UModelMario)
        return;

    if (repeat == 120)
    {
        currentTime++;
        repeat = 0;
    } else repeat++;
}

// this function sets a part of the dummy marios' controller memory to 0, which makes them able to sleep
void sleepFix(u32* controller, u32* mario) {
	__asm("mr 14, 4");
	__asm("mr 4, 31");
	if (mario != marios[0]) {
		controller[0x20 / 4] = 0;
	}
	__asm("mr 4, 14");
	__asm("lfs 0, 0x20 (3)");
}

// When the script sets a value in TPauseMenu2 to 9, this function skips over set() from TGameSequence.
// This just prevents the game from overwriting the next stage when the script wants to change stages
void stageChange() {
	__asm("addi 3, 3, 0x12");
	__asm("lwz 14, 0xAC (31)");
	__asm("lbz 15, 0x109 (14)");    // value set by script
	__asm("cmpwi 15, 0x9");     
	__asm("bne 0x1C");
	__asm("li 16, 0x2");
	__asm("stb 16, 0x109 (14)");
	__asm("lis 14, 0x8029");
	__asm("ori 14, 14, 0x9234");
	__asm("mtctr 14");
	__asm("bctrl");
	__asm("b csOne");
}

// if it's a dummy mario, we don't branch to the function which moves mario on moving objects
void movingObjectsFix() {
	__asm("lis 14, 0x8040");
	__asm("ori 14, 14, 0xE0E8");
	__asm("lwz 14, 0x0 (14)");
	__asm("cmpw 14, 30");
	__asm("bnelr");
	__asm("lis 14, 0x8034");
	__asm("ori 14, 14, 0xA2D0");
	__asm("mtctr 14");
	__asm("bctrl");
	__asm("b mOF");
}

// doesn't allow the code to store some input flags for dummy marios
void dummyFix1() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0(15)");
	__asm("cmpw 15, 30");
	__asm("bne 0x8");
	__asm("stw 0, 0x74 (30)");
	__asm("b mpTwo");
}

// doesn't allow the code to store some input flags for dummy marios
void dummyFix2() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0(15)");
	__asm("cmpw 15, 30");
	__asm("bne 0x8");
	__asm("stw 0, 0x74 (30)");
	__asm("b mpThree");
}

// doesn't allow the code to store base acceleration (pretty much stick input) for dummy marios
void dummyFix3() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0(15)");
	__asm("cmpw 15, 30");
	__asm("bne 0x8");
	__asm("stfs 0, 0x8C (31)");
	__asm("b mpFour");
}

// checks the object's keycode and mario list to see if it's one of the dummy marios. If it is,
// it doesn't allow the code to store the y angle
void dummyFix4(u16* mario) {
	__asm("mr 3, 31");
	if (mario[0x8 / 2] == 0xB863 && mario != marios[0]) {
		__asm("b mpFive");
	}
	__asm("sth 0, 0x96 (31)");
	__asm("b mpFive");
}


// doesn't allow the code to store acceleration direction for dummy marios
void dummyFix5() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0(15)");
	__asm("cmpw 15, 31");
	__asm("bne 0x8");
	__asm("sth 0, 0x90 (31)");
	__asm("b mpSix");
}

// doesn't allow the code to store acceleration direction for dummy marios
void dummyFix6() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0(15)");
	__asm("cmpw 15, 31");
	__asm("bne 0x8");
	__asm("sth 0, 0x90 (31)");
	__asm("b mpSeven");
}

// we skip checkController if its a dummy mario
void dummyFix7() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0x0(15)");
	__asm("cmpw 15, 3");
	__asm("bnelr");
	__asm("mflr 0");
	__asm("b cOne");
}

// if it's a dummy mario, we don't load from TMarioGamePad and return a 0 in r0
void dummyFix8() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0x0(15)");
	__asm("cmpw 15, 3");
	__asm("beq 0xC");
	__asm("li 0, 0");
	__asm("b 0x8");
	__asm("lwz 0, 0x00D0 (5)");
	__asm("b cTwo");
}

// if it's a dummy mario, we don't load from TMarioGamePad and return a 0 in r0
void dummyFix9() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0x0(15)");
	__asm("cmpw 15, 30");
	__asm("beq 0xC");
	__asm("li 0, 0");
	__asm("b 0x8");
	__asm("lwz 0, 0x00D4 (3)");
	__asm("b cThree");
}

// if it's a dummy mario, we don't load from TMarioGamePad and return 0x600 in r3 (i can't remember why we
// return 0x600, but it has something to do with an input)
void dummyFix10() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0x0(15)");
	__asm("cmpw 15, 30");
	__asm("beq 0xC");
	__asm("li 3, 0x600");
	__asm("b 0x8");
	__asm("lwz 3, 0x00D0 (4)");
	__asm("b cFour");
}

// if it's a dummy mario, we don't load from TMarioGamePad
void dummyFix11() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0x0(15)");
	__asm("cmpw 15, 30");
	__asm("bne 0x8");
	__asm("lfs 1, 0x00B4 (3)");
	__asm("b cSix");
}

// if it's a dummy mario, we don't load from TMarioGamePad
void dummyFix12() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0x0(15)");
	__asm("cmpw 15, 30");
	__asm("bne 0x8");
	__asm("lfs 1, 0x00A8 (4)");
	__asm("b cSeven");
}

// if it's a dummy mario, we don't store the y angle from y cam (this is done from script)
void dummyFix13() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0x0(15)");
	__asm("cmpw 15, 30");
	__asm("bne 0x8");
	__asm("sth 0, 0x0096 (31)");
	__asm("b cEight");
}

// if it's a dummy mario, we don't update mario's state (this is done from script)
void dummyFix14(u16* mario) {
	__asm("mr 14, 3");
	__asm("mr 3, 30");
	if (mario[0x8 / 2] == 0xB863 && mario != marios[0]) {
		__asm("mr 3, 14");
		__asm("b cNine");
	} else {
		__asm("mr 3, 14");
		__asm("stw 29, 0x7C (30)");
		__asm("b cNine");
	}
}

// if it's a dummy mario, we don't load from TMarioGamePad and return a 0 in r0
void dummyFix15() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0x0(15)");
	__asm("cmpw 15, 30");
	__asm("beq 0xC");
	__asm("li 0, 0");
	__asm("b 0x8");
	__asm("lwz 0, 0x00D4 (3)");
	__asm("b cTen");
}

// if it's a dummy mario, we don't load from TMarioGamePad and return a 0 in r0
void dummyFix16() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0x0(15)");
	__asm("cmpw 15, 30");
	__asm("beq 0xC");
	__asm("li 0, 0");
	__asm("b 0x8");
	__asm("lwz 0, 0x00D4 (3)");
	__asm("b cEleven");
}

// doesn't allow the code to check mario controller
void dummyFix17() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0(15)");
	__asm("cmpw 15, 31");
	__asm("bne 0x8");
	__asm("lwz 0, 0x00D4 (3)");
	__asm("b mpNine");
}

// doesn't allow the code to check mario controller
void dummyFix18() {
	__asm("lis 15, 0x8040");
	__asm("ori 15, 15, 0xE0E8");
	__asm("lwz 15, 0(15)");
	__asm("cmpw 15, 31");
	__asm("bne 0x8");
	__asm("lwz 0, 0x00D0 (4)");
	__asm("b mpTen");
}

// if it's a dummy mario, we don't update mario's position (this is done from script)
void stopPosUpdate1(u16* mario) {
	__asm("mr 14, 3");
	__asm("mr 3, 30");
	if (mario[0x8 / 2] == 0xB863 && mario != marios[0]) {
		__asm("mr 3, 14");
		__asm("b posUpdate1");
	} else {
		__asm("mr 3, 14");
		__asm("stfs 0, 0x10 (30)");
		__asm("b posUpdate2");
	}
}

void stopPosUpdate2(u16* mario) {
	__asm("mr 14, 3");
	__asm("mr 3, 22");
	if (mario[0x8 / 2] == 0xB863 && mario != marios[0]) {
		__asm("mr 3, 14");
		__asm("b posUpdate3");
	} else {
		__asm("mr 3, 14");
		__asm("stfs 0, 0x10 (22)");
		__asm("b posUpdate4");
	}
}

void updateFlags() {
	static u32* gpFlagManager = 0x8040E160;

	if (bResetFlags)
		resetFlags();

	switch (flagToUpdate[0])
	{
		// no current flags to update
		case -1:
			return;
		// shine flag to update
		case 0:
			setShineFlag(*gpFlagManager, flagToUpdate[1], 1);
			flagToUpdate[0] = -1;
			break;
		// blue coin flag to update
		case 1:
			int stage = (flagToUpdate[1] / 50) + 1;
			if (stage >= 7)	// for some reason hotel delfino takes id 7, so we have to offset this here
				stage++;
			int id = flagToUpdate[1] % 50;
			setBlueCoinFlag(*gpFlagManager, stage, id);
			flagToUpdate[0] = -1;
			break;
		// misc flag to update
		case 2:
			setBool(*gpFlagManager, 1, flagToUpdate[1]);
			flagToUpdate[0] = -1;
			break;
	}
}

void resetFlags() {
	static u32* gpFlagManager = 0x8040E160;

	// reset shines
	for (int i = 0; i < 120; i++) {
		setBool(*gpFlagManager, 0, 0x10000+i);
	}
	setFlag(*gpFlagManager, 0x40000, 0);
	u16* TGCConsole2 = ((u16**)SDAword(-0x6048))[0x74 / 4];
	TGCConsole2[0x8A / 2] = 0x105;

	// reset blues
	for (int i = 0; i < 450; i++) {
		setBool(*gpFlagManager, 0, 0x10078+i);
	}
	setFlag(*gpFlagManager, 0x40001, 0);

	// reset misc1 flags
	for (int i = 0x10360; i < 0x10360+80; i++) {
		if (i == 0x1039a || i == 0x1039d || i == 0x103a6)
			continue;
		setBool(*gpFlagManager, 0, i);
	}

	// reset misc2 flags
	for (int i = 0x30008; i < 0x30008+8; i++) {
		setBool(*gpFlagManager, 0, i);
	}

	bResetFlags = false;
}

void allowShineDecrement() {
	u32 internalShineCount = fromRegister(30);
	u32* TGCConsole2 = fromRegister(31);
	if (TGCConsole2[0x64 / 4] != internalShineCount) {
		TGCConsole2[0x64 / 4] = internalShineCount;
		((u16*)TGCConsole2)[0x8A / 2] = 0xFB;
	} 
	else  {
		((s16*)TGCConsole2)[0x8A / 2] = -1;
	}
}

void allowBlueDecrement(u32 internalBlueCount, u32 visualBlueCount) {
	u32* TGCConsole2 = fromRegister(31);
	TGCConsole2[0x168 / 4] = internalBlueCount;
}

typedef struct OSReceiveMessageException
{
	u32 funcAddr;
	u16 exceptionType;
	u32 *context;
	u32 DSISR;
	u32 DAR;
} OSReceiveMessageException;

typedef struct exceptionContext
{
	bool hasExceptionOccured;	// _0
	u32 context;				// _4
	char *exceptionType;		// _8
	u32 SRR0;					// _C
	u32 SRR1;					// _10
	u32 DSISR;					// _14
	u32 DAR;					// _18
	u32 GPR[32];				// _1C
	double FPR[32];				// _A0
	u32 MSR;					// _1A0
	u32 FPSCR;					// _1A4
	u32 trace[10][3];			// _1A8

} exceptionContext;

exceptionContext osContext = {
	false,
	0,
	nullptr,
	0,
	0,
	0,
	0,
	{0},
	{0.0},
	0,
	0,
	{{0}}
};

// this function intercepts exception context info that gets printed on screen when SMS crashes so that it can be read by the GUI and
// submitted to us via google form
void logExceptionContext() {
	OSReceiveMessageException **stack = fromRegister(1); // I have to offset from the stack that the compiler creates for this function
	OSReceiveMessageException *o = stack[0x1C / 4];

	osContext.context = o->context;
	osContext.exceptionType = *((char **)(0x803e0238 + (o->exceptionType * 4)));
	osContext.SRR0 = o->context[0x198 / 4];
	osContext.SRR1 = o->context[0x19C / 4];
	osContext.DSISR = o->DSISR;
	osContext.DAR = o->DAR;

	// get all general purpose register vals
	for (int i = 0; i < 32; i++) {
		osContext.GPR[i] = o->context[i];
	}

	double *doubleContextPtr = (double *)(o->context);
	// get all floating point register vals
	for (int i = 0; i < 32; i++) {
		osContext.FPR[i] = doubleContextPtr[(0x90 / 8) + i];
	}
	osContext.MSR = SDAword(-0x5EF0);
	osContext.FPSCR = SDAword(-0x5EEC);

	u32 *stackPtr = o->context[1]; // get the stack pointer from r1
	// get the stack trace
	for (int i = 0; i < 10; i++) {
		if (stackPtr == 0) break;
		if (((u32)stackPtr) == 0xffffffff) break; 

		osContext.trace[i][0] = stackPtr;
		osContext.trace[i][1] = *stackPtr;
		osContext.trace[i][2] = stackPtr[1];
		stackPtr = *stackPtr;
	}

	osContext.hasExceptionOccured = true;


	toRegister(3, SDAword(-0x5F08)); // replace instruction where we're inserting
}

void printSMSOErrorNotice(u32 *JUTConsole) {
	JUTConsole__print_f(JUTConsole, "HOOK SMSO GUI TO SUBMIT CRASH INFO TO SMSO TEAM!\n\n\n\n");
	__asm("lwz 5, 0x0060 (31)"); // replace instruction where we're inserting
}