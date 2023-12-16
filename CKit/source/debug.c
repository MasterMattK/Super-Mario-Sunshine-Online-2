#include "defines.h"

const u32 WHITE = 0xffffff88;
const u32 RED = 0xff0000ff;
const u32 PURPLE = 0xff00ffff;
const u32 GREEN = 0x00ff00fff;
const u32 GRAY = 0x777777ff;

static u32 gPrint[(0x90 / 4)] = { [0 ... 0x80 / 4] = 0xff0000ff };  // stuff for printing (thx brocoli)

void initPrint(u32* j2dprint, u32 color, int fontSize)
{
    u32* font = SDAword(-0x6038);
    if (font == 0) {
        font = SDAword(-0x6034);
    }
    ct_Print(j2dprint, font, 0);
    initiatePrint(j2dprint);
    gPrint[0x40 / 4] = color;
    gPrint[0x44 / 4] = color;
    // size
    gPrint[0x58 / 4] = 9*fontSize;
    gPrint[0x5c / 4] = 12*fontSize;
}

void initPrintDefaultSize(u32* j2dprint, u32 color)
{
    u32* font = SDAword(-0x6038);
    if (font == 0) {
        font = SDAword(-0x6034);
    }
    ct_Print(j2dprint, font, 0);
    initiatePrint(j2dprint);
    gPrint[0x40 / 4] = color;
    gPrint[0x44 / 4] = color;
}

void printString(char *s)
{
    initPrint(gPrint, GREEN, 2);
    printInternal(gPrint, 0, 100, "%s", s);
}

void printNumber(int n)
{
    initPrint(gPrint, GREEN, 2);
    printInternal(gPrint, 0, 100, "%d", n);
}