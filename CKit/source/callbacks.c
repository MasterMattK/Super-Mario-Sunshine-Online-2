#include "defines.h"

void onGameLoad() {
	widescreen = *(int*)0x80416B74 == 0x3F9A7643;

	main();
}

void onStageLoad() {
	tag_onStageLoad();
	manhunt_onStageLoad();
}

void onStageExit() {

}