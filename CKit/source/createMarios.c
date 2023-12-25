// Special thanks to Brocoli, who wrote the code in this file aside from a few very small tweaks.
// This file is responsible for actually spawning in and setting up the multiple marios. The number of marios
// is determined by realpNum, which is defined in defines.h
#include "defines.h"

// these two things are defined here, but are made available to the other c files in defines.h
int pNum = 1;
u32********* marios[realpNum] = { [0 ... (realpNum-1)] = -1 };

int fNum = 1;

u32* makeMarios(u32* mario) {
	// this makes it so only 1 mario can spawn on file select
	char* bob = SDAword(-0x6048);	// pretty sure bob is the pointer for current level
	if (bob[0x7c] == 15) {
		pNum = 1;
	}
	else {
		pNum = realpNum;
	}

	// this gets the marios into the memory by allocating memory and branching to the init function (ct_Mario)
	ct_Mario(mario);
	marios[0] = mario;
	for (int i = 1; i < pNum; i++) {
		u32* m = alloc(0x4290);
		//xfbNews[i] = alloc(0xa5000);
		ct_Mario(m);
		marios[i] = m;
	}
	SDAstoreword(0x7000, &marios); // CCMarioPtrs
	return mario;
}

typedef struct {
	Node *prev;
	Node *next;
	u32 *data;
} Node;

// This is how mario is loaded through an input stream or something. I have to preserve it's neccesarry values to allow for multiple reads that are equivalent
void load_MarioTrickyOverhaul(u32* mario, u32* unk, u32* bleh1, u32* bleh2, Node *n) {
	for (int i = 1; i < pNum; i++) {
		Node *newNode = alloc(12);
		newNode->data = marios[i];
		newNode->next = n;
		newNode->prev = n->prev;
		n->prev->next = newNode;
		n->next->prev = newNode;
		n = newNode;
	}

	int a = unk[1], b = unk[3], c = unk[4];
	for (int i = 0; i < pNum; i++) {
		unk[1] = a;
		unk[3] = b;
		unk[4] = c;
		SDAstoreword(-0x60D8, marios[0]);
		load_MarioMFLR(marios[i], unk);
	}
	SDAstoreword(-0x60D8, marios[0]);
}

// I inject a branch straight into load_Mario so I have to manually do mflr r0
void __attribute__((noinline)) load_MarioMFLR(u32* mario, u32* unk) {
	__asm("mflr 0");
	__asm("b load_Mario");
}

u32* makeFruit(u32* fruit, char *unk) {
	initFruit(fruit, unk);

	// this makes it so no fruit will spawn on scene/option.szs
	char* currLevel = SDAword(-0x6048);
	if (currLevel[0x7c] == 1) {
		u32* f = alloc(0x1A8);
		initFruit(f, unk);
	}	

	return fruit;
}

void loadFruitOverhaul(u32* fruit, u32* unk, u32* bleh1, u32* bleh2, u32* gadgetNode)	// probably have to add a check for it it's a fruit or not... -0x8 from r3 should say "Fruit"
{
	// unk is memory input stream
	u32* susNode = gadgetNode[0]; // the gadget node would be the first input
	u32** newNode = alloc(12);
	newNode[2] = fruit; // the mario would be second input
	newNode[1] = gadgetNode;
	newNode[0] = susNode;
	susNode[1] = newNode;
	gadgetNode[0] = newNode;
	gadgetNode = newNode;

	int a = unk[1], b = unk[3], c = unk[4];
	unk[1] = a;
	unk[3] = b;
	unk[4] = c;
	SDAstoreword(-0x60D8, marios[0]);
	load_FruitMFLR(fruit, unk);

	SDAstoreword(-0x60D8, marios[0]);

}

// I inject a branch straight into load_Fruit so I have to manually do mflr r0
void __attribute__((noinline)) load_FruitMFLR(u32* fruit, u32* unk) {
	__asm("mflr 0");
	__asm("b load_Fruit");
}
