// Special thanks to Brocoli, who wrote the code in this file aside from a few very small tweaks.
// This file is responsible for actually spawning in and setting up the multiple marios. The number of marios
// is determined by realpNum, which is defined in defines.h
#include "defines.h"

// these two things are defined here, but are made available to the other c files in defines.h
int pNum = 1;
u32********* marios[realpNum] = { [0 ... (realpNum-1)] = -1 };
int* newMarioParams;

u32* makeMarios(u32* mario) {
	//newMarioParams = alloc(0x3d1c);
	//ct_MarioParams(newMarioParams);

	// this makes it so only 1 mario can spawn on file select
	char* bob = SDAword(-0x6048);
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

// This is how mario is loaded through an input stream or something. I have to preserve it's neccesarry values to allow for multiple reads that are equivalent
void load_MarioTrickyOverhaul(u32* mario, u32* unk, u32* bleh1, u32* bleh2, u32* gadgetNode) {
	// unk is memory input stream
	u32* susNode = gadgetNode[0]; // the gadget node would be the first input
	for (int i = 1; i < pNum; i++) {
		u32** newNode = alloc(12);
		newNode[2] = marios[i]; // the mario would be second input
		newNode[1] = gadgetNode;
		newNode[0] = susNode;
		susNode[1] = newNode;
		gadgetNode[0] = newNode;
		gadgetNode = newNode;
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

// replace gpThrowPower with a reference to newMarioParams
/*void replace_gpThrowPower() {
	SDAstoreword(-0x6090, newMarioParams + 0x2AC/4);
}*/

/*void ct_MarioParams(u32** this) {
	// the prm file path strings are gotten relative to one of these addresses
	char *prmStrBasePointer = 0x8039fe80;
	char *r2 = 0x80416ba0;

	TDeParams(this);

	// initialization of /Mario/BodyAngleFree.prm
	this[0x42c / 4] = prmStrBasePointer + 0x15a8;
	this[0x430 / 4] = 0;

	// initialization of /Mario/BodyAngleFree.prm : mHeadRot
	TBaseParam(this + 0x434/4, this + 0x42c/4, calcKeyCode(prmStrBasePointer + 0x121c), prmStrBasePointer + 0x121c);
	this[0x434 / 4] = 0x803abd30;
	this[0x444 / 4] = 0;

	// initialization of /Mario/BodyAngleFree.prm : mWaistRoll
	TBaseParam(this + 0x448/4, this + 0x42c/4, calcKeyCode(prmStrBasePointer + 0x188), prmStrBasePointer + 0x188);
	this[0x448 / 4] = 0x803abd30;
	this[0x458 / 4] = 0;

	// initialization of /Mario/BodyAngleFree.prm : mWaistPitch
	TBaseParam(this + 0x45c/4, this + 0x42c/4, calcKeyCode(prmStrBasePointer + 0x194), prmStrBasePointer + 0x194);
	this[0x45c / 4] = 0x803abd30;
	this[0x46c / 4] = 0;

	// initialization of /Mario/BodyAngleFree.prm : mWaistRollMax
	TBaseParam(this + 0x470/4, this + 0x42c/4, calcKeyCode(prmStrBasePointer + 0x1a0), prmStrBasePointer + 0x1a0);
	this[0x470 / 4] = 0x803ad0f0;
	this[0x480 / 4] = 0;

	// initialization of /Mario/BodyAngleFree.prm : mWaistPitchMax
	TBaseParam(this + 0x484/4, this + 0x42c/4, calcKeyCode(prmStrBasePointer + 0x1b0), prmStrBasePointer + 0x1b0);
	this[0x484 / 4] = 0x803ad0f0;
	this[0x494 / 4] = 0;

	// initialization of /Mario/BodyAngleFree.prm : mWaistAngleChangeRate
	TBaseParam(this + 0x498/4, this + 0x42c/4, calcKeyCode(prmStrBasePointer + 0x1ec), prmStrBasePointer + 0x1ec);
	this[0x498 / 4] = 0x803abd30;
	this[0x4a8 / 4] = 0;

	// loading of /Mario/BodyAngleFree.prm
	paramsLoad(this + 0x42c / 4, this[0x42c/4]);

	// initialization of /Mario/BodyAngleWaterGun.prm
	this[0x4ac / 4] = prmStrBasePointer + 0x15c4;
	this[0x4b0 / 4] = 0;

	// initialization of /Mario/BodyAngleWaterGun.prm : mHeadRot
	TBaseParam(this + 0x4b4/4, this + 0x4ac/4, calcKeyCode(prmStrBasePointer + 0x121c), prmStrBasePointer + 0x121c);
	this[0x4b4 / 4] = 0x803abd30;
	this[0x4c4 / 4] = 0;

	// initialization of /Mario/BodyAngleWaterGun.prm : mWaistRoll
	TBaseParam(this + 0x4c8/4, this + 0x4ac/4, calcKeyCode(prmStrBasePointer + 0x188), prmStrBasePointer + 0x188);
	this[0x4c8 / 4] = 0x803abd30;
	this[0x4d8 / 4] = 0;

	// initialization of /Mario/BodyAngleWaterGun.prm : mWaistPitch
	TBaseParam(this + 0x4dc/4, this + 0x4ac/4, calcKeyCode(prmStrBasePointer + 0x194), prmStrBasePointer + 0x194);
	this[0x4dc / 4] = 0x803abd30;
	this[0x4ec / 4] = 0;

	// initialization of /Mario/BodyAngleWaterGun.prm : mWaistRollMax
	TBaseParam(this + 0x4f0/4, this + 0x4ac/4, calcKeyCode(prmStrBasePointer + 0x1a0), prmStrBasePointer + 0x1a0);
	this[0x4f0 / 4] = 0x803ad0f0;
	this[0x500 / 4] = 0;

	// initialization of /Mario/BodyAngleWaterGun.prm : mWaistPitchMax
	TBaseParam(this + 0x504/4, this + 0x4ac/4, calcKeyCode(prmStrBasePointer + 0x1b0), prmStrBasePointer + 0x1b0);
	this[0x504 / 4] = 0x803ad0f0;
	this[0x514 / 4] = 0;

	// initialization of /Mario/BodyAngleWaterGun.prm : mWaistAngleChangeRate
	TBaseParam(this + 0x518/4, this + 0x4ac/4, calcKeyCode(prmStrBasePointer + 0x1ec), prmStrBasePointer + 0x1ec);
	this[0x518 / 4] = 0x803abd30;
	this[0x528 / 4] = 0;

	// loading of /Mario/BodyAngleWaterGun.prm
	paramsLoad(this + 0x4ac / 4, this[0x4ac/4]);

	// initialization of /Mario/AttackFencePunch.prm
	this[0x52c / 4] = prmStrBasePointer + 0x15e4;
	this[0x530 / 4] = 0;

	// initialization of /Mario/AttackFencePunch.prm : mRadius
	TBaseParam(this + 0x534/4, this + 0x52c/4, calcKeyCode(r2 - 0x8dc), r2 - 0x8dc);
	this[0x534 / 4] = 0x803abd30;
	this[0x544 / 4] = 0;

	// initialization of /Mario/AttackFencePunch.prm : mHeight
	TBaseParam(this + 0x548/4, this + 0x52c/4, calcKeyCode(r2 - 0x8d4), r2 - 0x8d4);
	this[0x548 / 4] = 0x803abd30;
	this[0x558 / 4] = 0;

	// loading of /Mario/AttackFencePunch.prm
	paramsLoad(this + 0x52c / 4, this[0x52c/4]);

	// initialization of /Mario/AttackKickRoof.prm
	this[0x55c / 4] = prmStrBasePointer + 0x1600;
	this[0x560 / 4] = 0;

	// initialization of /Mario/AttackKickRoof.prm : mRadius
	TBaseParam(this + 0x564/4, this + 0x55c/4, calcKeyCode(r2 - 0x8dc), r2 - 0x8dc);
	this[0x564 / 4] = 0x803abd30;
	this[0x574 / 4] = 0;

	// initialization of /Mario/AttackKickRoof.prm : mHeight
	TBaseParam(this + 0x578/4, this + 0x55c/4, calcKeyCode(r2 - 0x8d4), r2 - 0x8d4);
	this[0x578 / 4] = 0x803abd30;
	this[0x588 / 4] = 0;

	// loading of /Mario/AttackKickRoof.prm
	paramsLoad(this + 0x55c / 4, this[0x55c/4]);

	TJumpParams(this + 0x58C / 4);
	TRunParams(this + 0x92C / 4);
	TSwimParams(this + 0xAD8 / 4);

	// initialization of /Mario/Hanging.prm
	this[0xd24 / 4] = prmStrBasePointer + 0xbdc;
	this[0xd28 / 4] = 0;

	// initialization of /Mario/Hanging.prm : mMoveSp
	TBaseParam(this + 0xd2c/4, this + 0xd24/4, calcKeyCode(r2 - 0x938), r2 - 0x938);
	this[0xd2c / 4] = 0x803abd30;
	this[0xd3c / 4] = 0;

	// initialization of /Mario/Hanging.prm : mAnmRate
	TBaseParam(this + 0xd40/4, this + 0xd24/4, calcKeyCode(prmStrBasePointer + 0xbf0), prmStrBasePointer + 0xbf0);
	this[0xd40 / 4] = 0x803abd30;
	this[0xd50 / 4] = 0;

	// initialization of /Mario/Hanging.prm : mRapidTime
	TBaseParam(this + 0xd54/4, this + 0xd24/4, calcKeyCode(prmStrBasePointer + 0xbfc), prmStrBasePointer + 0xbfc);
	this[0xd54 / 4] = 0x803ad0f0;
	this[0xd64 / 4] = 0;

	// initialization of /Mario/Hanging.prm : mLimitTime
	TBaseParam(this + 0xd68/4, this + 0xd24/4, calcKeyCode(prmStrBasePointer + 0xc08), prmStrBasePointer + 0xc08);
	this[0xd68 / 4] = 0x803ad0f0;
	this[0xd78 / 4] = 0;

	// initialization of /Mario/Hanging.prm : mAnmRapid
	TBaseParam(this + 0xd7c/4, this + 0xd24/4, calcKeyCode(prmStrBasePointer + 0xc14), prmStrBasePointer + 0xc14);
	this[0xd7c / 4] = 0x803abd30;
	this[0xd8c / 4] = 0;

	// initialization of /Mario/Hanging.prm : mDescentSp
	TBaseParam(this + 0xd90/4, this + 0xd24/4, calcKeyCode(prmStrBasePointer + 0xc20), prmStrBasePointer + 0xc20);
	this[0xd90 / 4] = 0x803abd30;
	this[0xda0 / 4] = 0;

	// loading of /Mario/Hanging.prm
	paramsLoad(this + 0xd24 / 4, this[0xd24/4]);

	// initialization of /Mario/HangRoof.prm
	this[0xda4 / 4] = prmStrBasePointer + 0xbbc;
	this[0xda8 / 4] = 0;

	// initialization of /Mario/HangRoof.prm : mAnmMult
	TBaseParam(this + 0xdac/4, this + 0xda4/4, calcKeyCode(prmStrBasePointer + 0xbd0), prmStrBasePointer + 0xbd0);
	this[0xdac / 4] = 0x803abd30;
	this[0xdbc / 4] = 0;

	// loading of /Mario/HangRoof.prm
	paramsLoad(this + 0xda4 / 4, this[0xda4/4]);

	TWireParams(this + 0xDC0 / 4);

	// initialization of /Mario/PullParamBGBeak.prm
	this[0xf08 / 4] = prmStrBasePointer + 0x161c;
	this[0xf0c / 4] = 0;

	// initialization of /Mario/PullParamBGBeak.prm : mPullRateV
	TBaseParam(this + 0xf10/4, this + 0xf08/4, calcKeyCode(prmStrBasePointer + 0xa70), prmStrBasePointer + 0xa70);
	this[0xf10 / 4] = 0x803abd30;
	this[0xf20 / 4] = 0;

	// initialization of /Mario/PullParamBGBeak.prm : mPullRateH
	TBaseParam(this + 0xf24/4, this + 0xf08/4, calcKeyCode(prmStrBasePointer + 0xa7c), prmStrBasePointer + 0xa7c);
	this[0xf24 / 4] = 0x803abd30;
	this[0xf34 / 4] = 0;

	// initialization of /Mario/PullParamBGBeak.prm : mOilPullRateV
	TBaseParam(this + 0xf38/4, this + 0xf08/4, calcKeyCode(prmStrBasePointer + 0xa88), prmStrBasePointer + 0xa88);
	this[0xf38 / 4] = 0x803abd30;
	this[0xf48 / 4] = 0;

	// initialization of /Mario/PullParamBGBeak.prm : mOilPullRateH
	TBaseParam(this + 0xf4c/4, this + 0xf08/4, calcKeyCode(prmStrBasePointer + 0xa98), prmStrBasePointer + 0xa98);
	this[0xf4c / 4] = 0x803abd30;
	this[0xf5c / 4] = 0;

	// loading of /Mario/PullParamBGBeak.prm
	paramsLoad(this + 0xf08 / 4, this[0xf08/4]);

	// initialization of /Mario/PullParamBGTentacle.prm
	this[0xf60 / 4] = prmStrBasePointer + 0x1638;
	this[0xf64 / 4] = 0;

	// initialization of /Mario/PullParamBGTentacle.prm : mPullRateV
	TBaseParam(this + 0xf68/4, this + 0xf60/4, calcKeyCode(prmStrBasePointer + 0xa70), prmStrBasePointer + 0xa70);
	this[0xf68 / 4] = 0x803abd30;
	this[0xf78 / 4] = 0;

	// initialization of /Mario/PullParamBGTentacle.prm : mPullRateH
	TBaseParam(this + 0xf7c/4, this + 0xf60/4, calcKeyCode(prmStrBasePointer + 0xa7c), prmStrBasePointer + 0xa7c);
	this[0xf7c / 4] = 0x803abd30;
	this[0xf8c / 4] = 0;

	// initialization of /Mario/PullParamBGTentacle.prm : mOilPullRateV
	TBaseParam(this + 0xf90/4, this + 0xf60/4, calcKeyCode(prmStrBasePointer + 0xa88), prmStrBasePointer + 0xa88);
	this[0xf90 / 4] = 0x803abd30;
	this[0xfa0 / 4] = 0;

	// initialization of /Mario/PullParamBGTentacle.prm : mOilPullRateH
	TBaseParam(this + 0xfa4/4, this + 0xf60/4, calcKeyCode(prmStrBasePointer + 0xa98), prmStrBasePointer + 0xa98);
	this[0xfa4 / 4] = 0x803abd30;
	this[0xfb4 / 4] = 0;

	// loading of /Mario/PullParamBGTentacle.prm
	paramsLoad(this + 0xf60 / 4, this[0xf60/4]);

	// initialization of /Mario/PullParamBGFireWanWanBossTail.prm
	this[0xfb8 / 4] = prmStrBasePointer + 0x1658;
	this[0xfbc / 4] = 0;

	// initialization of /Mario/PullParamBGFireWanWanBossTail.prm : mPullRateV
	TBaseParam(this + 0xfc0/4, this + 0xfb8/4, calcKeyCode(prmStrBasePointer + 0xa70), prmStrBasePointer + 0xa70);
	this[0xfc0 / 4] = 0x803abd30;
	this[0xfd0 / 4] = 0;

	// initialization of /Mario/PullParamBGFireWanWanBossTail.prm : mPullRateH
	TBaseParam(this + 0xfd4/4, this + 0xfb8/4, calcKeyCode(prmStrBasePointer + 0xa7c), prmStrBasePointer + 0xa7c);
	this[0xfd4 / 4] = 0x803abd30;
	this[0xfe4 / 4] = 0;

	// initialization of /Mario/PullParamBGFireWanWanBossTail.prm : mOilPullRateV
	TBaseParam(this + 0xfe8/4, this + 0xfb8/4, calcKeyCode(prmStrBasePointer + 0xa88), prmStrBasePointer + 0xa88);
	this[0xfe8 / 4] = 0x803abd30;
	this[0xff8 / 4] = 0;

	// initialization of /Mario/PullParamBGFireWanWanBossTail.prm : mOilPullRateH
	TBaseParam(this + 0xffc/4, this + 0xfb8/4, calcKeyCode(prmStrBasePointer + 0xa98), prmStrBasePointer + 0xa98);
	this[0xffc / 4] = 0x803abd30;
	this[0x100c / 4] = 0;

	// loading of /Mario/PullParamBGFireWanWanBossTail.prm
	paramsLoad(this + 0xfb8 / 4, this[0xfb8/4]);

	// initialization of /Mario/PullParamFireWanWanTail.prm
	this[0x1010 / 4] = prmStrBasePointer + 0x1684;
	this[0x1014 / 4] = 0;

	// initialization of /Mario/PullParamFireWanWanTail.prm : mPullRateV
	TBaseParam(this + 0x1018/4, this + 0x1010/4, calcKeyCode(prmStrBasePointer + 0xa70), prmStrBasePointer + 0xa70);
	this[0x1018 / 4] = 0x803abd30;
	this[0x1028 / 4] = 0;

	// initialization of /Mario/PullParamFireWanWanTail.prm : mPullRateH
	TBaseParam(this + 0x102c/4, this + 0x1010/4, calcKeyCode(prmStrBasePointer + 0xa7c), prmStrBasePointer + 0xa7c);
	this[0x102c / 4] = 0x803abd30;
	this[0x103c / 4] = 0;

	// initialization of /Mario/PullParamFireWanWanTail.prm : mOilPullRateV
	TBaseParam(this + 0x1040/4, this + 0x1010/4, calcKeyCode(prmStrBasePointer + 0xa88), prmStrBasePointer + 0xa88);
	this[0x1040 / 4] = 0x803abd30;
	this[0x1050 / 4] = 0;

	// initialization of /Mario/PullParamFireWanWanTail.prm : mOilPullRateH
	TBaseParam(this + 0x1054/4, this + 0x1010/4, calcKeyCode(prmStrBasePointer + 0xa98), prmStrBasePointer + 0xa98);
	this[0x1054 / 4] = 0x803abd30;
	this[0x1064 / 4] = 0;

	// loading of /Mario/PullParamFireWanWanTail.prm
	paramsLoad(this + 0x1010 / 4, this[0x1010/4]);

	// initialization of /Mario/Bar.prm
	this[0x1068 / 4] = prmStrBasePointer + 0xa1c;
	this[0x106c / 4] = 0;

	// initialization of /Mario/Bar.prm : mClimbSp
	TBaseParam(this + 0x1070/4, this + 0x1068/4, calcKeyCode(prmStrBasePointer + 0xa2c), prmStrBasePointer + 0xa2c);
	this[0x1070 / 4] = 0x803abd30;
	this[0x1080 / 4] = 0;

	// initialization of /Mario/Bar.prm : mRotateSp
	TBaseParam(this + 0x1084/4, this + 0x1068/4, calcKeyCode(prmStrBasePointer + 0xa38), prmStrBasePointer + 0xa38);
	this[0x1084 / 4] = 0x803abd30;
	this[0x1094 / 4] = 0;

	// initialization of /Mario/Bar.prm : mClimbAnmRate
	TBaseParam(this + 0x1098/4, this + 0x1068/4, calcKeyCode(prmStrBasePointer + 0xa44), prmStrBasePointer + 0xa44);
	this[0x1098 / 4] = 0x803abd30;
	this[0x10a8 / 4] = 0;

	// initialization of /Mario/Bar.prm : mCatchRadius
	TBaseParam(this + 0x10ac/4, this + 0x1068/4, calcKeyCode(prmStrBasePointer + 0xa54), prmStrBasePointer + 0xa54);
	this[0x10ac / 4] = 0x803abd30;
	this[0x10bc / 4] = 0;

	// initialization of /Mario/Bar.prm : mCatchAngle
	TBaseParam(this + 0x10c0/4, this + 0x1068/4, calcKeyCode(prmStrBasePointer + 0xa64), prmStrBasePointer + 0xa64);
	this[0x10c0 / 4] = 0x803abd30;
	this[0x10d0 / 4] = 0;

	// loading of /Mario/Bar.prm
	paramsLoad(this + 0x1068 / 4, this[0x1068/4]);

	TSurfingParams(this + 0x10D4 / 4, prmStrBasePointer + 0x16a8);
	TSurfingParams(this + 0x12A8 / 4, prmStrBasePointer + 0x16c4);

	TSurfingParams(this + 0x147C / 4, prmStrBasePointer + 0x16e0);
	TSurfingParams(this + 0x1650 / 4, prmStrBasePointer + 0x1700);

	TSurfingParams(this + 0x1824 / 4, prmStrBasePointer + 0x1720);
	TSurfingParams(this + 0x19f8 / 4, prmStrBasePointer + 0x1740);

	// initialization of /Mario/HHover.prm
	this[0x1bcc / 4] = prmStrBasePointer + 0x1760;
	this[0x1bd0 / 4] = 0;

	// initialization of /Mario/HHover.prm : mRotSp
	TBaseParam(this + 0x1bd4/4, this + 0x1bcc/4, calcKeyCode(r2 - 0xa48), r2 - 0xa48);
	this[0x1bd4 / 4] = 0x803ad0f0;
	this[0x1be4 / 4] = 0;

	// initialization of /Mario/HHover.prm : mAccelRate
	TBaseParam(this + 0x1be8/4, this + 0x1bcc/4, calcKeyCode(prmStrBasePointer + 0x17c), prmStrBasePointer + 0x17c);
	this[0x1be8 / 4] = 0x803abd30;
	this[0x1bf8 / 4] = 0;

	// initialization of /Mario/HHover.prm : mBrake
	TBaseParam(this + 0x1bfc/4, this + 0x1bcc/4, calcKeyCode(r2 - 0xa2c), r2 - 0xa2c);
	this[0x1bfc / 4] = 0x803abd30;
	this[0x1c0c / 4] = 0;

	// loading of /Mario/HHover.prm
	paramsLoad(this + 0x1bcc / 4, this[0x1bcc/4]);

	// initialization of /Mario/Diving.prm
	this[0x1c10 / 4] = prmStrBasePointer + 0x1774;
	this[0x1c14 / 4] = 0;

	// initialization of /Mario/Diving.prm : mRotSp
	TBaseParam(this + 0x1c18/4, this + 0x1c10/4, calcKeyCode(r2 - 0xa48), r2 - 0xa48);
	this[0x1c18 / 4] = 0x803ad0f0;
	this[0x1c28 / 4] = 0;

	// initialization of /Mario/Diving.prm : mGravity
	TBaseParam(this + 0x1c2c/4, this + 0x1c10/4, calcKeyCode(prmStrBasePointer + 0x148), prmStrBasePointer + 0x148);
	this[0x1c2c / 4] = 0x803abd30;
	this[0x1c3c / 4] = 0;

	// initialization of /Mario/Diving.prm : mAccelControl
	TBaseParam(this + 0x1c40/4, this + 0x1c10/4, calcKeyCode(prmStrBasePointer + 0x154), prmStrBasePointer + 0x154);
	this[0x1c40 / 4] = 0x803abd30;
	this[0x1c50 / 4] = 0;

	// initialization of /Mario/Diving.prm : mSeaBrake
	TBaseParam(this + 0x1c54/4, this + 0x1c10/4, calcKeyCode(prmStrBasePointer + 0x164), prmStrBasePointer + 0x164);
	this[0x1c54 / 4] = 0x803abd30;
	this[0x1c64 / 4] = 0;

	// initialization of /Mario/Diving.prm : mSeaBrakeY
	TBaseParam(this + 0x1c68/4, this + 0x1c10/4, calcKeyCode(prmStrBasePointer + 0x170), prmStrBasePointer + 0x170);
	this[0x1c68 / 4] = 0x803abd30;
	this[0x1c78 / 4] = 0;

	// loading of /Mario/Diving.prm
	paramsLoad(this + 0x1c10 / 4, this[0x1c10/4]);

	// initialization of /Mario/Yoshi.prm
	this[0x1c7c / 4] = prmStrBasePointer + 0x8dc;
	this[0x1c80 / 4] = 0;

	// initialization of /Mario/Yoshi.prm : mRunYoshiMult
	TBaseParam(this + 0x1c84/4, this + 0x1c7c/4, calcKeyCode(prmStrBasePointer + 0x8f0), prmStrBasePointer + 0x8f0);
	this[0x1c84 / 4] = 0x803abd30;
	this[0x1c94 / 4] = 0;

	// initialization of /Mario/Yoshi.prm : mJumpYoshiMult
	TBaseParam(this + 0x1c98/4, this + 0x1c7c/4, calcKeyCode(prmStrBasePointer + 0x900), prmStrBasePointer + 0x900);
	this[0x1c98 / 4] = 0x803abd30;
	this[0x1ca8 / 4] = 0;

	// initialization of /Mario/Yoshi.prm : mRotYoshiMult
	TBaseParam(this + 0x1cac/4, this + 0x1c7c/4, calcKeyCode(prmStrBasePointer + 0x910), prmStrBasePointer + 0x910);
	this[0x1cac / 4] = 0x803abd30;
	this[0x1cbc / 4] = 0;

	// initialization of /Mario/Yoshi.prm : mHeadFront
	TBaseParam(this + 0x1cc0/4, this + 0x1c7c/4, calcKeyCode(prmStrBasePointer + 0x920), prmStrBasePointer + 0x920);
	this[0x1cc0 / 4] = 0x803abd30;
	this[0x1cd0 / 4] = 0;

	// initialization of /Mario/Yoshi.prm : mHeadRadius
	TBaseParam(this + 0x1cd4/4, this + 0x1c7c/4, calcKeyCode(prmStrBasePointer + 0x92c), prmStrBasePointer + 0x92c);
	this[0x1cd4 / 4] = 0x803abd30;
	this[0x1ce4 / 4] = 0;

	// initialization of /Mario/Yoshi.prm : mHoldOutAccCtrlF
	TBaseParam(this + 0x1ce8/4, this + 0x1c7c/4, calcKeyCode(prmStrBasePointer + 0x938), prmStrBasePointer + 0x938);
	this[0x1ce8 / 4] = 0x803abd30;
	this[0x1cf8 / 4] = 0;

	// initialization of /Mario/Yoshi.prm : mHoldOutAccCtrlB
	TBaseParam(this + 0x1cfc/4, this + 0x1c7c/4, calcKeyCode(prmStrBasePointer + 0x94c), prmStrBasePointer + 0x94c);
	this[0x1cfc / 4] = 0x803abd30;
	this[0x1d0c / 4] = 0;

	// initialization of /Mario/Yoshi.prm : mHoldOutSldCtrl
	TBaseParam(this + 0x1d10/4, this + 0x1c7c/4, calcKeyCode(prmStrBasePointer + 0x960), prmStrBasePointer + 0x960);
	this[0x1d10 / 4] = 0x803abd30;
	this[0x1d20 / 4] = 0;

	// initialization of /Mario/Yoshi.prm : mDecBrake
	TBaseParam(this + 0x1d24/4, this + 0x1c7c/4, calcKeyCode(prmStrBasePointer + 0x970), prmStrBasePointer + 0x970);
	this[0x1d24 / 4] = 0x803abd30;
	this[0x1d34 / 4] = 0;

	// loading of /Mario/Yoshi.prm
	paramsLoad(this + 0x1c7c / 4, this[0x1c7c/4]);

	// initialization of /Mario/WaterEffect.prm
	this[0x1d38 / 4] = prmStrBasePointer + 0x97c;
	this[0x1d3c / 4] = 0;

	// initialization of /Mario/WaterEffect.prm : mJumpIntoMdlEffectSpY
	TBaseParam(this + 0x1d40/4, this + 0x1d38/4, calcKeyCode(prmStrBasePointer + 0x994), prmStrBasePointer + 0x994);
	this[0x1d40 / 4] = 0x803abd30;
	this[0x1d50 / 4] = 0;

	// initialization of /Mario/WaterEffect.prm : mJumpIntoMinY
	TBaseParam(this + 0x1d54/4, this + 0x1d38/4, calcKeyCode(prmStrBasePointer + 0x9ac), prmStrBasePointer + 0x9ac);
	this[0x1d54 / 4] = 0x803abd30;
	this[0x1d64 / 4] = 0;

	// initialization of /Mario/WaterEffect.prm : mJumpIntoMaxY
	TBaseParam(this + 0x1d68/4, this + 0x1d38/4, calcKeyCode(prmStrBasePointer + 0x9bc), prmStrBasePointer + 0x9bc);
	this[0x1d68 / 4] = 0x803abd30;
	this[0x1d78 / 4] = 0;

	// initialization of /Mario/WaterEffect.prm : mJumpIntoScaleMin
	TBaseParam(this + 0x1d7c/4, this + 0x1d38/4, calcKeyCode(prmStrBasePointer + 0x9cc), prmStrBasePointer + 0x9cc);
	this[0x1d7c / 4] = 0x803abd30;
	this[0x1d8c / 4] = 0;

	// initialization of /Mario/WaterEffect.prm : mJumpIntoScaleWidth
	TBaseParam(this + 0x1d90/4, this + 0x1d38/4, calcKeyCode(prmStrBasePointer + 0x9e0), prmStrBasePointer + 0x9e0);
	this[0x1d90 / 4] = 0x803abd30;
	this[0x1da0 / 4] = 0;

	// initialization of /Mario/WaterEffect.prm : mRunningRippleSpeed
	TBaseParam(this + 0x1da4/4, this + 0x1d38/4, calcKeyCode(prmStrBasePointer + 0x9f4), prmStrBasePointer + 0x9f4);
	this[0x1da4 / 4] = 0x803abd30;
	this[0x1db4 / 4] = 0;

	// initialization of /Mario/WaterEffect.prm : mRunningRippleDepth
	TBaseParam(this + 0x1db8/4, this + 0x1d38/4, calcKeyCode(prmStrBasePointer + 0xa08), prmStrBasePointer + 0xa08);
	this[0x1db8 / 4] = 0x803abd30;
	this[0x1dc8 / 4] = 0;

	// loading of /Mario/WaterEffect.prm
	paramsLoad(this + 0x1d38 / 4, this[0x1d38/4]);

	// initialization of /Mario/Controller.prm
	this[0x1dcc / 4] = prmStrBasePointer + 0x7fc;
	this[0x1dd0 / 4] = 0;

	// initialization of /Mario/Controller.prm : mAnalogLRToZeroVal
	TBaseParam(this + 0x1dd4/4, this + 0x1dcc/4, calcKeyCode(prmStrBasePointer + 0x814), prmStrBasePointer + 0x814);
	this[0x1dd4 / 4] = 0x803ad0d8;
	this[0x1de4 / 4] = 0;

	// initialization of /Mario/Controller.prm : mAnalogLRToMiddleVal
	TBaseParam(this + 0x1de8/4, this + 0x1dcc/4, calcKeyCode(prmStrBasePointer + 0x828), prmStrBasePointer + 0x828);
	this[0x1de8 / 4] = 0x803ad0d8;
	this[0x1df8 / 4] = 0;

	// initialization of /Mario/Controller.prm : mAnalogLRToMaxVal
	TBaseParam(this + 0x1dfc/4, this + 0x1dcc/4, calcKeyCode(prmStrBasePointer + 0x840), prmStrBasePointer + 0x840);
	this[0x1dfc / 4] = 0x803ad0d8;
	this[0x1e0c / 4] = 0;

	// initialization of /Mario/Controller.prm : mAnalogLRMiddleLevel
	TBaseParam(this + 0x1e10/4, this + 0x1dcc/4, calcKeyCode(prmStrBasePointer + 0x854), prmStrBasePointer + 0x854);
	this[0x1e10 / 4] = 0x803abd30;
	this[0x1e20 / 4] = 0;

	// initialization of /Mario/Controller.prm : mStartToWalkLevel
	TBaseParam(this + 0x1e24/4, this + 0x1dcc/4, calcKeyCode(prmStrBasePointer + 0x86c), prmStrBasePointer + 0x86c);
	this[0x1e24 / 4] = 0x803abd30;
	this[0x1e34 / 4] = 0;

	// initialization of /Mario/Controller.prm : mStickRotateTime
	TBaseParam(this + 0x1e38/4, this + 0x1dcc/4, calcKeyCode(prmStrBasePointer + 0x880), prmStrBasePointer + 0x880);
	this[0x1e38 / 4] = 0x803ad0f0;
	this[0x1e48 / 4] = 0;

	// initialization of /Mario/Controller.prm : mLengthMultTimes
	TBaseParam(this + 0x1e4c/4, this + 0x1dcc/4, calcKeyCode(prmStrBasePointer + 0x894), prmStrBasePointer + 0x894);
	this[0x1e4c / 4] = 0x803ad0f0;
	this[0x1e5c / 4] = 0;

	// initialization of /Mario/Controller.prm : mLengthMult
	TBaseParam(this + 0x1e60/4, this + 0x1dcc/4, calcKeyCode(prmStrBasePointer + 0x8a8), prmStrBasePointer + 0x8a8);
	this[0x1e60 / 4] = 0x803abd30;
	this[0x1e70 / 4] = 0;

	// initialization of /Mario/Controller.prm : mSquatRotMidAnalog
	TBaseParam(this + 0x1e74/4, this + 0x1dcc/4, calcKeyCode(prmStrBasePointer + 0x8b4), prmStrBasePointer + 0x8b4);
	this[0x1e74 / 4] = 0x803abd30;
	this[0x1e84 / 4] = 0;

	// initialization of /Mario/Controller.prm : mSquatRotMidValue
	TBaseParam(this + 0x1e88/4, this + 0x1dcc/4, calcKeyCode(prmStrBasePointer + 0x8c8), prmStrBasePointer + 0x8c8);
	this[0x1e88 / 4] = 0x803abd30;
	this[0x1e98 / 4] = 0;

	// loading of /Mario/Controller.prm
	paramsLoad(this + 0x1dcc / 4, this[0x1dcc/4]);

	TGraffitoParams(this + 0x1E9C / 4);
	TDirtyParams(this + 0x2048 / 4);

	// initialization of /Mario/MarioMotor.prm
	this[0x2230 / 4] = prmStrBasePointer + 0x4c0;
	this[0x2234 / 4] = 0;

	// initialization of /Mario/MarioMotor.prm : mMotorReturn
	TBaseParam(this + 0x2238/4, this + 0x2230/4, calcKeyCode(prmStrBasePointer + 0x4d8), prmStrBasePointer + 0x4d8);
	this[0x2238 / 4] = 0x803ad0f0;
	this[0x2248 / 4] = 0;

	// initialization of /Mario/MarioMotor.prm : mMotorTrample
	TBaseParam(this + 0x224c/4, this + 0x2230/4, calcKeyCode(prmStrBasePointer + 0x4e8), prmStrBasePointer + 0x4e8);
	this[0x224c / 4] = 0x803ad0f0;
	this[0x225c / 4] = 0;

	// initialization of /Mario/MarioMotor.prm : mMotorHipDrop
	TBaseParam(this + 0x2260/4, this + 0x2230/4, calcKeyCode(prmStrBasePointer + 0x4f8), prmStrBasePointer + 0x4f8);
	this[0x2260 / 4] = 0x803ad0f0;
	this[0x2270 / 4] = 0;

	// initialization of /Mario/MarioMotor.prm : mMotorWall
	TBaseParam(this + 0x2274/4, this + 0x2230/4, calcKeyCode(prmStrBasePointer + 0x508), prmStrBasePointer + 0x508);
	this[0x2274 / 4] = 0x803ad0f0;
	this[0x2284 / 4] = 0;

	// loading of /Mario/MarioMotor.prm
	paramsLoad(this + 0x2230 / 4, this[0x2230/4]);

	// initialization of /Mario/MarioParticle.prm
	this[0x2288 / 4] = prmStrBasePointer + 0x3e4;
	this[0x228c / 4] = 0;

	// initialization of /Mario/MarioParticle.prm : mMeltInWaterMax
	TBaseParam(this + 0x2290/4, this + 0x2288/4, calcKeyCode(prmStrBasePointer + 0x400), prmStrBasePointer + 0x400);
	this[0x2290 / 4] = 0x803abd30;
	this[0x22a0 / 4] = 0;

	// initialization of /Mario/MarioParticle.prm : mWaveEmitSpeed
	TBaseParam(this + 0x22a4/4, this + 0x2288/4, calcKeyCode(prmStrBasePointer + 0x410), prmStrBasePointer + 0x410);
	this[0x22a4 / 4] = 0x803abd30;
	this[0x22b4 / 4] = 0;

	// initialization of /Mario/MarioParticle.prm : mWaveAlphaDec
	TBaseParam(this + 0x22b8/4, this + 0x2288/4, calcKeyCode(prmStrBasePointer + 0x420), prmStrBasePointer + 0x420);
	this[0x22b8 / 4] = 0x803ad0f0;
	this[0x22c8 / 4] = 0;

	// initialization of /Mario/MarioParticle.prm : mBubbleDepth
	TBaseParam(this + 0x22cc/4, this + 0x2288/4, calcKeyCode(prmStrBasePointer + 0x430), prmStrBasePointer + 0x430);
	this[0x22cc / 4] = 0x803abd30;
	this[0x22dc / 4] = 0;

	// initialization of /Mario/MarioParticle.prm : mBodyBubbleSpMin
	TBaseParam(this + 0x22e0/4, this + 0x2288/4, calcKeyCode(prmStrBasePointer + 0x440), prmStrBasePointer + 0x440);
	this[0x22e0 / 4] = 0x803abd30;
	this[0x22f0 / 4] = 0;

	// initialization of /Mario/MarioParticle.prm : mBodyBubbleSpMax
	TBaseParam(this + 0x22f4/4, this + 0x2288/4, calcKeyCode(prmStrBasePointer + 0x454), prmStrBasePointer + 0x454);
	this[0x22f4 / 4] = 0x803abd30;
	this[0x2304 / 4] = 0;

	// initialization of /Mario/MarioParticle.prm : mBodyBubbleEmitMin
	TBaseParam(this + 0x2308/4, this + 0x2288/4, calcKeyCode(prmStrBasePointer + 0x468), prmStrBasePointer + 0x468);
	this[0x2308 / 4] = 0x803abd30;
	this[0x2318 / 4] = 0;

	// initialization of /Mario/MarioParticle.prm : mBodyBubbleEmitMax
	TBaseParam(this + 0x231c/4, this + 0x2288/4, calcKeyCode(prmStrBasePointer + 0x47c), prmStrBasePointer + 0x47c);
	this[0x231c / 4] = 0x803abd30;
	this[0x232c / 4] = 0;

	// initialization of /Mario/MarioParticle.prm : mBubbleToRipple
	TBaseParam(this + 0x2330/4, this + 0x2288/4, calcKeyCode(prmStrBasePointer + 0x490), prmStrBasePointer + 0x490);
	this[0x2330 / 4] = 0x803abd30;
	this[0x2340 / 4] = 0;

	// initialization of /Mario/MarioParticle.prm : mToroccoWind
	TBaseParam(this + 0x2344/4, this + 0x2288/4, calcKeyCode(prmStrBasePointer + 0x4a0), prmStrBasePointer + 0x4a0);
	this[0x2344 / 4] = 0x803abd30;
	this[0x2354 / 4] = 0;

	// initialization of /Mario/MarioParticle.prm : mToroccoSpark
	TBaseParam(this + 0x2358/4, this + 0x2288/4, calcKeyCode(prmStrBasePointer + 0x4b0), prmStrBasePointer + 0x4b0);
	this[0x2358 / 4] = 0x803abd30;
	this[0x2368 / 4] = 0;

	// loading of /Mario/MarioParticle.prm
	paramsLoad(this + 0x2288 / 4, this[0x2288/4]);

	// initialization of /Mario/MarioEffect.prm
	this[0x236c / 4] = prmStrBasePointer + 0x37c;
	this[0x2370 / 4] = 0;

	// initialization of /Mario/MarioEffect.prm : mDashInc
	TBaseParam(this + 0x2374/4, this + 0x236c/4, calcKeyCode(prmStrBasePointer + 0x394), prmStrBasePointer + 0x394);
	this[0x2374 / 4] = 0x803abd30;
	this[0x2384 / 4] = 0;

	// initialization of /Mario/MarioEffect.prm : mDashDec
	TBaseParam(this + 0x2388/4, this + 0x236c/4, calcKeyCode(prmStrBasePointer + 0x3a0), prmStrBasePointer + 0x3a0);
	this[0x2388 / 4] = 0x803abd30;
	this[0x2398 / 4] = 0;

	// initialization of /Mario/MarioEffect.prm : mDashMaxBlendInBlur
	TBaseParam(this + 0x239c/4, this + 0x236c/4, calcKeyCode(prmStrBasePointer + 0x3ac), prmStrBasePointer + 0x3ac);
	this[0x239c / 4] = 0x803ad0d8;
	this[0x23ac / 4] = 0;

	// initialization of /Mario/MarioEffect.prm : mDashMaxBlendInIris
	TBaseParam(this + 0x23b0/4, this + 0x236c/4, calcKeyCode(prmStrBasePointer + 0x3c0), prmStrBasePointer + 0x3c0);
	this[0x23b0 / 4] = 0x803ad0d8;
	this[0x23c0 / 4] = 0;

	// initialization of /Mario/MarioEffect.prm : mDashBlendScale
	TBaseParam(this + 0x23c4/4, this + 0x236c/4, calcKeyCode(prmStrBasePointer + 0x3d4), prmStrBasePointer + 0x3d4);
	this[0x23c4 / 4] = 0x803abd30;
	this[0x23d4 / 4] = 0;

	// loading of /Mario/MarioEffect.prm
	paramsLoad(this + 0x236c / 4, this[0x236c/4]);

	// initialization of /Mario/SlipParamNormal.prm
	this[0x23d8 / 4] = prmStrBasePointer + 0x1788;
	this[0x23dc / 4] = 0;

	// initialization of /Mario/SlipParamNormal.prm : mSlipFriction
	TBaseParam(this + 0x23e0/4, this + 0x23d8/4, calcKeyCode(prmStrBasePointer + 0x2c8), prmStrBasePointer + 0x2c8);
	this[0x23e0 / 4] = 0x803abd30;
	this[0x23f0 / 4] = 0;

	// initialization of /Mario/SlipParamNormal.prm : mSlopeAcceleUp
	TBaseParam(this + 0x23f4/4, this + 0x23d8/4, calcKeyCode(prmStrBasePointer + 0x2d8), prmStrBasePointer + 0x2d8);
	this[0x23f4 / 4] = 0x803abd30;
	this[0x2404 / 4] = 0;

	// initialization of /Mario/SlipParamNormal.prm : mSlopeAcceleDown
	TBaseParam(this + 0x2408/4, this + 0x23d8/4, calcKeyCode(prmStrBasePointer + 0x2e8), prmStrBasePointer + 0x2e8);
	this[0x2408 / 4] = 0x803abd30;
	this[0x2418 / 4] = 0;

	// initialization of /Mario/SlipParamNormal.prm : mSlideAcceleUp
	TBaseParam(this + 0x241c/4, this + 0x23d8/4, calcKeyCode(prmStrBasePointer + 0x2fc), prmStrBasePointer + 0x2fc);
	this[0x241c / 4] = 0x803abd30;
	this[0x242c / 4] = 0;

	// initialization of /Mario/SlipParamNormal.prm : mSlideAcceleDown
	TBaseParam(this + 0x2430/4, this + 0x23d8/4, calcKeyCode(prmStrBasePointer + 0x30c), prmStrBasePointer + 0x30c);
	this[0x2430 / 4] = 0x803abd30;
	this[0x2440 / 4] = 0;

	// initialization of /Mario/SlipParamNormal.prm : mSlideStopNormal
	TBaseParam(this + 0x2444/4, this + 0x23d8/4, calcKeyCode(prmStrBasePointer + 0x320), prmStrBasePointer + 0x320);
	this[0x2444 / 4] = 0x803abd30;
	this[0x2454 / 4] = 0;

	// initialization of /Mario/SlipParamNormal.prm : mSlideStopCatch
	TBaseParam(this + 0x2458/4, this + 0x23d8/4, calcKeyCode(prmStrBasePointer + 0x334), prmStrBasePointer + 0x334);
	this[0x2458 / 4] = 0x803abd30;
	this[0x2468 / 4] = 0;

	// initialization of /Mario/SlipParamNormal.prm : mJumpEnable
	TBaseParam(this + 0x246c/4, this + 0x23d8/4, calcKeyCode(prmStrBasePointer + 0x344), prmStrBasePointer + 0x344);
	this[0x246c / 4] = 0x803ad0d8;
	this[0x247c / 4] = 0;

	// initialization of /Mario/SlipParamNormal.prm : mMissJump
	TBaseParam(this + 0x2480/4, this + 0x23d8/4, calcKeyCode(prmStrBasePointer + 0x350), prmStrBasePointer + 0x350);
	this[0x2480 / 4] = 0x803ad0d8;
	this[0x2490 / 4] = 0;

	// initialization of /Mario/SlipParamNormal.prm : mSlideAngleYSp
	TBaseParam(this + 0x2494/4, this + 0x23d8/4, calcKeyCode(prmStrBasePointer + 0x35c), prmStrBasePointer + 0x35c);
	this[0x2494 / 4] = 0x803ad0f0;
	this[0x24a4 / 4] = 0;

	// initialization of /Mario/SlipParamNormal.prm : mStickSlideMult
	TBaseParam(this + 0x24a8/4, this + 0x23d8/4, calcKeyCode(prmStrBasePointer + 0x36c), prmStrBasePointer + 0x36c);
	this[0x24a8 / 4] = 0x803abd30;
	this[0x24b8 / 4] = 0;

	// loading of /Mario/SlipParamNormal.prm
	paramsLoad(this + 0x23d8 / 4, this[0x23d8/4]);

	// initialization of /Mario/SlipParamOil.prm
	this[0x24bc / 4] = prmStrBasePointer + 0x17a4;
	this[0x24c0 / 4] = 0;

	// initialization of /Mario/SlipParamOil.prm : mSlipFriction
	TBaseParam(this + 0x24c4/4, this + 0x24bc/4, calcKeyCode(prmStrBasePointer + 0x2c8), prmStrBasePointer + 0x2c8);
	this[0x24c4 / 4] = 0x803abd30;
	this[0x24d4 / 4] = 0;

	// initialization of /Mario/SlipParamOil.prm : mSlopeAcceleUp
	TBaseParam(this + 0x24d8/4, this + 0x24bc/4, calcKeyCode(prmStrBasePointer + 0x2d8), prmStrBasePointer + 0x2d8);
	this[0x24d8 / 4] = 0x803abd30;
	this[0x24e8 / 4] = 0;

	// initialization of /Mario/SlipParamOil.prm : mSlopeAcceleDown
	TBaseParam(this + 0x24ec/4, this + 0x24bc/4, calcKeyCode(prmStrBasePointer + 0x2e8), prmStrBasePointer + 0x2e8);
	this[0x24ec / 4] = 0x803abd30;
	this[0x24fc / 4] = 0;

	// initialization of /Mario/SlipParamOil.prm : mSlideAcceleUp
	TBaseParam(this + 0x2500/4, this + 0x24bc/4, calcKeyCode(prmStrBasePointer + 0x2fc), prmStrBasePointer + 0x2fc);
	this[0x2500 / 4] = 0x803abd30;
	this[0x2510 / 4] = 0;

	// initialization of /Mario/SlipParamOil.prm : mSlideAcceleDown
	TBaseParam(this + 0x2514/4, this + 0x24bc/4, calcKeyCode(prmStrBasePointer + 0x30c), prmStrBasePointer + 0x30c);
	this[0x2514 / 4] = 0x803abd30;
	this[0x2524 / 4] = 0;

	// initialization of /Mario/SlipParamOil.prm : mSlideStopNormal
	TBaseParam(this + 0x2528/4, this + 0x24bc/4, calcKeyCode(prmStrBasePointer + 0x320), prmStrBasePointer + 0x320);
	this[0x2528 / 4] = 0x803abd30;
	this[0x2538 / 4] = 0;

	// initialization of /Mario/SlipParamOil.prm : mSlideStopCatch
	TBaseParam(this + 0x253c/4, this + 0x24bc/4, calcKeyCode(prmStrBasePointer + 0x334), prmStrBasePointer + 0x334);
	this[0x253c / 4] = 0x803abd30;
	this[0x254c / 4] = 0;

	// initialization of /Mario/SlipParamOil.prm : mJumpEnable
	TBaseParam(this + 0x2550/4, this + 0x24bc/4, calcKeyCode(prmStrBasePointer + 0x344), prmStrBasePointer + 0x344);
	this[0x2550 / 4] = 0x803ad0d8;
	this[0x2560 / 4] = 0;

	// initialization of /Mario/SlipParamOil.prm : mMissJump
	TBaseParam(this + 0x2564/4, this + 0x24bc/4, calcKeyCode(prmStrBasePointer + 0x350), prmStrBasePointer + 0x350);
	this[0x2564 / 4] = 0x803ad0d8;
	this[0x2574 / 4] = 0;

	// initialization of /Mario/SlipParamOil.prm : mSlideAngleYSp
	TBaseParam(this + 0x2578/4, this + 0x24bc/4, calcKeyCode(prmStrBasePointer + 0x35c), prmStrBasePointer + 0x35c);
	this[0x2578 / 4] = 0x803ad0f0;
	this[0x2588 / 4] = 0;

	// initialization of /Mario/SlipParamOil.prm : mStickSlideMult
	TBaseParam(this + 0x258c/4, this + 0x24bc/4, calcKeyCode(prmStrBasePointer + 0x36c), prmStrBasePointer + 0x36c);
	this[0x258c / 4] = 0x803abd30;
	this[0x259c / 4] = 0;

	// loading of /Mario/SlipParamOil.prm
	paramsLoad(this + 0x24bc / 4, this[0x24bc/4]);

	// initialization of /Mario/SlipParamAll.prm
	this[0x25a0 / 4] = prmStrBasePointer + 0x17bc;
	this[0x25a4 / 4] = 0;

	// initialization of /Mario/SlipParamAll.prm : mSlipFriction
	TBaseParam(this + 0x25a8/4, this + 0x25a0/4, calcKeyCode(prmStrBasePointer + 0x2c8), prmStrBasePointer + 0x2c8);
	this[0x25a8 / 4] = 0x803abd30;
	this[0x25b8 / 4] = 0;

	// initialization of /Mario/SlipParamAll.prm : mSlopeAcceleUp
	TBaseParam(this + 0x25bc/4, this + 0x25a0/4, calcKeyCode(prmStrBasePointer + 0x2d8), prmStrBasePointer + 0x2d8);
	this[0x25bc / 4] = 0x803abd30;
	this[0x25cc / 4] = 0;

	// initialization of /Mario/SlipParamAll.prm : mSlopeAcceleDown
	TBaseParam(this + 0x25d0/4, this + 0x25a0/4, calcKeyCode(prmStrBasePointer + 0x2e8), prmStrBasePointer + 0x2e8);
	this[0x25d0 / 4] = 0x803abd30;
	this[0x25e0 / 4] = 0;

	// initialization of /Mario/SlipParamAll.prm : mSlideAcceleUp
	TBaseParam(this + 0x25e4/4, this + 0x25a0/4, calcKeyCode(prmStrBasePointer + 0x2fc), prmStrBasePointer + 0x2fc);
	this[0x25e4 / 4] = 0x803abd30;
	this[0x25f4 / 4] = 0;

	// initialization of /Mario/SlipParamAll.prm : mSlideAcceleDown
	TBaseParam(this + 0x25f8/4, this + 0x25a0/4, calcKeyCode(prmStrBasePointer + 0x30c), prmStrBasePointer + 0x30c);
	this[0x25f8 / 4] = 0x803abd30;
	this[0x2608 / 4] = 0;

	// initialization of /Mario/SlipParamAll.prm : mSlideStopNormal
	TBaseParam(this + 0x260c/4, this + 0x25a0/4, calcKeyCode(prmStrBasePointer + 0x320), prmStrBasePointer + 0x320);
	this[0x260c / 4] = 0x803abd30;
	this[0x261c / 4] = 0;

	// initialization of /Mario/SlipParamAll.prm : mSlideStopCatch
	TBaseParam(this + 0x2620/4, this + 0x25a0/4, calcKeyCode(prmStrBasePointer + 0x334), prmStrBasePointer + 0x334);
	this[0x2620 / 4] = 0x803abd30;
	this[0x2630 / 4] = 0;

	// initialization of /Mario/SlipParamAll.prm : mJumpEnable
	TBaseParam(this + 0x2634/4, this + 0x25a0/4, calcKeyCode(prmStrBasePointer + 0x344), prmStrBasePointer + 0x344);
	this[0x2634 / 4] = 0x803ad0d8;
	this[0x2644 / 4] = 0;

	// initialization of /Mario/SlipParamAll.prm : mMissJump
	TBaseParam(this + 0x2648/4, this + 0x25a0/4, calcKeyCode(prmStrBasePointer + 0x350), prmStrBasePointer + 0x350);
	this[0x2648 / 4] = 0x803ad0d8;
	this[0x2658 / 4] = 0;

	// initialization of /Mario/SlipParamAll.prm : mSlideAngleYSp
	TBaseParam(this + 0x265c/4, this + 0x25a0/4, calcKeyCode(prmStrBasePointer + 0x35c), prmStrBasePointer + 0x35c);
	this[0x265c / 4] = 0x803ad0f0;
	this[0x266c / 4] = 0;

	// initialization of /Mario/SlipParamAll.prm : mStickSlideMult
	TBaseParam(this + 0x2670/4, this + 0x25a0/4, calcKeyCode(prmStrBasePointer + 0x36c), prmStrBasePointer + 0x36c);
	this[0x2670 / 4] = 0x803abd30;
	this[0x2680 / 4] = 0;

	// loading of /Mario/SlipParamAll.prm
	paramsLoad(this + 0x25a0 / 4, this[0x25a0/4]);

	// initialization of /Mario/SlipParamAll_Slider.prm
	this[0x2684 / 4] = prmStrBasePointer + 0x17d4;
	this[0x2688 / 4] = 0;

	// initialization of /Mario/SlipParamAll_Slider.prm : mSlipFriction
	TBaseParam(this + 0x268c/4, this + 0x2684/4, calcKeyCode(prmStrBasePointer + 0x2c8), prmStrBasePointer + 0x2c8);
	this[0x268c / 4] = 0x803abd30;
	this[0x269c / 4] = 0;

	// initialization of /Mario/SlipParamAll_Slider.prm : mSlopeAcceleUp
	TBaseParam(this + 0x26a0/4, this + 0x2684/4, calcKeyCode(prmStrBasePointer + 0x2d8), prmStrBasePointer + 0x2d8);
	this[0x26a0 / 4] = 0x803abd30;
	this[0x26b0 / 4] = 0;

	// initialization of /Mario/SlipParamAll_Slider.prm : mSlopeAcceleDown
	TBaseParam(this + 0x26b4/4, this + 0x2684/4, calcKeyCode(prmStrBasePointer + 0x2e8), prmStrBasePointer + 0x2e8);
	this[0x26b4 / 4] = 0x803abd30;
	this[0x26c4 / 4] = 0;

	// initialization of /Mario/SlipParamAll_Slider.prm : mSlideAcceleUp
	TBaseParam(this + 0x26c8/4, this + 0x2684/4, calcKeyCode(prmStrBasePointer + 0x2fc), prmStrBasePointer + 0x2fc);
	this[0x26c8 / 4] = 0x803abd30;
	this[0x26d8 / 4] = 0;

	// initialization of /Mario/SlipParamAll_Slider.prm : mSlideAcceleDown
	TBaseParam(this + 0x26dc/4, this + 0x2684/4, calcKeyCode(prmStrBasePointer + 0x30c), prmStrBasePointer + 0x30c);
	this[0x26dc / 4] = 0x803abd30;
	this[0x26ec / 4] = 0;

	// initialization of /Mario/SlipParamAll_Slider.prm : mSlideStopNormal
	TBaseParam(this + 0x26f0/4, this + 0x2684/4, calcKeyCode(prmStrBasePointer + 0x320), prmStrBasePointer + 0x320);
	this[0x26f0 / 4] = 0x803abd30;
	this[0x2700 / 4] = 0;

	// initialization of /Mario/SlipParamAll_Slider.prm : mSlideStopCatch
	TBaseParam(this + 0x2704/4, this + 0x2684/4, calcKeyCode(prmStrBasePointer + 0x334), prmStrBasePointer + 0x334);
	this[0x2704 / 4] = 0x803abd30;
	this[0x2714 / 4] = 0;

	// initialization of /Mario/SlipParamAll_Slider.prm : mJumpEnable
	TBaseParam(this + 0x2718/4, this + 0x2684/4, calcKeyCode(prmStrBasePointer + 0x344), prmStrBasePointer + 0x344);
	this[0x2718 / 4] = 0x803ad0d8;
	this[0x2728 / 4] = 0;

	// initialization of /Mario/SlipParamAll_Slider.prm : mMissJump
	TBaseParam(this + 0x272c/4, this + 0x2684/4, calcKeyCode(prmStrBasePointer + 0x350), prmStrBasePointer + 0x350);
	this[0x272c / 4] = 0x803ad0d8;
	this[0x273c / 4] = 0;

	// initialization of /Mario/SlipParamAll_Slider.prm : mSlideAngleYSp
	TBaseParam(this + 0x2740/4, this + 0x2684/4, calcKeyCode(prmStrBasePointer + 0x35c), prmStrBasePointer + 0x35c);
	this[0x2740 / 4] = 0x803ad0f0;
	this[0x2750 / 4] = 0;

	// initialization of /Mario/SlipParamAll_Slider.prm : mStickSlideMult
	TBaseParam(this + 0x2754/4, this + 0x2684/4, calcKeyCode(prmStrBasePointer + 0x36c), prmStrBasePointer + 0x36c);
	this[0x2754 / 4] = 0x803abd30;
	this[0x2764 / 4] = 0;

	// loading of /Mario/SlipParamAll_Slider.prm
	paramsLoad(this + 0x2684 / 4, this[0x2684/4]);

	// initialization of /Mario/SlipParam45.prm
	this[0x2768 / 4] = prmStrBasePointer + 0x17f4;
	this[0x276c / 4] = 0;

	// initialization of /Mario/SlipParam45.prm : mSlipFriction
	TBaseParam(this + 0x2770/4, this + 0x2768/4, calcKeyCode(prmStrBasePointer + 0x2c8), prmStrBasePointer + 0x2c8);
	this[0x2770 / 4] = 0x803abd30;
	this[0x2780 / 4] = 0;

	// initialization of /Mario/SlipParam45.prm : mSlopeAcceleUp
	TBaseParam(this + 0x2784/4, this + 0x2768/4, calcKeyCode(prmStrBasePointer + 0x2d8), prmStrBasePointer + 0x2d8);
	this[0x2784 / 4] = 0x803abd30;
	this[0x2794 / 4] = 0;

	// initialization of /Mario/SlipParam45.prm : mSlopeAcceleDown
	TBaseParam(this + 0x2798/4, this + 0x2768/4, calcKeyCode(prmStrBasePointer + 0x2e8), prmStrBasePointer + 0x2e8);
	this[0x2798 / 4] = 0x803abd30;
	this[0x27a8 / 4] = 0;

	// initialization of /Mario/SlipParam45.prm : mSlideAcceleUp
	TBaseParam(this + 0x27ac/4, this + 0x2768/4, calcKeyCode(prmStrBasePointer + 0x2fc), prmStrBasePointer + 0x2fc);
	this[0x27ac / 4] = 0x803abd30;
	this[0x27bc / 4] = 0;

	// initialization of /Mario/SlipParam45.prm : mSlideAcceleDown
	TBaseParam(this + 0x27c0/4, this + 0x2768/4, calcKeyCode(prmStrBasePointer + 0x30c), prmStrBasePointer + 0x30c);
	this[0x27c0 / 4] = 0x803abd30;
	this[0x27d0 / 4] = 0;

	// initialization of /Mario/SlipParam45.prm : mSlideStopNormal
	TBaseParam(this + 0x27d4/4, this + 0x2768/4, calcKeyCode(prmStrBasePointer + 0x320), prmStrBasePointer + 0x320);
	this[0x27d4 / 4] = 0x803abd30;
	this[0x27e4 / 4] = 0;

	// initialization of /Mario/SlipParam45.prm : mSlideStopCatch
	TBaseParam(this + 0x27e8/4, this + 0x2768/4, calcKeyCode(prmStrBasePointer + 0x334), prmStrBasePointer + 0x334);
	this[0x27e8 / 4] = 0x803abd30;
	this[0x27f8 / 4] = 0;

	// initialization of /Mario/SlipParam45.prm : mJumpEnable
	TBaseParam(this + 0x27fc/4, this + 0x2768/4, calcKeyCode(prmStrBasePointer + 0x344), prmStrBasePointer + 0x344);
	this[0x27fc / 4] = 0x803ad0d8;
	this[0x280c / 4] = 0;

	// initialization of /Mario/SlipParam45.prm : mMissJump
	TBaseParam(this + 0x2810/4, this + 0x2768/4, calcKeyCode(prmStrBasePointer + 0x350), prmStrBasePointer + 0x350);
	this[0x2810 / 4] = 0x803ad0d8;
	this[0x2820 / 4] = 0;

	// initialization of /Mario/SlipParam45.prm : mSlideAngleYSp
	TBaseParam(this + 0x2824/4, this + 0x2768/4, calcKeyCode(prmStrBasePointer + 0x35c), prmStrBasePointer + 0x35c);
	this[0x2824 / 4] = 0x803ad0f0;
	this[0x2834 / 4] = 0;

	// initialization of /Mario/SlipParam45.prm : mStickSlideMult
	TBaseParam(this + 0x2838/4, this + 0x2768/4, calcKeyCode(prmStrBasePointer + 0x36c), prmStrBasePointer + 0x36c);
	this[0x2838 / 4] = 0x803abd30;
	this[0x2848 / 4] = 0;

	// loading of /Mario/SlipParam45.prm
	paramsLoad(this + 0x2768 / 4, this[0x2768/4]);

	// initialization of /Mario/SlipParamWaterSlope.prm
	this[0x284c / 4] = prmStrBasePointer + 0x180c;
	this[0x2850 / 4] = 0;

	// initialization of /Mario/SlipParamWaterSlope.prm : mSlipFriction
	TBaseParam(this + 0x2854/4, this + 0x284c/4, calcKeyCode(prmStrBasePointer + 0x2c8), prmStrBasePointer + 0x2c8);
	this[0x2854 / 4] = 0x803abd30;
	this[0x2864 / 4] = 0;

	// initialization of /Mario/SlipParamWaterSlope.prm : mSlopeAcceleUp
	TBaseParam(this + 0x2868/4, this + 0x284c/4, calcKeyCode(prmStrBasePointer + 0x2d8), prmStrBasePointer + 0x2d8);
	this[0x2868 / 4] = 0x803abd30;
	this[0x2878 / 4] = 0;

	// initialization of /Mario/SlipParamWaterSlope.prm : mSlopeAcceleDown
	TBaseParam(this + 0x287c/4, this + 0x284c/4, calcKeyCode(prmStrBasePointer + 0x2e8), prmStrBasePointer + 0x2e8);
	this[0x287c / 4] = 0x803abd30;
	this[0x288c / 4] = 0;

	// initialization of /Mario/SlipParamWaterSlope.prm : mSlideAcceleUp
	TBaseParam(this + 0x2890/4, this + 0x284c/4, calcKeyCode(prmStrBasePointer + 0x2fc), prmStrBasePointer + 0x2fc);
	this[0x2890 / 4] = 0x803abd30;
	this[0x28a0 / 4] = 0;

	// initialization of /Mario/SlipParamWaterSlope.prm : mSlideAcceleDown
	TBaseParam(this + 0x28a4/4, this + 0x284c/4, calcKeyCode(prmStrBasePointer + 0x30c), prmStrBasePointer + 0x30c);
	this[0x28a4 / 4] = 0x803abd30;
	this[0x28b4 / 4] = 0;

	// initialization of /Mario/SlipParamWaterSlope.prm : mSlideStopNormal
	TBaseParam(this + 0x28b8/4, this + 0x284c/4, calcKeyCode(prmStrBasePointer + 0x320), prmStrBasePointer + 0x320);
	this[0x28b8 / 4] = 0x803abd30;
	this[0x28c8 / 4] = 0;

	// initialization of /Mario/SlipParamWaterSlope.prm : mSlideStopCatch
	TBaseParam(this + 0x28cc/4, this + 0x284c/4, calcKeyCode(prmStrBasePointer + 0x334), prmStrBasePointer + 0x334);
	this[0x28cc / 4] = 0x803abd30;
	this[0x28dc / 4] = 0;

	// initialization of /Mario/SlipParamWaterSlope.prm : mJumpEnable
	TBaseParam(this + 0x28e0/4, this + 0x284c/4, calcKeyCode(prmStrBasePointer + 0x344), prmStrBasePointer + 0x344);
	this[0x28e0 / 4] = 0x803ad0d8;
	this[0x28f0 / 4] = 0;

	// initialization of /Mario/SlipParamWaterSlope.prm : mMissJump
	TBaseParam(this + 0x28f4/4, this + 0x284c/4, calcKeyCode(prmStrBasePointer + 0x350), prmStrBasePointer + 0x350);
	this[0x28f4 / 4] = 0x803ad0d8;
	this[0x2904 / 4] = 0;

	// initialization of /Mario/SlipParamWaterSlope.prm : mSlideAngleYSp
	TBaseParam(this + 0x2908/4, this + 0x284c/4, calcKeyCode(prmStrBasePointer + 0x35c), prmStrBasePointer + 0x35c);
	this[0x2908 / 4] = 0x803ad0f0;
	this[0x2918 / 4] = 0;

	// initialization of /Mario/SlipParamWaterSlope.prm : mStickSlideMult
	TBaseParam(this + 0x291c/4, this + 0x284c/4, calcKeyCode(prmStrBasePointer + 0x36c), prmStrBasePointer + 0x36c);
	this[0x291c / 4] = 0x803abd30;
	this[0x292c / 4] = 0;

	// loading of /Mario/SlipParamWaterSlope.prm
	paramsLoad(this + 0x284c / 4, this[0x284c/4]);

	// initialization of /Mario/SlipParamWaterGround.prm
	this[0x2930 / 4] = prmStrBasePointer + 0x182c;
	this[0x2934 / 4] = 0;

	// initialization of /Mario/SlipParamWaterGround.prm : mSlipFriction
	TBaseParam(this + 0x2938/4, this + 0x2930/4, calcKeyCode(prmStrBasePointer + 0x2c8), prmStrBasePointer + 0x2c8);
	this[0x2938 / 4] = 0x803abd30;
	this[0x2948 / 4] = 0;

	// initialization of /Mario/SlipParamWaterGround.prm : mSlopeAcceleUp
	TBaseParam(this + 0x294c/4, this + 0x2930/4, calcKeyCode(prmStrBasePointer + 0x2d8), prmStrBasePointer + 0x2d8);
	this[0x294c / 4] = 0x803abd30;
	this[0x295c / 4] = 0;

	// initialization of /Mario/SlipParamWaterGround.prm : mSlopeAcceleDown
	TBaseParam(this + 0x2960/4, this + 0x2930/4, calcKeyCode(prmStrBasePointer + 0x2e8), prmStrBasePointer + 0x2e8);
	this[0x2960 / 4] = 0x803abd30;
	this[0x2970 / 4] = 0;

	// initialization of /Mario/SlipParamWaterGround.prm : mSlideAcceleUp
	TBaseParam(this + 0x2974/4, this + 0x2930/4, calcKeyCode(prmStrBasePointer + 0x2fc), prmStrBasePointer + 0x2fc);
	this[0x2974 / 4] = 0x803abd30;
	this[0x2984 / 4] = 0;

	// initialization of /Mario/SlipParamWaterGround.prm : mSlideAcceleDown
	TBaseParam(this + 0x2988/4, this + 0x2930/4, calcKeyCode(prmStrBasePointer + 0x30c), prmStrBasePointer + 0x30c);
	this[0x2988 / 4] = 0x803abd30;
	this[0x2998 / 4] = 0;

	// initialization of /Mario/SlipParamWaterGround.prm : mSlideStopNormal
	TBaseParam(this + 0x299c/4, this + 0x2930/4, calcKeyCode(prmStrBasePointer + 0x320), prmStrBasePointer + 0x320);
	this[0x299c / 4] = 0x803abd30;
	this[0x29ac / 4] = 0;

	// initialization of /Mario/SlipParamWaterGround.prm : mSlideStopCatch
	TBaseParam(this + 0x29b0/4, this + 0x2930/4, calcKeyCode(prmStrBasePointer + 0x334), prmStrBasePointer + 0x334);
	this[0x29b0 / 4] = 0x803abd30;
	this[0x29c0 / 4] = 0;

	// initialization of /Mario/SlipParamWaterGround.prm : mJumpEnable
	TBaseParam(this + 0x29c4/4, this + 0x2930/4, calcKeyCode(prmStrBasePointer + 0x344), prmStrBasePointer + 0x344);
	this[0x29c4 / 4] = 0x803ad0d8;
	this[0x29d4 / 4] = 0;

	// initialization of /Mario/SlipParamWaterGround.prm : mMissJump
	TBaseParam(this + 0x29d8/4, this + 0x2930/4, calcKeyCode(prmStrBasePointer + 0x350), prmStrBasePointer + 0x350);
	this[0x29d8 / 4] = 0x803ad0d8;
	this[0x29e8 / 4] = 0;

	// initialization of /Mario/SlipParamWaterGround.prm : mSlideAngleYSp
	TBaseParam(this + 0x29ec/4, this + 0x2930/4, calcKeyCode(prmStrBasePointer + 0x35c), prmStrBasePointer + 0x35c);
	this[0x29ec / 4] = 0x803ad0f0;
	this[0x29fc / 4] = 0;

	// initialization of /Mario/SlipParamWaterGround.prm : mStickSlideMult
	TBaseParam(this + 0x2a00/4, this + 0x2930/4, calcKeyCode(prmStrBasePointer + 0x36c), prmStrBasePointer + 0x36c);
	this[0x2a00 / 4] = 0x803abd30;
	this[0x2a10 / 4] = 0;

	// loading of /Mario/SlipParamWaterGround.prm
	paramsLoad(this + 0x2930 / 4, this[0x2930/4]);

	// initialization of /Mario/SlipParamYoshi.prm
	this[0x2a14 / 4] = prmStrBasePointer + 0x184c;
	this[0x2a18 / 4] = 0;

	// initialization of /Mario/SlipParamYoshi.prm : mSlipFriction
	TBaseParam(this + 0x2a1c/4, this + 0x2a14/4, calcKeyCode(prmStrBasePointer + 0x2c8), prmStrBasePointer + 0x2c8);
	this[0x2a1c / 4] = 0x803abd30;
	this[0x2a2c / 4] = 0;

	// initialization of /Mario/SlipParamYoshi.prm : mSlopeAcceleUp
	TBaseParam(this + 0x2a30/4, this + 0x2a14/4, calcKeyCode(prmStrBasePointer + 0x2d8), prmStrBasePointer + 0x2d8);
	this[0x2a30 / 4] = 0x803abd30;
	this[0x2a40 / 4] = 0;

	// initialization of /Mario/SlipParamYoshi.prm : mSlopeAcceleDown
	TBaseParam(this + 0x2a44/4, this + 0x2a14/4, calcKeyCode(prmStrBasePointer + 0x2e8), prmStrBasePointer + 0x2e8);
	this[0x2a44 / 4] = 0x803abd30;
	this[0x2a54 / 4] = 0;

	// initialization of /Mario/SlipParamYoshi.prm : mSlideAcceleUp
	TBaseParam(this + 0x2a58/4, this + 0x2a14/4, calcKeyCode(prmStrBasePointer + 0x2fc), prmStrBasePointer + 0x2fc);
	this[0x2a58 / 4] = 0x803abd30;
	this[0x2a68 / 4] = 0;

	// initialization of /Mario/SlipParamYoshi.prm : mSlideAcceleDown
	TBaseParam(this + 0x2a6c/4, this + 0x2a14/4, calcKeyCode(prmStrBasePointer + 0x30c), prmStrBasePointer + 0x30c);
	this[0x2a6c / 4] = 0x803abd30;
	this[0x2a7c / 4] = 0;

	// initialization of /Mario/SlipParamYoshi.prm : mSlideStopNormal
	TBaseParam(this + 0x2a80/4, this + 0x2a14/4, calcKeyCode(prmStrBasePointer + 0x320), prmStrBasePointer + 0x320);
	this[0x2a80 / 4] = 0x803abd30;
	this[0x2a90 / 4] = 0;

	// initialization of /Mario/SlipParamYoshi.prm : mSlideStopCatch
	TBaseParam(this + 0x2a94/4, this + 0x2a14/4, calcKeyCode(prmStrBasePointer + 0x334), prmStrBasePointer + 0x334);
	this[0x2a94 / 4] = 0x803abd30;
	this[0x2aa4 / 4] = 0;

	// initialization of /Mario/SlipParamYoshi.prm : mJumpEnable
	TBaseParam(this + 0x2aa8/4, this + 0x2a14/4, calcKeyCode(prmStrBasePointer + 0x344), prmStrBasePointer + 0x344);
	this[0x2aa8 / 4] = 0x803ad0d8;
	this[0x2ab8 / 4] = 0;

	// initialization of /Mario/SlipParamYoshi.prm : mMissJump
	TBaseParam(this + 0x2abc/4, this + 0x2a14/4, calcKeyCode(prmStrBasePointer + 0x350), prmStrBasePointer + 0x350);
	this[0x2abc / 4] = 0x803ad0d8;
	this[0x2acc / 4] = 0;

	// initialization of /Mario/SlipParamYoshi.prm : mSlideAngleYSp
	TBaseParam(this + 0x2ad0/4, this + 0x2a14/4, calcKeyCode(prmStrBasePointer + 0x35c), prmStrBasePointer + 0x35c);
	this[0x2ad0 / 4] = 0x803ad0f0;
	this[0x2ae0 / 4] = 0;

	// initialization of /Mario/SlipParamYoshi.prm : mStickSlideMult
	TBaseParam(this + 0x2ae4/4, this + 0x2a14/4, calcKeyCode(prmStrBasePointer + 0x36c), prmStrBasePointer + 0x36c);
	this[0x2ae4 / 4] = 0x803abd30;
	this[0x2af4 / 4] = 0;

	// loading of /Mario/SlipParamYoshi.prm
	paramsLoad(this + 0x2a14 / 4, this[0x2a14/4]);

	// initialization of /Mario/UpperBody.prm
	this[0x2af8 / 4] = prmStrBasePointer + 0x1868;
	this[0x2afc / 4] = 0;

	// initialization of /Mario/UpperBody.prm : mPumpWaitTime
	TBaseParam(this + 0x2b00/4, this + 0x2af8/4, calcKeyCode(prmStrBasePointer + 0x270), prmStrBasePointer + 0x270);
	this[0x2b00 / 4] = 0x803ad0f0;
	this[0x2b10 / 4] = 0;

	// initialization of /Mario/UpperBody.prm : mPumpAnmSpeed
	TBaseParam(this + 0x2b14/4, this + 0x2af8/4, calcKeyCode(prmStrBasePointer + 0x280), prmStrBasePointer + 0x280);
	this[0x2b14 / 4] = 0x803abd30;
	this[0x2b24 / 4] = 0;

	// initialization of /Mario/UpperBody.prm : mHoverHeadAngle
	TBaseParam(this + 0x2b28/4, this + 0x2af8/4, calcKeyCode(prmStrBasePointer + 0x290), prmStrBasePointer + 0x290);
	this[0x2b28 / 4] = 0x803ad0f0;
	this[0x2b38 / 4] = 0;

	// initialization of /Mario/UpperBody.prm : mFeelDeepHeadAngle
	TBaseParam(this + 0x2b3c/4, this + 0x2af8/4, calcKeyCode(prmStrBasePointer + 0x2a0), prmStrBasePointer + 0x2a0);
	this[0x2b3c / 4] = 0x803ad0f0;
	this[0x2b4c / 4] = 0;

	// initialization of /Mario/UpperBody.prm : mFrontWallHeadAngle
	TBaseParam(this + 0x2b50/4, this + 0x2af8/4, calcKeyCode(prmStrBasePointer + 0x2b4), prmStrBasePointer + 0x2b4);
	this[0x2b50 / 4] = 0x803ad0f0;
	this[0x2b60 / 4] = 0;

	// loading of /Mario/UpperBody.prm
	paramsLoad(this + 0x2af8 / 4, this[0x2af8/4]);

	// initialization of /Mario/DmgEnemyCommon.prm
	this[0x2b64 / 4] = prmStrBasePointer + 0x1880;
	this[0x2b68 / 4] = 0;

	// initialization of /Mario/DmgEnemyCommon.prm : mDamage
	TBaseParam(this + 0x2b6c/4, this + 0x2b64/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x2b6c / 4] = 0x803ad0d8;
	this[0x2b7c / 4] = 0;

	// initialization of /Mario/DmgEnemyCommon.prm : mDownType
	TBaseParam(this + 0x2b80/4, this + 0x2b64/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x2b80 / 4] = 0x803ad0d8;
	this[0x2b90 / 4] = 0;

	// initialization of /Mario/DmgEnemyCommon.prm : mWaterEmit
	TBaseParam(this + 0x2b94/4, this + 0x2b64/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x2b94 / 4] = 0x803ad0d8;
	this[0x2ba4 / 4] = 0;

	// initialization of /Mario/DmgEnemyCommon.prm : mMotor
	TBaseParam(this + 0x2ba8/4, this + 0x2b64/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x2ba8 / 4] = 0x803ad0d8;
	this[0x2bb8 / 4] = 0;

	// initialization of /Mario/DmgEnemyCommon.prm : mMinSpeed
	TBaseParam(this + 0x2bbc/4, this + 0x2b64/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x2bbc / 4] = 0x803abd30;
	this[0x2bcc / 4] = 0;

	// initialization of /Mario/DmgEnemyCommon.prm : mDirty
	TBaseParam(this + 0x2bd0/4, this + 0x2b64/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x2bd0 / 4] = 0x803abd30;
	this[0x2be0 / 4] = 0;

	// initialization of /Mario/DmgEnemyCommon.prm : mInvincibleTime
	TBaseParam(this + 0x2be4/4, this + 0x2b64/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x2be4 / 4] = 0x803ad0f0;
	this[0x2bf4 / 4] = 0;

	// loading of /Mario/DmgEnemyCommon.prm
	paramsLoad(this + 0x2b64 / 4, this[0x2b64/4]);

	// initialization of /Mario/DmgHamukuri.prm
	this[0x2bf8 / 4] = prmStrBasePointer + 0x189c;
	this[0x2bfc / 4] = 0;

	// initialization of /Mario/DmgHamukuri.prm : mDamage
	TBaseParam(this + 0x2c00/4, this + 0x2bf8/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x2c00 / 4] = 0x803ad0d8;
	this[0x2c10 / 4] = 0;

	// initialization of /Mario/DmgHamukuri.prm : mDownType
	TBaseParam(this + 0x2c14/4, this + 0x2bf8/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x2c14 / 4] = 0x803ad0d8;
	this[0x2c24 / 4] = 0;

	// initialization of /Mario/DmgHamukuri.prm : mWaterEmit
	TBaseParam(this + 0x2c28/4, this + 0x2bf8/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x2c28 / 4] = 0x803ad0d8;
	this[0x2c38 / 4] = 0;

	// initialization of /Mario/DmgHamukuri.prm : mMotor
	TBaseParam(this + 0x2c3c/4, this + 0x2bf8/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x2c3c / 4] = 0x803ad0d8;
	this[0x2c4c / 4] = 0;

	// initialization of /Mario/DmgHamukuri.prm : mMinSpeed
	TBaseParam(this + 0x2c50/4, this + 0x2bf8/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x2c50 / 4] = 0x803abd30;
	this[0x2c60 / 4] = 0;

	// initialization of /Mario/DmgHamukuri.prm : mDirty
	TBaseParam(this + 0x2c64/4, this + 0x2bf8/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x2c64 / 4] = 0x803abd30;
	this[0x2c74 / 4] = 0;

	// initialization of /Mario/DmgHamukuri.prm : mInvincibleTime
	TBaseParam(this + 0x2c78/4, this + 0x2bf8/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x2c78 / 4] = 0x803ad0f0;
	this[0x2c88 / 4] = 0;

	// loading of /Mario/DmgHamukuri.prm
	paramsLoad(this + 0x2bf8 / 4, this[0x2bf8/4]);

	// initialization of /Mario/DmgNamekuri.prm
	this[0x2c8c / 4] = prmStrBasePointer + 0x18b4;
	this[0x2c90 / 4] = 0;

	// initialization of /Mario/DmgNamekuri.prm : mDamage
	TBaseParam(this + 0x2c94/4, this + 0x2c8c/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x2c94 / 4] = 0x803ad0d8;
	this[0x2ca4 / 4] = 0;

	// initialization of /Mario/DmgNamekuri.prm : mDownType
	TBaseParam(this + 0x2ca8/4, this + 0x2c8c/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x2ca8 / 4] = 0x803ad0d8;
	this[0x2cb8 / 4] = 0;

	// initialization of /Mario/DmgNamekuri.prm : mWaterEmit
	TBaseParam(this + 0x2cbc/4, this + 0x2c8c/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x2cbc / 4] = 0x803ad0d8;
	this[0x2ccc / 4] = 0;

	// initialization of /Mario/DmgNamekuri.prm : mMotor
	TBaseParam(this + 0x2cd0/4, this + 0x2c8c/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x2cd0 / 4] = 0x803ad0d8;
	this[0x2ce0 / 4] = 0;

	// initialization of /Mario/DmgNamekuri.prm : mMinSpeed
	TBaseParam(this + 0x2ce4/4, this + 0x2c8c/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x2ce4 / 4] = 0x803abd30;
	this[0x2cf4 / 4] = 0;

	// initialization of /Mario/DmgNamekuri.prm : mDirty
	TBaseParam(this + 0x2cf8/4, this + 0x2c8c/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x2cf8 / 4] = 0x803abd30;
	this[0x2d08 / 4] = 0;

	// initialization of /Mario/DmgNamekuri.prm : mInvincibleTime
	TBaseParam(this + 0x2d0c/4, this + 0x2c8c/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x2d0c / 4] = 0x803ad0f0;
	this[0x2d1c / 4] = 0;

	// loading of /Mario/DmgNamekuri.prm
	paramsLoad(this + 0x2c8c / 4, this[0x2c8c/4]);

	// initialization of /Mario/DmgHinokuri.prm
	this[0x2d20 / 4] = prmStrBasePointer + 0x18cc;
	this[0x2d24 / 4] = 0;

	// initialization of /Mario/DmgHinokuri.prm : mDamage
	TBaseParam(this + 0x2d28/4, this + 0x2d20/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x2d28 / 4] = 0x803ad0d8;
	this[0x2d38 / 4] = 0;

	// initialization of /Mario/DmgHinokuri.prm : mDownType
	TBaseParam(this + 0x2d3c/4, this + 0x2d20/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x2d3c / 4] = 0x803ad0d8;
	this[0x2d4c / 4] = 0;

	// initialization of /Mario/DmgHinokuri.prm : mWaterEmit
	TBaseParam(this + 0x2d50/4, this + 0x2d20/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x2d50 / 4] = 0x803ad0d8;
	this[0x2d60 / 4] = 0;

	// initialization of /Mario/DmgHinokuri.prm : mMotor
	TBaseParam(this + 0x2d64/4, this + 0x2d20/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x2d64 / 4] = 0x803ad0d8;
	this[0x2d74 / 4] = 0;

	// initialization of /Mario/DmgHinokuri.prm : mMinSpeed
	TBaseParam(this + 0x2d78/4, this + 0x2d20/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x2d78 / 4] = 0x803abd30;
	this[0x2d88 / 4] = 0;

	// initialization of /Mario/DmgHinokuri.prm : mDirty
	TBaseParam(this + 0x2d8c/4, this + 0x2d20/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x2d8c / 4] = 0x803abd30;
	this[0x2d9c / 4] = 0;

	// initialization of /Mario/DmgHinokuri.prm : mInvincibleTime
	TBaseParam(this + 0x2da0/4, this + 0x2d20/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x2da0 / 4] = 0x803ad0f0;
	this[0x2db0 / 4] = 0;

	// loading of /Mario/DmgHinokuri.prm
	paramsLoad(this + 0x2d20 / 4, this[0x2d20/4]);

	// initialization of /Mario/DmgFire.prm
	this[0x2db4 / 4] = prmStrBasePointer + 0x18e4;
	this[0x2db8 / 4] = 0;

	// initialization of /Mario/DmgFire.prm : mDamage
	TBaseParam(this + 0x2dbc/4, this + 0x2db4/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x2dbc / 4] = 0x803ad0d8;
	this[0x2dcc / 4] = 0;

	// initialization of /Mario/DmgFire.prm : mDownType
	TBaseParam(this + 0x2dd0/4, this + 0x2db4/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x2dd0 / 4] = 0x803ad0d8;
	this[0x2de0 / 4] = 0;

	// initialization of /Mario/DmgFire.prm : mWaterEmit
	TBaseParam(this + 0x2de4/4, this + 0x2db4/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x2de4 / 4] = 0x803ad0d8;
	this[0x2df4 / 4] = 0;

	// initialization of /Mario/DmgFire.prm : mMotor
	TBaseParam(this + 0x2df8/4, this + 0x2db4/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x2df8 / 4] = 0x803ad0d8;
	this[0x2e08 / 4] = 0;

	// initialization of /Mario/DmgFire.prm : mMinSpeed
	TBaseParam(this + 0x2e0c/4, this + 0x2db4/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x2e0c / 4] = 0x803abd30;
	this[0x2e1c / 4] = 0;

	// initialization of /Mario/DmgFire.prm : mDirty
	TBaseParam(this + 0x2e20/4, this + 0x2db4/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x2e20 / 4] = 0x803abd30;
	this[0x2e30 / 4] = 0;

	// initialization of /Mario/DmgFire.prm : mInvincibleTime
	TBaseParam(this + 0x2e34/4, this + 0x2db4/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x2e34 / 4] = 0x803ad0f0;
	this[0x2e44 / 4] = 0;

	// loading of /Mario/DmgFire.prm
	paramsLoad(this + 0x2db4 / 4, this[0x2db4/4]);

	// initialization of /Mario/DmgBGTentacle.prm
	this[0x2e48 / 4] = prmStrBasePointer + 0x18f8;
	this[0x2e4c / 4] = 0;

	// initialization of /Mario/DmgBGTentacle.prm : mDamage
	TBaseParam(this + 0x2e50/4, this + 0x2e48/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x2e50 / 4] = 0x803ad0d8;
	this[0x2e60 / 4] = 0;

	// initialization of /Mario/DmgBGTentacle.prm : mDownType
	TBaseParam(this + 0x2e64/4, this + 0x2e48/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x2e64 / 4] = 0x803ad0d8;
	this[0x2e74 / 4] = 0;

	// initialization of /Mario/DmgBGTentacle.prm : mWaterEmit
	TBaseParam(this + 0x2e78/4, this + 0x2e48/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x2e78 / 4] = 0x803ad0d8;
	this[0x2e88 / 4] = 0;

	// initialization of /Mario/DmgBGTentacle.prm : mMotor
	TBaseParam(this + 0x2e8c/4, this + 0x2e48/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x2e8c / 4] = 0x803ad0d8;
	this[0x2e9c / 4] = 0;

	// initialization of /Mario/DmgBGTentacle.prm : mMinSpeed
	TBaseParam(this + 0x2ea0/4, this + 0x2e48/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x2ea0 / 4] = 0x803abd30;
	this[0x2eb0 / 4] = 0;

	// initialization of /Mario/DmgBGTentacle.prm : mDirty
	TBaseParam(this + 0x2eb4/4, this + 0x2e48/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x2eb4 / 4] = 0x803abd30;
	this[0x2ec4 / 4] = 0;

	// initialization of /Mario/DmgBGTentacle.prm : mInvincibleTime
	TBaseParam(this + 0x2ec8/4, this + 0x2e48/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x2ec8 / 4] = 0x803ad0f0;
	this[0x2ed8 / 4] = 0;

	// loading of /Mario/DmgBGTentacle.prm
	paramsLoad(this + 0x2e48 / 4, this[0x2e48/4]);

	// initialization of /Mario/DmgBossEel.prm
	this[0x2edc / 4] = prmStrBasePointer + 0x1914;
	this[0x2ee0 / 4] = 0;

	// initialization of /Mario/DmgBossEel.prm : mDamage
	TBaseParam(this + 0x2ee4/4, this + 0x2edc/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x2ee4 / 4] = 0x803ad0d8;
	this[0x2ef4 / 4] = 0;

	// initialization of /Mario/DmgBossEel.prm : mDownType
	TBaseParam(this + 0x2ef8/4, this + 0x2edc/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x2ef8 / 4] = 0x803ad0d8;
	this[0x2f08 / 4] = 0;

	// initialization of /Mario/DmgBossEel.prm : mWaterEmit
	TBaseParam(this + 0x2f0c/4, this + 0x2edc/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x2f0c / 4] = 0x803ad0d8;
	this[0x2f1c / 4] = 0;

	// initialization of /Mario/DmgBossEel.prm : mMotor
	TBaseParam(this + 0x2f20/4, this + 0x2edc/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x2f20 / 4] = 0x803ad0d8;
	this[0x2f30 / 4] = 0;

	// initialization of /Mario/DmgBossEel.prm : mMinSpeed
	TBaseParam(this + 0x2f34/4, this + 0x2edc/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x2f34 / 4] = 0x803abd30;
	this[0x2f44 / 4] = 0;

	// initialization of /Mario/DmgBossEel.prm : mDirty
	TBaseParam(this + 0x2f48/4, this + 0x2edc/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x2f48 / 4] = 0x803abd30;
	this[0x2f58 / 4] = 0;

	// initialization of /Mario/DmgBossEel.prm : mInvincibleTime
	TBaseParam(this + 0x2f5c/4, this + 0x2edc/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x2f5c / 4] = 0x803ad0f0;
	this[0x2f6c / 4] = 0;

	// loading of /Mario/DmgBossEel.prm
	paramsLoad(this + 0x2edc / 4, this[0x2edc/4]);

	// initialization of /Mario/DmgHanachanBoss.prm
	this[0x2f70 / 4] = prmStrBasePointer + 0x192c;
	this[0x2f74 / 4] = 0;

	// initialization of /Mario/DmgHanachanBoss.prm : mDamage
	TBaseParam(this + 0x2f78/4, this + 0x2f70/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x2f78 / 4] = 0x803ad0d8;
	this[0x2f88 / 4] = 0;

	// initialization of /Mario/DmgHanachanBoss.prm : mDownType
	TBaseParam(this + 0x2f8c/4, this + 0x2f70/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x2f8c / 4] = 0x803ad0d8;
	this[0x2f9c / 4] = 0;

	// initialization of /Mario/DmgHanachanBoss.prm : mWaterEmit
	TBaseParam(this + 0x2fa0/4, this + 0x2f70/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x2fa0 / 4] = 0x803ad0d8;
	this[0x2fb0 / 4] = 0;

	// initialization of /Mario/DmgHanachanBoss.prm : mMotor
	TBaseParam(this + 0x2fb4/4, this + 0x2f70/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x2fb4 / 4] = 0x803ad0d8;
	this[0x2fc4 / 4] = 0;

	// initialization of /Mario/DmgHanachanBoss.prm : mMinSpeed
	TBaseParam(this + 0x2fc8/4, this + 0x2f70/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x2fc8 / 4] = 0x803abd30;
	this[0x2fd8 / 4] = 0;

	// initialization of /Mario/DmgHanachanBoss.prm : mDirty
	TBaseParam(this + 0x2fdc/4, this + 0x2f70/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x2fdc / 4] = 0x803abd30;
	this[0x2fec / 4] = 0;

	// initialization of /Mario/DmgHanachanBoss.prm : mInvincibleTime
	TBaseParam(this + 0x2ff0/4, this + 0x2f70/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x2ff0 / 4] = 0x803ad0f0;
	this[0x3000 / 4] = 0;

	// loading of /Mario/DmgHanachanBoss.prm
	paramsLoad(this + 0x2f70 / 4, this[0x2f70/4]);

	// initialization of /Mario/DmgPoihana.prm
	this[0x3004 / 4] = prmStrBasePointer + 0x1948;
	this[0x3008 / 4] = 0;

	// initialization of /Mario/DmgPoihana.prm : mDamage
	TBaseParam(this + 0x300c/4, this + 0x3004/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x300c / 4] = 0x803ad0d8;
	this[0x301c / 4] = 0;

	// initialization of /Mario/DmgPoihana.prm : mDownType
	TBaseParam(this + 0x3020/4, this + 0x3004/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x3020 / 4] = 0x803ad0d8;
	this[0x3030 / 4] = 0;

	// initialization of /Mario/DmgPoihana.prm : mWaterEmit
	TBaseParam(this + 0x3034/4, this + 0x3004/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x3034 / 4] = 0x803ad0d8;
	this[0x3044 / 4] = 0;

	// initialization of /Mario/DmgPoihana.prm : mMotor
	TBaseParam(this + 0x3048/4, this + 0x3004/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x3048 / 4] = 0x803ad0d8;
	this[0x3058 / 4] = 0;

	// initialization of /Mario/DmgPoihana.prm : mMinSpeed
	TBaseParam(this + 0x305c/4, this + 0x3004/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x305c / 4] = 0x803abd30;
	this[0x306c / 4] = 0;

	// initialization of /Mario/DmgPoihana.prm : mDirty
	TBaseParam(this + 0x3070/4, this + 0x3004/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x3070 / 4] = 0x803abd30;
	this[0x3080 / 4] = 0;

	// initialization of /Mario/DmgPoihana.prm : mInvincibleTime
	TBaseParam(this + 0x3084/4, this + 0x3004/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x3084 / 4] = 0x803ad0f0;
	this[0x3094 / 4] = 0;

	// loading of /Mario/DmgPoihana.prm
	paramsLoad(this + 0x3004 / 4, this[0x3004/4]);

	// initialization of /Mario/DmgKiller.prm
	this[0x3098 / 4] = prmStrBasePointer + 0x1960;
	this[0x309c / 4] = 0;

	// initialization of /Mario/DmgKiller.prm : mDamage
	TBaseParam(this + 0x30a0/4, this + 0x3098/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x30a0 / 4] = 0x803ad0d8;
	this[0x30b0 / 4] = 0;

	// initialization of /Mario/DmgKiller.prm : mDownType
	TBaseParam(this + 0x30b4/4, this + 0x3098/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x30b4 / 4] = 0x803ad0d8;
	this[0x30c4 / 4] = 0;

	// initialization of /Mario/DmgKiller.prm : mWaterEmit
	TBaseParam(this + 0x30c8/4, this + 0x3098/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x30c8 / 4] = 0x803ad0d8;
	this[0x30d8 / 4] = 0;

	// initialization of /Mario/DmgKiller.prm : mMotor
	TBaseParam(this + 0x30dc/4, this + 0x3098/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x30dc / 4] = 0x803ad0d8;
	this[0x30ec / 4] = 0;

	// initialization of /Mario/DmgKiller.prm : mMinSpeed
	TBaseParam(this + 0x30f0/4, this + 0x3098/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x30f0 / 4] = 0x803abd30;
	this[0x3100 / 4] = 0;

	// initialization of /Mario/DmgKiller.prm : mDirty
	TBaseParam(this + 0x3104/4, this + 0x3098/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x3104 / 4] = 0x803abd30;
	this[0x3114 / 4] = 0;

	// initialization of /Mario/DmgKiller.prm : mInvincibleTime
	TBaseParam(this + 0x3118/4, this + 0x3098/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x3118 / 4] = 0x803ad0f0;
	this[0x3128 / 4] = 0;

	// loading of /Mario/DmgKiller.prm
	paramsLoad(this + 0x3098 / 4, this[0x3098/4]);

	// initialization of /Mario/DmgLampTrapIron.prm
	this[0x312c / 4] = prmStrBasePointer + 0x1978;
	this[0x3130 / 4] = 0;

	// initialization of /Mario/DmgLampTrapIron.prm : mDamage
	TBaseParam(this + 0x3134/4, this + 0x312c/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x3134 / 4] = 0x803ad0d8;
	this[0x3144 / 4] = 0;

	// initialization of /Mario/DmgLampTrapIron.prm : mDownType
	TBaseParam(this + 0x3148/4, this + 0x312c/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x3148 / 4] = 0x803ad0d8;
	this[0x3158 / 4] = 0;

	// initialization of /Mario/DmgLampTrapIron.prm : mWaterEmit
	TBaseParam(this + 0x315c/4, this + 0x312c/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x315c / 4] = 0x803ad0d8;
	this[0x316c / 4] = 0;

	// initialization of /Mario/DmgLampTrapIron.prm : mMotor
	TBaseParam(this + 0x3170/4, this + 0x312c/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x3170 / 4] = 0x803ad0d8;
	this[0x3180 / 4] = 0;

	// initialization of /Mario/DmgLampTrapIron.prm : mMinSpeed
	TBaseParam(this + 0x3184/4, this + 0x312c/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x3184 / 4] = 0x803abd30;
	this[0x3194 / 4] = 0;

	// initialization of /Mario/DmgLampTrapIron.prm : mDirty
	TBaseParam(this + 0x3198/4, this + 0x312c/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x3198 / 4] = 0x803abd30;
	this[0x31a8 / 4] = 0;

	// initialization of /Mario/DmgLampTrapIron.prm : mInvincibleTime
	TBaseParam(this + 0x31ac/4, this + 0x312c/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x31ac / 4] = 0x803ad0f0;
	this[0x31bc / 4] = 0;

	// loading of /Mario/DmgLampTrapIron.prm
	paramsLoad(this + 0x312c / 4, this[0x312c/4]);

	// initialization of /Mario/DmgLampTrapSpike.prm
	this[0x31c0 / 4] = prmStrBasePointer + 0x1994;
	this[0x31c4 / 4] = 0;

	// initialization of /Mario/DmgLampTrapSpike.prm : mDamage
	TBaseParam(this + 0x31c8/4, this + 0x31c0/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x31c8 / 4] = 0x803ad0d8;
	this[0x31d8 / 4] = 0;

	// initialization of /Mario/DmgLampTrapSpike.prm : mDownType
	TBaseParam(this + 0x31dc/4, this + 0x31c0/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x31dc / 4] = 0x803ad0d8;
	this[0x31ec / 4] = 0;

	// initialization of /Mario/DmgLampTrapSpike.prm : mWaterEmit
	TBaseParam(this + 0x31f0/4, this + 0x31c0/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x31f0 / 4] = 0x803ad0d8;
	this[0x3200 / 4] = 0;

	// initialization of /Mario/DmgLampTrapSpike.prm : mMotor
	TBaseParam(this + 0x3204/4, this + 0x31c0/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x3204 / 4] = 0x803ad0d8;
	this[0x3214 / 4] = 0;

	// initialization of /Mario/DmgLampTrapSpike.prm : mMinSpeed
	TBaseParam(this + 0x3218/4, this + 0x31c0/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x3218 / 4] = 0x803abd30;
	this[0x3228 / 4] = 0;

	// initialization of /Mario/DmgLampTrapSpike.prm : mDirty
	TBaseParam(this + 0x322c/4, this + 0x31c0/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x322c / 4] = 0x803abd30;
	this[0x323c / 4] = 0;

	// initialization of /Mario/DmgLampTrapSpike.prm : mInvincibleTime
	TBaseParam(this + 0x3240/4, this + 0x31c0/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x3240 / 4] = 0x803ad0f0;
	this[0x3250 / 4] = 0;

	// loading of /Mario/DmgLampTrapSpike.prm
	paramsLoad(this + 0x31c0 / 4, this[0x31c0/4]);

	// initialization of /Mario/DmgEnemyMario.prm
	this[0x3254 / 4] = prmStrBasePointer + 0x19b0;
	this[0x3258 / 4] = 0;

	// initialization of /Mario/DmgEnemyMario.prm : mDamage
	TBaseParam(this + 0x325c/4, this + 0x3254/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x325c / 4] = 0x803ad0d8;
	this[0x326c / 4] = 0;

	// initialization of /Mario/DmgEnemyMario.prm : mDownType
	TBaseParam(this + 0x3270/4, this + 0x3254/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x3270 / 4] = 0x803ad0d8;
	this[0x3280 / 4] = 0;

	// initialization of /Mario/DmgEnemyMario.prm : mWaterEmit
	TBaseParam(this + 0x3284/4, this + 0x3254/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x3284 / 4] = 0x803ad0d8;
	this[0x3294 / 4] = 0;

	// initialization of /Mario/DmgEnemyMario.prm : mMotor
	TBaseParam(this + 0x3298/4, this + 0x3254/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x3298 / 4] = 0x803ad0d8;
	this[0x32a8 / 4] = 0;

	// initialization of /Mario/DmgEnemyMario.prm : mMinSpeed
	TBaseParam(this + 0x32ac/4, this + 0x3254/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x32ac / 4] = 0x803abd30;
	this[0x32bc / 4] = 0;

	// initialization of /Mario/DmgEnemyMario.prm : mDirty
	TBaseParam(this + 0x32c0/4, this + 0x3254/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x32c0 / 4] = 0x803abd30;
	this[0x32d0 / 4] = 0;

	// initialization of /Mario/DmgEnemyMario.prm : mInvincibleTime
	TBaseParam(this + 0x32d4/4, this + 0x3254/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x32d4 / 4] = 0x803ad0f0;
	this[0x32e4 / 4] = 0;

	// loading of /Mario/DmgEnemyMario.prm
	paramsLoad(this + 0x3254 / 4, this[0x3254/4]);

	// initialization of /Mario/DmgCannotBreath.prm
	this[0x32e8 / 4] = prmStrBasePointer + 0x19cc;
	this[0x32ec / 4] = 0;

	// initialization of /Mario/DmgCannotBreath.prm : mDamage
	TBaseParam(this + 0x32f0/4, this + 0x32e8/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x32f0 / 4] = 0x803ad0d8;
	this[0x3300 / 4] = 0;

	// initialization of /Mario/DmgCannotBreath.prm : mDownType
	TBaseParam(this + 0x3304/4, this + 0x32e8/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x3304 / 4] = 0x803ad0d8;
	this[0x3314 / 4] = 0;

	// initialization of /Mario/DmgCannotBreath.prm : mWaterEmit
	TBaseParam(this + 0x3318/4, this + 0x32e8/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x3318 / 4] = 0x803ad0d8;
	this[0x3328 / 4] = 0;

	// initialization of /Mario/DmgCannotBreath.prm : mMotor
	TBaseParam(this + 0x332c/4, this + 0x32e8/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x332c / 4] = 0x803ad0d8;
	this[0x333c / 4] = 0;

	// initialization of /Mario/DmgCannotBreath.prm : mMinSpeed
	TBaseParam(this + 0x3340/4, this + 0x32e8/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x3340 / 4] = 0x803abd30;
	this[0x3350 / 4] = 0;

	// initialization of /Mario/DmgCannotBreath.prm : mDirty
	TBaseParam(this + 0x3354/4, this + 0x32e8/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x3354 / 4] = 0x803abd30;
	this[0x3364 / 4] = 0;

	// initialization of /Mario/DmgCannotBreath.prm : mInvincibleTime
	TBaseParam(this + 0x3368/4, this + 0x32e8/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x3368 / 4] = 0x803ad0f0;
	this[0x3378 / 4] = 0;

	// loading of /Mario/DmgCannotBreath.prm
	paramsLoad(this + 0x32e8 / 4, this[0x32e8/4]);

	// initialization of /Mario/DmgGraffitoFire.prm
	this[0x337c / 4] = prmStrBasePointer + 0x19e8;
	this[0x3380 / 4] = 0;

	// initialization of /Mario/DmgGraffitoFire.prm : mDamage
	TBaseParam(this + 0x3384/4, this + 0x337c/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x3384 / 4] = 0x803ad0d8;
	this[0x3394 / 4] = 0;

	// initialization of /Mario/DmgGraffitoFire.prm : mDownType
	TBaseParam(this + 0x3398/4, this + 0x337c/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x3398 / 4] = 0x803ad0d8;
	this[0x33a8 / 4] = 0;

	// initialization of /Mario/DmgGraffitoFire.prm : mWaterEmit
	TBaseParam(this + 0x33ac/4, this + 0x337c/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x33ac / 4] = 0x803ad0d8;
	this[0x33bc / 4] = 0;

	// initialization of /Mario/DmgGraffitoFire.prm : mMotor
	TBaseParam(this + 0x33c0/4, this + 0x337c/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x33c0 / 4] = 0x803ad0d8;
	this[0x33d0 / 4] = 0;

	// initialization of /Mario/DmgGraffitoFire.prm : mMinSpeed
	TBaseParam(this + 0x33d4/4, this + 0x337c/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x33d4 / 4] = 0x803abd30;
	this[0x33e4 / 4] = 0;

	// initialization of /Mario/DmgGraffitoFire.prm : mDirty
	TBaseParam(this + 0x33e8/4, this + 0x337c/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x33e8 / 4] = 0x803abd30;
	this[0x33f8 / 4] = 0;

	// initialization of /Mario/DmgGraffitoFire.prm : mInvincibleTime
	TBaseParam(this + 0x33fc/4, this + 0x337c/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x33fc / 4] = 0x803ad0f0;
	this[0x340c / 4] = 0;

	// loading of /Mario/DmgGraffitoFire.prm
	paramsLoad(this + 0x337c / 4, this[0x337c/4]);

	// initialization of /Mario/DmgGraffitoPoison.prm
	this[0x3410 / 4] = prmStrBasePointer + 0x1a04;
	this[0x3414 / 4] = 0;

	// initialization of /Mario/DmgGraffitoPoison.prm : mDamage
	TBaseParam(this + 0x3418/4, this + 0x3410/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x3418 / 4] = 0x803ad0d8;
	this[0x3428 / 4] = 0;

	// initialization of /Mario/DmgGraffitoPoison.prm : mDownType
	TBaseParam(this + 0x342c/4, this + 0x3410/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x342c / 4] = 0x803ad0d8;
	this[0x343c / 4] = 0;

	// initialization of /Mario/DmgGraffitoPoison.prm : mWaterEmit
	TBaseParam(this + 0x3440/4, this + 0x3410/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x3440 / 4] = 0x803ad0d8;
	this[0x3450 / 4] = 0;

	// initialization of /Mario/DmgGraffitoPoison.prm : mMotor
	TBaseParam(this + 0x3454/4, this + 0x3410/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x3454 / 4] = 0x803ad0d8;
	this[0x3464 / 4] = 0;

	// initialization of /Mario/DmgGraffitoPoison.prm : mMinSpeed
	TBaseParam(this + 0x3468/4, this + 0x3410/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x3468 / 4] = 0x803abd30;
	this[0x3478 / 4] = 0;

	// initialization of /Mario/DmgGraffitoPoison.prm : mDirty
	TBaseParam(this + 0x347c/4, this + 0x3410/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x347c / 4] = 0x803abd30;
	this[0x348c / 4] = 0;

	// initialization of /Mario/DmgGraffitoPoison.prm : mInvincibleTime
	TBaseParam(this + 0x3490/4, this + 0x3410/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x3490 / 4] = 0x803ad0f0;
	this[0x34a0 / 4] = 0;

	// loading of /Mario/DmgGraffitoPoison.prm
	paramsLoad(this + 0x3410 / 4, this[0x3410/4]);

	// initialization of /Mario/DmgGraffitoElec.prm
	this[0x34a4 / 4] = prmStrBasePointer + 0x1a24;
	this[0x34a8 / 4] = 0;

	// initialization of /Mario/DmgGraffitoElec.prm : mDamage
	TBaseParam(this + 0x34ac/4, this + 0x34a4/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x34ac / 4] = 0x803ad0d8;
	this[0x34bc / 4] = 0;

	// initialization of /Mario/DmgGraffitoElec.prm : mDownType
	TBaseParam(this + 0x34c0/4, this + 0x34a4/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x34c0 / 4] = 0x803ad0d8;
	this[0x34d0 / 4] = 0;

	// initialization of /Mario/DmgGraffitoElec.prm : mWaterEmit
	TBaseParam(this + 0x34d4/4, this + 0x34a4/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x34d4 / 4] = 0x803ad0d8;
	this[0x34e4 / 4] = 0;

	// initialization of /Mario/DmgGraffitoElec.prm : mMotor
	TBaseParam(this + 0x34e8/4, this + 0x34a4/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x34e8 / 4] = 0x803ad0d8;
	this[0x34f8 / 4] = 0;

	// initialization of /Mario/DmgGraffitoElec.prm : mMinSpeed
	TBaseParam(this + 0x34fc/4, this + 0x34a4/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x34fc / 4] = 0x803abd30;
	this[0x350c / 4] = 0;

	// initialization of /Mario/DmgGraffitoElec.prm : mDirty
	TBaseParam(this + 0x3510/4, this + 0x34a4/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x3510 / 4] = 0x803abd30;
	this[0x3520 / 4] = 0;

	// initialization of /Mario/DmgGraffitoElec.prm : mInvincibleTime
	TBaseParam(this + 0x3524/4, this + 0x34a4/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x3524 / 4] = 0x803ad0f0;
	this[0x3534 / 4] = 0;

	// loading of /Mario/DmgGraffitoElec.prm
	paramsLoad(this + 0x34a4 / 4, this[0x34a4/4]);

	// initialization of /Mario/DmgGraffitoLava.prm
	this[0x3538 / 4] = prmStrBasePointer + 0x1a40;
	this[0x353c / 4] = 0;

	// initialization of /Mario/DmgGraffitoLava.prm : mDamage
	TBaseParam(this + 0x3540/4, this + 0x3538/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x3540 / 4] = 0x803ad0d8;
	this[0x3550 / 4] = 0;

	// initialization of /Mario/DmgGraffitoLava.prm : mDownType
	TBaseParam(this + 0x3554/4, this + 0x3538/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x3554 / 4] = 0x803ad0d8;
	this[0x3564 / 4] = 0;

	// initialization of /Mario/DmgGraffitoLava.prm : mWaterEmit
	TBaseParam(this + 0x3568/4, this + 0x3538/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x3568 / 4] = 0x803ad0d8;
	this[0x3578 / 4] = 0;

	// initialization of /Mario/DmgGraffitoLava.prm : mMotor
	TBaseParam(this + 0x357c/4, this + 0x3538/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x357c / 4] = 0x803ad0d8;
	this[0x358c / 4] = 0;

	// initialization of /Mario/DmgGraffitoLava.prm : mMinSpeed
	TBaseParam(this + 0x3590/4, this + 0x3538/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x3590 / 4] = 0x803abd30;
	this[0x35a0 / 4] = 0;

	// initialization of /Mario/DmgGraffitoLava.prm : mDirty
	TBaseParam(this + 0x35a4/4, this + 0x3538/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x35a4 / 4] = 0x803abd30;
	this[0x35b4 / 4] = 0;

	// initialization of /Mario/DmgGraffitoLava.prm : mInvincibleTime
	TBaseParam(this + 0x35b8/4, this + 0x3538/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x35b8 / 4] = 0x803ad0f0;
	this[0x35c8 / 4] = 0;

	// loading of /Mario/DmgGraffitoLava.prm
	paramsLoad(this + 0x3538 / 4, this[0x3538/4]);

	// initialization of /Mario/DmgGraffitoWaterSurface.prm
	this[0x35cc / 4] = prmStrBasePointer + 0x1a5c;
	this[0x35d0 / 4] = 0;

	// initialization of /Mario/DmgGraffitoWaterSurface.prm : mDamage
	TBaseParam(this + 0x35d4/4, this + 0x35cc/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x35d4 / 4] = 0x803ad0d8;
	this[0x35e4 / 4] = 0;

	// initialization of /Mario/DmgGraffitoWaterSurface.prm : mDownType
	TBaseParam(this + 0x35e8/4, this + 0x35cc/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x35e8 / 4] = 0x803ad0d8;
	this[0x35f8 / 4] = 0;

	// initialization of /Mario/DmgGraffitoWaterSurface.prm : mWaterEmit
	TBaseParam(this + 0x35fc/4, this + 0x35cc/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x35fc / 4] = 0x803ad0d8;
	this[0x360c / 4] = 0;

	// initialization of /Mario/DmgGraffitoWaterSurface.prm : mMotor
	TBaseParam(this + 0x3610/4, this + 0x35cc/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x3610 / 4] = 0x803ad0d8;
	this[0x3620 / 4] = 0;

	// initialization of /Mario/DmgGraffitoWaterSurface.prm : mMinSpeed
	TBaseParam(this + 0x3624/4, this + 0x35cc/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x3624 / 4] = 0x803abd30;
	this[0x3634 / 4] = 0;

	// initialization of /Mario/DmgGraffitoWaterSurface.prm : mDirty
	TBaseParam(this + 0x3638/4, this + 0x35cc/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x3638 / 4] = 0x803abd30;
	this[0x3648 / 4] = 0;

	// initialization of /Mario/DmgGraffitoWaterSurface.prm : mInvincibleTime
	TBaseParam(this + 0x364c/4, this + 0x35cc/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x364c / 4] = 0x803ad0f0;
	this[0x365c / 4] = 0;

	// loading of /Mario/DmgGraffitoWaterSurface.prm
	paramsLoad(this + 0x35cc / 4, this[0x35cc/4]);

	// initialization of /Mario/DmgMapCode0.prm
	this[0x3660 / 4] = prmStrBasePointer + 0x1a80;
	this[0x3664 / 4] = 0;

	// initialization of /Mario/DmgMapCode0.prm : mDamage
	TBaseParam(this + 0x3668/4, this + 0x3660/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x3668 / 4] = 0x803ad0d8;
	this[0x3678 / 4] = 0;

	// initialization of /Mario/DmgMapCode0.prm : mDownType
	TBaseParam(this + 0x367c/4, this + 0x3660/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x367c / 4] = 0x803ad0d8;
	this[0x368c / 4] = 0;

	// initialization of /Mario/DmgMapCode0.prm : mWaterEmit
	TBaseParam(this + 0x3690/4, this + 0x3660/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x3690 / 4] = 0x803ad0d8;
	this[0x36a0 / 4] = 0;

	// initialization of /Mario/DmgMapCode0.prm : mMotor
	TBaseParam(this + 0x36a4/4, this + 0x3660/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x36a4 / 4] = 0x803ad0d8;
	this[0x36b4 / 4] = 0;

	// initialization of /Mario/DmgMapCode0.prm : mMinSpeed
	TBaseParam(this + 0x36b8/4, this + 0x3660/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x36b8 / 4] = 0x803abd30;
	this[0x36c8 / 4] = 0;

	// initialization of /Mario/DmgMapCode0.prm : mDirty
	TBaseParam(this + 0x36cc/4, this + 0x3660/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x36cc / 4] = 0x803abd30;
	this[0x36dc / 4] = 0;

	// initialization of /Mario/DmgMapCode0.prm : mInvincibleTime
	TBaseParam(this + 0x36e0/4, this + 0x3660/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x36e0 / 4] = 0x803ad0f0;
	this[0x36f0 / 4] = 0;

	// loading of /Mario/DmgMapCode0.prm
	paramsLoad(this + 0x3660 / 4, this[0x3660/4]);

	// initialization of /Mario/DmgMapCode1.prm
	this[0x36f4 / 4] = prmStrBasePointer + 0x1a98;
	this[0x36f8 / 4] = 0;

	// initialization of /Mario/DmgMapCode1.prm : mDamage
	TBaseParam(this + 0x36fc/4, this + 0x36f4/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x36fc / 4] = 0x803ad0d8;
	this[0x370c / 4] = 0;

	// initialization of /Mario/DmgMapCode1.prm : mDownType
	TBaseParam(this + 0x3710/4, this + 0x36f4/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x3710 / 4] = 0x803ad0d8;
	this[0x3720 / 4] = 0;

	// initialization of /Mario/DmgMapCode1.prm : mWaterEmit
	TBaseParam(this + 0x3724/4, this + 0x36f4/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x3724 / 4] = 0x803ad0d8;
	this[0x3734 / 4] = 0;

	// initialization of /Mario/DmgMapCode1.prm : mMotor
	TBaseParam(this + 0x3738/4, this + 0x36f4/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x3738 / 4] = 0x803ad0d8;
	this[0x3748 / 4] = 0;

	// initialization of /Mario/DmgMapCode1.prm : mMinSpeed
	TBaseParam(this + 0x374c/4, this + 0x36f4/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x374c / 4] = 0x803abd30;
	this[0x375c / 4] = 0;

	// initialization of /Mario/DmgMapCode1.prm : mDirty
	TBaseParam(this + 0x3760/4, this + 0x36f4/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x3760 / 4] = 0x803abd30;
	this[0x3770 / 4] = 0;

	// initialization of /Mario/DmgMapCode1.prm : mInvincibleTime
	TBaseParam(this + 0x3774/4, this + 0x36f4/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x3774 / 4] = 0x803ad0f0;
	this[0x3784 / 4] = 0;

	// loading of /Mario/DmgMapCode1.prm
	paramsLoad(this + 0x36f4 / 4, this[0x36f4/4]);

	// initialization of /Mario/DmgMapCode2.prm
	this[0x3788 / 4] = prmStrBasePointer + 0x1ab0;
	this[0x378c / 4] = 0;

	// initialization of /Mario/DmgMapCode2.prm : mDamage
	TBaseParam(this + 0x3790/4, this + 0x3788/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x3790 / 4] = 0x803ad0d8;
	this[0x37a0 / 4] = 0;

	// initialization of /Mario/DmgMapCode2.prm : mDownType
	TBaseParam(this + 0x37a4/4, this + 0x3788/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x37a4 / 4] = 0x803ad0d8;
	this[0x37b4 / 4] = 0;

	// initialization of /Mario/DmgMapCode2.prm : mWaterEmit
	TBaseParam(this + 0x37b8/4, this + 0x3788/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x37b8 / 4] = 0x803ad0d8;
	this[0x37c8 / 4] = 0;

	// initialization of /Mario/DmgMapCode2.prm : mMotor
	TBaseParam(this + 0x37cc/4, this + 0x3788/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x37cc / 4] = 0x803ad0d8;
	this[0x37dc / 4] = 0;

	// initialization of /Mario/DmgMapCode2.prm : mMinSpeed
	TBaseParam(this + 0x37e0/4, this + 0x3788/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x37e0 / 4] = 0x803abd30;
	this[0x37f0 / 4] = 0;

	// initialization of /Mario/DmgMapCode2.prm : mDirty
	TBaseParam(this + 0x37f4/4, this + 0x3788/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x37f4 / 4] = 0x803abd30;
	this[0x3804 / 4] = 0;

	// initialization of /Mario/DmgMapCode2.prm : mInvincibleTime
	TBaseParam(this + 0x3808/4, this + 0x3788/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x3808 / 4] = 0x803ad0f0;
	this[0x3818 / 4] = 0;

	// loading of /Mario/DmgMapCode2.prm
	paramsLoad(this + 0x3788 / 4, this[0x3788/4]);

	// initialization of /Mario/DmgMapCode3.prm
	this[0x381c / 4] = prmStrBasePointer + 0x1ac8;
	this[0x3820 / 4] = 0;

	// initialization of /Mario/DmgMapCode3.prm : mDamage
	TBaseParam(this + 0x3824/4, this + 0x381c/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x3824 / 4] = 0x803ad0d8;
	this[0x3834 / 4] = 0;

	// initialization of /Mario/DmgMapCode3.prm : mDownType
	TBaseParam(this + 0x3838/4, this + 0x381c/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x3838 / 4] = 0x803ad0d8;
	this[0x3848 / 4] = 0;

	// initialization of /Mario/DmgMapCode3.prm : mWaterEmit
	TBaseParam(this + 0x384c/4, this + 0x381c/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x384c / 4] = 0x803ad0d8;
	this[0x385c / 4] = 0;

	// initialization of /Mario/DmgMapCode3.prm : mMotor
	TBaseParam(this + 0x3860/4, this + 0x381c/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x3860 / 4] = 0x803ad0d8;
	this[0x3870 / 4] = 0;

	// initialization of /Mario/DmgMapCode3.prm : mMinSpeed
	TBaseParam(this + 0x3874/4, this + 0x381c/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x3874 / 4] = 0x803abd30;
	this[0x3884 / 4] = 0;

	// initialization of /Mario/DmgMapCode3.prm : mDirty
	TBaseParam(this + 0x3888/4, this + 0x381c/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x3888 / 4] = 0x803abd30;
	this[0x3898 / 4] = 0;

	// initialization of /Mario/DmgMapCode3.prm : mInvincibleTime
	TBaseParam(this + 0x389c/4, this + 0x381c/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x389c / 4] = 0x803ad0f0;
	this[0x38ac / 4] = 0;

	// loading of /Mario/DmgMapCode3.prm
	paramsLoad(this + 0x381c / 4, this[0x381c/4]);

	// initialization of /Mario/DmgMapCode4.prm
	this[0x38b0 / 4] = prmStrBasePointer + 0x1ae0;
	this[0x38b4 / 4] = 0;

	// initialization of /Mario/DmgMapCode4.prm : mDamage
	TBaseParam(this + 0x38b8/4, this + 0x38b0/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x38b8 / 4] = 0x803ad0d8;
	this[0x38c8 / 4] = 0;

	// initialization of /Mario/DmgMapCode4.prm : mDownType
	TBaseParam(this + 0x38cc/4, this + 0x38b0/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x38cc / 4] = 0x803ad0d8;
	this[0x38dc / 4] = 0;

	// initialization of /Mario/DmgMapCode4.prm : mWaterEmit
	TBaseParam(this + 0x38e0/4, this + 0x38b0/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x38e0 / 4] = 0x803ad0d8;
	this[0x38f0 / 4] = 0;

	// initialization of /Mario/DmgMapCode4.prm : mMotor
	TBaseParam(this + 0x38f4/4, this + 0x38b0/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x38f4 / 4] = 0x803ad0d8;
	this[0x3904 / 4] = 0;

	// initialization of /Mario/DmgMapCode4.prm : mMinSpeed
	TBaseParam(this + 0x3908/4, this + 0x38b0/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x3908 / 4] = 0x803abd30;
	this[0x3918 / 4] = 0;

	// initialization of /Mario/DmgMapCode4.prm : mDirty
	TBaseParam(this + 0x391c/4, this + 0x38b0/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x391c / 4] = 0x803abd30;
	this[0x392c / 4] = 0;

	// initialization of /Mario/DmgMapCode4.prm : mInvincibleTime
	TBaseParam(this + 0x3930/4, this + 0x38b0/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x3930 / 4] = 0x803ad0f0;
	this[0x3940 / 4] = 0;

	// loading of /Mario/DmgMapCode4.prm
	paramsLoad(this + 0x38b0 / 4, this[0x38b0/4]);

	// initialization of /Mario/DmgMapCode5.prm
	this[0x3944 / 4] = prmStrBasePointer + 0x1af8;
	this[0x3948 / 4] = 0;

	// initialization of /Mario/DmgMapCode5.prm : mDamage
	TBaseParam(this + 0x394c/4, this + 0x3944/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x394c / 4] = 0x803ad0d8;
	this[0x395c / 4] = 0;

	// initialization of /Mario/DmgMapCode5.prm : mDownType
	TBaseParam(this + 0x3960/4, this + 0x3944/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x3960 / 4] = 0x803ad0d8;
	this[0x3970 / 4] = 0;

	// initialization of /Mario/DmgMapCode5.prm : mWaterEmit
	TBaseParam(this + 0x3974/4, this + 0x3944/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x3974 / 4] = 0x803ad0d8;
	this[0x3984 / 4] = 0;

	// initialization of /Mario/DmgMapCode5.prm : mMotor
	TBaseParam(this + 0x3988/4, this + 0x3944/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x3988 / 4] = 0x803ad0d8;
	this[0x3998 / 4] = 0;

	// initialization of /Mario/DmgMapCode5.prm : mMinSpeed
	TBaseParam(this + 0x399c/4, this + 0x3944/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x399c / 4] = 0x803abd30;
	this[0x39ac / 4] = 0;

	// initialization of /Mario/DmgMapCode5.prm : mDirty
	TBaseParam(this + 0x39b0/4, this + 0x3944/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x39b0 / 4] = 0x803abd30;
	this[0x39c0 / 4] = 0;

	// initialization of /Mario/DmgMapCode5.prm : mInvincibleTime
	TBaseParam(this + 0x39c4/4, this + 0x3944/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x39c4 / 4] = 0x803ad0f0;
	this[0x39d4 / 4] = 0;

	// loading of /Mario/DmgMapCode5.prm
	paramsLoad(this + 0x3944 / 4, this[0x3944/4]);

	// initialization of /Mario/DmgMapCode6.prm
	this[0x39d8 / 4] = prmStrBasePointer + 0x1b10;
	this[0x39dc / 4] = 0;

	// initialization of /Mario/DmgMapCode6.prm : mDamage
	TBaseParam(this + 0x39e0/4, this + 0x39d8/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x39e0 / 4] = 0x803ad0d8;
	this[0x39f0 / 4] = 0;

	// initialization of /Mario/DmgMapCode6.prm : mDownType
	TBaseParam(this + 0x39f4/4, this + 0x39d8/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x39f4 / 4] = 0x803ad0d8;
	this[0x3a04 / 4] = 0;

	// initialization of /Mario/DmgMapCode6.prm : mWaterEmit
	TBaseParam(this + 0x3a08/4, this + 0x39d8/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x3a08 / 4] = 0x803ad0d8;
	this[0x3a18 / 4] = 0;

	// initialization of /Mario/DmgMapCode6.prm : mMotor
	TBaseParam(this + 0x3a1c/4, this + 0x39d8/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x3a1c / 4] = 0x803ad0d8;
	this[0x3a2c / 4] = 0;

	// initialization of /Mario/DmgMapCode6.prm : mMinSpeed
	TBaseParam(this + 0x3a30/4, this + 0x39d8/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x3a30 / 4] = 0x803abd30;
	this[0x3a40 / 4] = 0;

	// initialization of /Mario/DmgMapCode6.prm : mDirty
	TBaseParam(this + 0x3a44/4, this + 0x39d8/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x3a44 / 4] = 0x803abd30;
	this[0x3a54 / 4] = 0;

	// initialization of /Mario/DmgMapCode6.prm : mInvincibleTime
	TBaseParam(this + 0x3a58/4, this + 0x39d8/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x3a58 / 4] = 0x803ad0f0;
	this[0x3a68 / 4] = 0;

	// loading of /Mario/DmgMapCode6.prm
	paramsLoad(this + 0x39d8 / 4, this[0x39d8/4]);

	// initialization of /Mario/DmgMapCode7.prm
	this[0x3a6c / 4] = prmStrBasePointer + 0x1b28;
	this[0x3a70 / 4] = 0;

	// initialization of /Mario/DmgMapCode7.prm : mDamage
	TBaseParam(this + 0x3a74/4, this + 0x3a6c/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x3a74 / 4] = 0x803ad0d8;
	this[0x3a84 / 4] = 0;

	// initialization of /Mario/DmgMapCode7.prm : mDownType
	TBaseParam(this + 0x3a88/4, this + 0x3a6c/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x3a88 / 4] = 0x803ad0d8;
	this[0x3a98 / 4] = 0;

	// initialization of /Mario/DmgMapCode7.prm : mWaterEmit
	TBaseParam(this + 0x3a9c/4, this + 0x3a6c/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x3a9c / 4] = 0x803ad0d8;
	this[0x3aac / 4] = 0;

	// initialization of /Mario/DmgMapCode7.prm : mMotor
	TBaseParam(this + 0x3ab0/4, this + 0x3a6c/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x3ab0 / 4] = 0x803ad0d8;
	this[0x3ac0 / 4] = 0;

	// initialization of /Mario/DmgMapCode7.prm : mMinSpeed
	TBaseParam(this + 0x3ac4/4, this + 0x3a6c/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x3ac4 / 4] = 0x803abd30;
	this[0x3ad4 / 4] = 0;

	// initialization of /Mario/DmgMapCode7.prm : mDirty
	TBaseParam(this + 0x3ad8/4, this + 0x3a6c/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x3ad8 / 4] = 0x803abd30;
	this[0x3ae8 / 4] = 0;

	// initialization of /Mario/DmgMapCode7.prm : mInvincibleTime
	TBaseParam(this + 0x3aec/4, this + 0x3a6c/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x3aec / 4] = 0x803ad0f0;
	this[0x3afc / 4] = 0;

	// loading of /Mario/DmgMapCode7.prm
	paramsLoad(this + 0x3a6c / 4, this[0x3a6c/4]);

	// initialization of /Mario/DmgMapCode8.prm
	this[0x3b00 / 4] = prmStrBasePointer + 0x1b40;
	this[0x3b04 / 4] = 0;

	// initialization of /Mario/DmgMapCode8.prm : mDamage
	TBaseParam(this + 0x3b08/4, this + 0x3b00/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x3b08 / 4] = 0x803ad0d8;
	this[0x3b18 / 4] = 0;

	// initialization of /Mario/DmgMapCode8.prm : mDownType
	TBaseParam(this + 0x3b1c/4, this + 0x3b00/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x3b1c / 4] = 0x803ad0d8;
	this[0x3b2c / 4] = 0;

	// initialization of /Mario/DmgMapCode8.prm : mWaterEmit
	TBaseParam(this + 0x3b30/4, this + 0x3b00/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x3b30 / 4] = 0x803ad0d8;
	this[0x3b40 / 4] = 0;

	// initialization of /Mario/DmgMapCode8.prm : mMotor
	TBaseParam(this + 0x3b44/4, this + 0x3b00/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x3b44 / 4] = 0x803ad0d8;
	this[0x3b54 / 4] = 0;

	// initialization of /Mario/DmgMapCode8.prm : mMinSpeed
	TBaseParam(this + 0x3b58/4, this + 0x3b00/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x3b58 / 4] = 0x803abd30;
	this[0x3b68 / 4] = 0;

	// initialization of /Mario/DmgMapCode8.prm : mDirty
	TBaseParam(this + 0x3b6c/4, this + 0x3b00/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x3b6c / 4] = 0x803abd30;
	this[0x3b7c / 4] = 0;

	// initialization of /Mario/DmgMapCode8.prm : mInvincibleTime
	TBaseParam(this + 0x3b80/4, this + 0x3b00/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x3b80 / 4] = 0x803ad0f0;
	this[0x3b90 / 4] = 0;

	// loading of /Mario/DmgMapCode8.prm
	paramsLoad(this + 0x3b00 / 4, this[0x3b00/4]);

	// initialization of /Mario/DmgMapCode9.prm
	this[0x3b94 / 4] = prmStrBasePointer + 0x1b58;
	this[0x3b98 / 4] = 0;

	// initialization of /Mario/DmgMapCode9.prm : mDamage
	TBaseParam(this + 0x3b9c/4, this + 0x3b94/4, calcKeyCode(r2 - 0xa68), r2 - 0xa68);
	this[0x3b9c / 4] = 0x803ad0d8;
	this[0x3bac / 4] = 0;

	// initialization of /Mario/DmgMapCode9.prm : mDownType
	TBaseParam(this + 0x3bb0/4, this + 0x3b94/4, calcKeyCode(prmStrBasePointer + 0x114), prmStrBasePointer + 0x114);
	this[0x3bb0 / 4] = 0x803ad0d8;
	this[0x3bc0 / 4] = 0;

	// initialization of /Mario/DmgMapCode9.prm : mWaterEmit
	TBaseParam(this + 0x3bc4/4, this + 0x3b94/4, calcKeyCode(prmStrBasePointer + 0x120), prmStrBasePointer + 0x120);
	this[0x3bc4 / 4] = 0x803ad0d8;
	this[0x3bd4 / 4] = 0;

	// initialization of /Mario/DmgMapCode9.prm : mMotor
	TBaseParam(this + 0x3bd8/4, this + 0x3b94/4, calcKeyCode(r2 - 0xa60), r2 - 0xa60);
	this[0x3bd8 / 4] = 0x803ad0d8;
	this[0x3be8 / 4] = 0;

	// initialization of /Mario/DmgMapCode9.prm : mMinSpeed
	TBaseParam(this + 0x3bec/4, this + 0x3b94/4, calcKeyCode(prmStrBasePointer + 0x12c), prmStrBasePointer + 0x12c);
	this[0x3bec / 4] = 0x803abd30;
	this[0x3bfc / 4] = 0;

	// initialization of /Mario/DmgMapCode9.prm : mDirty
	TBaseParam(this + 0x3c00/4, this + 0x3b94/4, calcKeyCode(r2 - 0xa54), r2 - 0xa54);
	this[0x3c00 / 4] = 0x803abd30;
	this[0x3c10 / 4] = 0;

	// initialization of /Mario/DmgMapCode9.prm : mInvincibleTime
	TBaseParam(this + 0x3c14/4, this + 0x3b94/4, calcKeyCode(prmStrBasePointer + 0x138), prmStrBasePointer + 0x138);
	this[0x3c14 / 4] = 0x803ad0f0;
	this[0x3c24 / 4] = 0;

	// loading of /Mario/DmgMapCode9.prm
	paramsLoad(this + 0x3b94 / 4, this[0x3b94/4]);

	// initialization of /Mario/AutoDemo.prm
	this[0x3c28 / 4] = prmStrBasePointer + 0x80;
	this[0x3c2c / 4] = 0;

	// initialization of /Mario/AutoDemo.prm : mWarpInBallsDispTime
	TBaseParam(this + 0x3c30/4, this + 0x3c28/4, calcKeyCode(prmStrBasePointer + 0x94), prmStrBasePointer + 0x94);
	this[0x3c30 / 4] = 0x803ad0f0;
	this[0x3c40 / 4] = 0;

	// initialization of /Mario/AutoDemo.prm : mWarpInBallsTime
	TBaseParam(this + 0x3c44/4, this + 0x3c28/4, calcKeyCode(prmStrBasePointer + 0xac), prmStrBasePointer + 0xac);
	this[0x3c44 / 4] = 0x803ad0f0;
	this[0x3c54 / 4] = 0;

	// initialization of /Mario/AutoDemo.prm : mWarpInCapturedTime
	TBaseParam(this + 0x3c58/4, this + 0x3c28/4, calcKeyCode(prmStrBasePointer + 0xc0), prmStrBasePointer + 0xc0);
	this[0x3c58 / 4] = 0x803ad0f0;
	this[0x3c68 / 4] = 0;

	// initialization of /Mario/AutoDemo.prm : mWarpInTremble
	TBaseParam(this + 0x3c6c/4, this + 0x3c28/4, calcKeyCode(prmStrBasePointer + 0xd4), prmStrBasePointer + 0xd4);
	this[0x3c6c / 4] = 0x803abd30;
	this[0x3c7c / 4] = 0;

	// initialization of /Mario/AutoDemo.prm : mWarpInVecBase
	TBaseParam(this + 0x3c80/4, this + 0x3c28/4, calcKeyCode(prmStrBasePointer + 0xe4), prmStrBasePointer + 0xe4);
	this[0x3c80 / 4] = 0x803abd30;
	this[0x3c90 / 4] = 0;

	// initialization of /Mario/AutoDemo.prm : mWarpTransTremble
	TBaseParam(this + 0x3c94/4, this + 0x3c28/4, calcKeyCode(prmStrBasePointer + 0xf4), prmStrBasePointer + 0xf4);
	this[0x3c94 / 4] = 0x803abd30;
	this[0x3ca4 / 4] = 0;

	// initialization of /Mario/AutoDemo.prm : mReadRotSp
	TBaseParam(this + 0x3ca8/4, this + 0x3c28/4, calcKeyCode(prmStrBasePointer + 0x108), prmStrBasePointer + 0x108);
	this[0x3ca8 / 4] = 0x803ad0f0;
	this[0x3cb8 / 4] = 0;

	// loading of /Mario/AutoDemo.prm
	paramsLoad(this + 0x3c28 / 4, this[0x3c28/4]);

	// initialization of /Mario/Sound.prm
	this[0x3cbc / 4] = prmStrBasePointer + 0x54;
	this[0x3cc0 / 4] = 0;

	// initialization of /Mario/Sound.prm : mStartFallVoiceSpeed
	TBaseParam(this + 0x3cc4/4, this + 0x3cbc/4, calcKeyCode(prmStrBasePointer + 0x68), prmStrBasePointer + 0x68);
	this[0x3cc4 / 4] = 0x803abd30;
	this[0x3cd4 / 4] = 0;

	// loading of /Mario/Sound.prm
	paramsLoad(this + 0x3cbc / 4, this[0x3cbc/4]);

	// initialization of /Mario/Option.prm
	this[0x3cd8 / 4] = prmStrBasePointer + 0x1b70;
	this[0x3cdc / 4] = 0;

	// initialization of /Mario/Option.prm : mZ
	TBaseParam(this + 0x3ce0/4, this + 0x3cd8/4, calcKeyCode(r2 - 0xa98), r2 - 0xa98);
	this[0x3ce0 / 4] = 0x803abd30;
	this[0x3cf0 / 4] = 0;

	// initialization of /Mario/Option.prm : mXMin
	TBaseParam(this + 0x3cf4/4, this + 0x3cd8/4, calcKeyCode(r2 - 0xa90), r2 - 0xa90);
	this[0x3cf4 / 4] = 0x803abd30;
	this[0x3d04 / 4] = 0;

	// initialization of /Mario/Option.prm : mXMax
	TBaseParam(this + 0x3d08/4, this + 0x3cd8/4, calcKeyCode(r2 - 0xa84), r2 - 0xa84);
	this[0x3d08 / 4] = 0x803abd30;
	this[0x3d18 / 4] = 0;
}*/
