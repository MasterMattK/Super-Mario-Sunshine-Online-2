#include "defines.h"

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