#include "defines.h"

// Overwrites loading from mHPMax at 80044cc4
void paramsReplace_initValues_80044cc4() {
	toRegister(0, ((short *)newMarioParams)[0xc]);
	__asm("b paramsReplace_initValues_80044cc4_b");
}

// Overwrites loading from mDamage at 802401f8
void paramsReplace_electricDamage_802401f8() {
	toRegister(4, ((char *)newMarioParams)[0x34bc]);
	__asm("b paramsReplace_electricDamage_802401f8_b");
}

// Overwrites loading from mWaterEmit at 802402ec
void paramsReplace_electricDamage_802402ec() {
	toRegister(7, ((char *)newMarioParams)[0x34e4]);
	__asm("b paramsReplace_electricDamage_802402ec_b");
}

// Overwrites loading from mMinSpeed at 802402f4
void paramsReplace_electricDamage_802402f4() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x350c (9)");
	__asm("b paramsReplace_electricDamage_802402f4_b");
}

// Overwrites loading from mMotor at 802402fc
void paramsReplace_electricDamage_802402fc() {
	toRegister(8, ((char *)newMarioParams)[0x34f8]);
	__asm("b paramsReplace_electricDamage_802402fc_b");
}

// Overwrites loading from mWarpInTremble at 80240f10
void paramsReplace_warpIn_80240f10() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x3c7c (9)");
	__asm("b paramsReplace_warpIn_80240f10_b");
}

// Overwrites loading from mWarpInBallsDispTime at 80240f68
void paramsReplace_warpIn_80240f68() {
	toRegister(0, ((short *)newMarioParams)[0x1e20]);
	__asm("b paramsReplace_warpIn_80240f68_b");
}

// Overwrites loading from mWarpInBallsTime at 80240fc4
void paramsReplace_warpIn_80240fc4() {
	toRegister(0, ((short *)newMarioParams)[0x1e2a]);
	__asm("b paramsReplace_warpIn_80240fc4_b");
}

// Overwrites loading from mWarpInVecBase at 80241010
void paramsReplace_warpIn_80241010() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x3c90 (9)");
	__asm("b paramsReplace_warpIn_80241010_b");
}

// Overwrites loading from mMotorWall at 80241034
void paramsReplace_warpIn_80241034() {
	toRegister(0, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_warpIn_80241034_b");
}

// Overwrites loading from mWarpInCapturedTime at 80241044
void paramsReplace_warpIn_80241044() {
	toRegister(0, ((short *)newMarioParams)[0x1e34]);
	__asm("b paramsReplace_warpIn_80241044_b");
}

// Overwrites loading from mReadRotSp at 802412dc
void paramsReplace_readBillboard_802412dc() {
	toRegister(5, ((short *)newMarioParams)[0x1e5c]);
	__asm("b paramsReplace_readBillboard_802412dc_b");
}

// Overwrites loading from mMotorTrample at 802433f0
void paramsReplace_trampleExec_802433f0() {
	toRegister(5, ((short *)newMarioParams)[0x112e]);
	__asm("b paramsReplace_trampleExec_802433f0_b");
}

// Overwrites loading from mHPMax at 802439ec
void paramsReplace_incHP_802439ec() {
	toRegister(3, ((short *)newMarioParams)[0xc]);
	__asm("b paramsReplace_incHP_802439ec_b");
}

// Overwrites loading from mFogTimeYellow at 80243de0
void paramsReplace_addDamageFog_80243de0() {
	toRegister(0, ((short *)newMarioParams)[0x110c]);
	__asm("b paramsReplace_addDamageFog_80243de0_b");
}

// Overwrites loading from mPumpAnmSpeed at 80244f84
void paramsReplace_addUpper_80244f84() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2b24 (9)");
	__asm("b paramsReplace_addUpper_80244f84_b");
}

// Overwrites loading from mPitchMax at 80245b88
void paramsReplace_calcBaseMtx_80245b88() {
	toRegister(5, ((short *)newMarioParams)[0x8ee]);
	__asm("b paramsReplace_calcBaseMtx_80245b88_b");
}

// Overwrites loading from mPitch at 80245ba0
void paramsReplace_calcBaseMtx_80245ba0() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x11b4 (9)");
	__asm("b paramsReplace_calcBaseMtx_80245ba0_b");
}

// Overwrites loading from mRoll at 80245bb0
void paramsReplace_calcBaseMtx_80245bb0() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x11a0 (9)");
	__asm("b paramsReplace_calcBaseMtx_80245bb0_b");
}

// Overwrites loading from mRollMax at 80245bb8
void paramsReplace_calcBaseMtx_80245bb8() {
	toRegister(6, ((short *)newMarioParams)[0x8e4]);
	__asm("b paramsReplace_calcBaseMtx_80245bb8_b");
}

// Overwrites loading from mAngleChangeRate at 80245c5c
void paramsReplace_calcBaseMtx_80245c5c() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x11f0 (9)");
	__asm("b paramsReplace_calcBaseMtx_80245c5c_b");
}

// Overwrites loading from mAngleChangeRate at 80245c90
void paramsReplace_calcBaseMtx_80245c90() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x11f0 (9)");
	__asm("b paramsReplace_calcBaseMtx_80245c90_b");
}

// Overwrites loading from mPitchMax at 80245cb0
void paramsReplace_calcBaseMtx_80245cb0() {
	toRegister(5, ((short *)newMarioParams)[0x9d8]);
	__asm("b paramsReplace_calcBaseMtx_80245cb0_b");
}

// Overwrites loading from mPitch at 80245cc8
void paramsReplace_calcBaseMtx_80245cc8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1388 (9)");
	__asm("b paramsReplace_calcBaseMtx_80245cc8_b");
}

// Overwrites loading from mRoll at 80245cd8
void paramsReplace_calcBaseMtx_80245cd8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1374 (9)");
	__asm("b paramsReplace_calcBaseMtx_80245cd8_b");
}

// Overwrites loading from mRollMax at 80245ce0
void paramsReplace_calcBaseMtx_80245ce0() {
	toRegister(6, ((short *)newMarioParams)[0x9ce]);
	__asm("b paramsReplace_calcBaseMtx_80245ce0_b");
}

// Overwrites loading from mAngleChangeRate at 80245d84
void paramsReplace_calcBaseMtx_80245d84() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x13c4 (9)");
	__asm("b paramsReplace_calcBaseMtx_80245d84_b");
}

// Overwrites loading from mAngleChangeRate at 80245db8
void paramsReplace_calcBaseMtx_80245db8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x13c4 (9)");
	__asm("b paramsReplace_calcBaseMtx_80245db8_b");
}

// Overwrites loading from mSinkTime at 80245e74
void paramsReplace_calcBaseMtx_80245e74() {
	toRegister(4, ((short *)newMarioParams)[0xf5a]);
	__asm("b paramsReplace_calcBaseMtx_80245e74_b");
}

// Overwrites loading from mSinkHeight at 80245e98
void paramsReplace_calcBaseMtx_80245e98() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1edc (9)");
	__asm("b paramsReplace_calcBaseMtx_80245e98_b");
}

// Overwrites loading from mWaistPitchMax at 80246050
void paramsReplace_considerWaist_80246050() {
	toRegister(3, ((short *)newMarioParams)[0x8c6]);
	__asm("b paramsReplace_considerWaist_80246050_b");
}

// Overwrites loading from mWaistPitch at 80246060
void paramsReplace_considerWaist_80246060() {
	toRegister(9, newMarioParams);
	__asm("lfs 3, 0x1164 (9)");
	__asm("b paramsReplace_considerWaist_80246060_b");
}

// Overwrites loading from mWaistAngleChangeRate at 80246068
void paramsReplace_considerWaist_80246068() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x1204 (9)");
	__asm("b paramsReplace_considerWaist_80246068_b");
}

// Overwrites loading from mWaistPitchMax at 8024607c
void paramsReplace_considerWaist_8024607c() {
	toRegister(3, ((short *)newMarioParams)[0x9b0]);
	__asm("b paramsReplace_considerWaist_8024607c_b");
}

// Overwrites loading from mWaistPitch at 8024608c
void paramsReplace_considerWaist_8024608c() {
	toRegister(9, newMarioParams);
	__asm("lfs 3, 0x1338 (9)");
	__asm("b paramsReplace_considerWaist_8024608c_b");
}

// Overwrites loading from mWaistAngleChangeRate at 80246094
void paramsReplace_considerWaist_80246094() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x13d8 (9)");
	__asm("b paramsReplace_considerWaist_80246094_b");
}

// Overwrites loading from mWaistPitchMax at 80246108
void paramsReplace_considerWaist_80246108() {
	toRegister(3, ((short *)newMarioParams)[0x28a]);
	__asm("b paramsReplace_considerWaist_80246108_b");
}

// Overwrites loading from mWaistPitch at 80246118
void paramsReplace_considerWaist_80246118() {
	toRegister(9, newMarioParams);
	__asm("lfs 3, 0x4ec (9)");
	__asm("b paramsReplace_considerWaist_80246118_b");
}

// Overwrites loading from mWaistAngleChangeRate at 80246120
void paramsReplace_considerWaist_80246120() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x528 (9)");
	__asm("b paramsReplace_considerWaist_80246120_b");
}

// Overwrites loading from mWaistPitchMax at 80246134
void paramsReplace_considerWaist_80246134() {
	toRegister(3, ((short *)newMarioParams)[0x24a]);
	__asm("b paramsReplace_considerWaist_80246134_b");
}

// Overwrites loading from mWaistPitch at 80246144
void paramsReplace_considerWaist_80246144() {
	toRegister(9, newMarioParams);
	__asm("lfs 3, 0x46c (9)");
	__asm("b paramsReplace_considerWaist_80246144_b");
}

// Overwrites loading from mWaistAngleChangeRate at 8024614c
void paramsReplace_considerWaist_8024614c() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x4a8 (9)");
	__asm("b paramsReplace_considerWaist_8024614c_b");
}

// Overwrites loading from mWaistRollMax at 80246204
void paramsReplace_considerWaist_80246204() {
	toRegister(3, ((short *)newMarioParams)[0x8bc]);
	__asm("b paramsReplace_considerWaist_80246204_b");
}

// Overwrites loading from mWaistRoll at 80246214
void paramsReplace_considerWaist_80246214() {
	toRegister(9, newMarioParams);
	__asm("lfs 4, 0x1150 (9)");
	__asm("b paramsReplace_considerWaist_80246214_b");
}

// Overwrites loading from mWaistAngleChangeRate at 8024621c
void paramsReplace_considerWaist_8024621c() {
	toRegister(9, newMarioParams);
	__asm("lfs 3, 0x1204 (9)");
	__asm("b paramsReplace_considerWaist_8024621c_b");
}

// Overwrites loading from mWaistRollMax at 80246230
void paramsReplace_considerWaist_80246230() {
	toRegister(3, ((short *)newMarioParams)[0x9a6]);
	__asm("b paramsReplace_considerWaist_80246230_b");
}

// Overwrites loading from mWaistRoll at 80246240
void paramsReplace_considerWaist_80246240() {
	toRegister(9, newMarioParams);
	__asm("lfs 4, 0x1324 (9)");
	__asm("b paramsReplace_considerWaist_80246240_b");
}

// Overwrites loading from mWaistAngleChangeRate at 80246248
void paramsReplace_considerWaist_80246248() {
	toRegister(9, newMarioParams);
	__asm("lfs 3, 0x13d8 (9)");
	__asm("b paramsReplace_considerWaist_80246248_b");
}

// Overwrites loading from mWaistRollMax at 8024629c
void paramsReplace_considerWaist_8024629c() {
	toRegister(3, ((short *)newMarioParams)[0x280]);
	__asm("b paramsReplace_considerWaist_8024629c_b");
}

// Overwrites loading from mWaistRoll at 802462ac
void paramsReplace_considerWaist_802462ac() {
	toRegister(9, newMarioParams);
	__asm("lfs 4, 0x4d8 (9)");
	__asm("b paramsReplace_considerWaist_802462ac_b");
}

// Overwrites loading from mWaistAngleChangeRate at 802462b4
void paramsReplace_considerWaist_802462b4() {
	toRegister(9, newMarioParams);
	__asm("lfs 3, 0x528 (9)");
	__asm("b paramsReplace_considerWaist_802462b4_b");
}

// Overwrites loading from mWaistRollMax at 802462c8
void paramsReplace_considerWaist_802462c8() {
	toRegister(3, ((short *)newMarioParams)[0x240]);
	__asm("b paramsReplace_considerWaist_802462c8_b");
}

// Overwrites loading from mWaistRoll at 802462d8
void paramsReplace_considerWaist_802462d8() {
	toRegister(9, newMarioParams);
	__asm("lfs 4, 0x458 (9)");
	__asm("b paramsReplace_considerWaist_802462d8_b");
}

// Overwrites loading from mWaistAngleChangeRate at 802462e0
void paramsReplace_considerWaist_802462e0() {
	toRegister(9, newMarioParams);
	__asm("lfs 3, 0x4a8 (9)");
	__asm("b paramsReplace_considerWaist_802462e0_b");
}

// Overwrites loading from mHoverHeadAngle at 80248cc4
void paramsReplace_MarioHeadCtrl_80248cc4() {
	toRegister(4, ((short *)newMarioParams)[0x159c]);
	__asm("b paramsReplace_MarioHeadCtrl_80248cc4_b");
}

// Overwrites loading from mFeelDeep at 80248d0c
void paramsReplace_MarioHeadCtrl_80248d0c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x338 (9)");
	__asm("b paramsReplace_MarioHeadCtrl_80248d0c_b");
}

// Overwrites loading from mFeelDeepHeadAngle at 80248d2c
void paramsReplace_MarioHeadCtrl_80248d2c() {
	toRegister(4, ((short *)newMarioParams)[0x15a6]);
	__asm("b paramsReplace_MarioHeadCtrl_80248d2c_b");
}

// Overwrites loading from mFrontWallHeadAngle at 80248d84
void paramsReplace_MarioHeadCtrl_80248d84() {
	toRegister(4, ((short *)newMarioParams)[0x15b0]);
	__asm("b paramsReplace_MarioHeadCtrl_80248d84_b");
}

// Overwrites loading from mHeadRot at 80248dfc
void paramsReplace_MarioHeadCtrl_80248dfc() {
	toRegister(9, newMarioParams);
	__asm("lfs 5, 0x4c4 (9)");
	__asm("b paramsReplace_MarioHeadCtrl_80248dfc_b");
}

// Overwrites loading from mHeadRot at 80248e04
void paramsReplace_MarioHeadCtrl_80248e04() {
	toRegister(9, newMarioParams);
	__asm("lfs 5, 0x444 (9)");
	__asm("b paramsReplace_MarioHeadCtrl_80248e04_b");
}

// Overwrites loading from mMotorWall at 80249580
void paramsReplace_jumpMain_80249580() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_jumpMain_80249580_b");
}

// Overwrites loading from mMotorWall at 80249654
void paramsReplace_jumpMain_80249654() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_jumpMain_80249654_b");
}

// Overwrites loading from mJumpJumpCatchSp at 802496a4
void paramsReplace_jumpMain_802496a4() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x900 (9)");
	__asm("b paramsReplace_jumpMain_802496a4_b");
}

// Overwrites loading from mJumpJumpCatchSp at 80249764
void paramsReplace_jumpMain_80249764() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x900 (9)");
	__asm("b paramsReplace_jumpMain_80249764_b");
}

// Overwrites loading from mJumpJumpCatchSp at 802498cc
void paramsReplace_jumpMain_802498cc() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x900 (9)");
	__asm("b paramsReplace_jumpMain_802498cc_b");
}

// Overwrites loading from mJumpJumpCatchSp at 80249994
void paramsReplace_jumpMain_80249994() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x900 (9)");
	__asm("b paramsReplace_jumpMain_80249994_b");
}

// Overwrites loading from mJumpJumpCatchSp at 80249c68
void paramsReplace_jumpMain_80249c68() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x900 (9)");
	__asm("b paramsReplace_jumpMain_80249c68_b");
}

// Overwrites loading from mMotorWall at 80249d38
void paramsReplace_jumpMain_80249d38() {
	toRegister(0, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_jumpMain_80249d38_b");
}

// Overwrites loading from mAccelControl at 8024a404
void paramsReplace_diving_8024a404() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x1c50 (9)");
	__asm("b paramsReplace_diving_8024a404_b");
}

// Overwrites loading from mRotSp at 8024a4c4
void paramsReplace_diving_8024a4c4() {
	toRegister(5, ((short *)newMarioParams)[0xe14]);
	__asm("b paramsReplace_diving_8024a4c4_b");
}

// Overwrites loading from mSeaBrake at 8024a60c
void paramsReplace_diving_8024a60c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1c64 (9)");
	__asm("b paramsReplace_diving_8024a60c_b");
}

// Overwrites loading from mSeaBrakeY at 8024a670
void paramsReplace_diving_8024a670() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1c78 (9)");
	__asm("b paramsReplace_diving_8024a670_b");
}

// Overwrites loading from mSuperHipAttackCt at 8024a940
void paramsReplace_hipAttacking_8024a940() {
	toRegister(0, ((short *)newMarioParams)[0x494]);
	__asm("b paramsReplace_hipAttacking_8024a940_b");
}

// Overwrites loading from mHipAttackSpeedY at 8024a960
void paramsReplace_hipAttacking_8024a960() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x70c (9)");
	__asm("b paramsReplace_hipAttacking_8024a960_b");
}

// Overwrites loading from mSuperHipAttackSpeedY at 8024a96c
void paramsReplace_hipAttacking_8024a96c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x720 (9)");
	__asm("b paramsReplace_hipAttacking_8024a96c_b");
}

// Overwrites loading from mHipdropRadius at 8024a994
void paramsReplace_hipAttacking_8024a994() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x220 (9)");
	__asm("b paramsReplace_hipAttacking_8024a994_b");
}

// Overwrites loading from mAttackHeight at 8024a9a4
void paramsReplace_hipAttacking_8024a9a4() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1d0 (9)");
	__asm("b paramsReplace_hipAttacking_8024a9a4_b");
}

// Overwrites loading from mMotorWall at 8024abf8
void paramsReplace_hipAttacking_8024abf8() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_hipAttacking_8024abf8_b");
}

// Overwrites loading from mAccelControl at 8024ae6c
void paramsReplace_rocketing_8024ae6c() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x1c50 (9)");
	__asm("b paramsReplace_rocketing_8024ae6c_b");
}

// Overwrites loading from mRotSp at 8024af28
void paramsReplace_rocketing_8024af28() {
	toRegister(5, ((short *)newMarioParams)[0xdf2]);
	__asm("b paramsReplace_rocketing_8024af28_b");
}

// Overwrites loading from mAccelRate at 8024afd4
void paramsReplace_rocketing_8024afd4() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1bf8 (9)");
	__asm("b paramsReplace_rocketing_8024afd4_b");
}

// Overwrites loading from mBrake at 8024afe8
void paramsReplace_rocketing_8024afe8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1c0c (9)");
	__asm("b paramsReplace_rocketing_8024afe8_b");
}

// Overwrites loading from mMotorWall at 8024b018
void paramsReplace_rocketing_8024b018() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_rocketing_8024b018_b");
}

// Overwrites loading from mTrampleRadius at 8024b1d0
void paramsReplace_boardJumping_8024b1d0() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1e4 (9)");
	__asm("b paramsReplace_boardJumping_8024b1d0_b");
}

// Overwrites loading from mAttackHeight at 8024b1e0
void paramsReplace_boardJumping_8024b1e0() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1d0 (9)");
	__asm("b paramsReplace_boardJumping_8024b1e0_b");
}

// Overwrites loading from mPushupRadius at 8024b1f4
void paramsReplace_boardJumping_8024b1f4() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1f8 (9)");
	__asm("b paramsReplace_boardJumping_8024b1f4_b");
}

// Overwrites loading from mPushupHeight at 8024b204
void paramsReplace_boardJumping_8024b204() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x20c (9)");
	__asm("b paramsReplace_boardJumping_8024b204_b");
}

// Overwrites loading from mClashAngle at 8024b2c4
void paramsReplace_boardJumping_8024b2c4() {
	toRegister(4, ((short *)newMarioParams)[0x952]);
	__asm("b paramsReplace_boardJumping_8024b2c4_b");
}

// Overwrites loading from mClashSpeed at 8024b2e8
void paramsReplace_boardJumping_8024b2e8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1290 (9)");
	__asm("b paramsReplace_boardJumping_8024b2e8_b");
}

// Overwrites loading from mThrownAccel at 8024b398
void paramsReplace_thrownDowning_8024b398() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x860 (9)");
	__asm("b paramsReplace_thrownDowning_8024b398_b");
}

// Overwrites loading from mThrownSlide at 8024b3dc
void paramsReplace_thrownDowning_8024b3dc() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x874 (9)");
	__asm("b paramsReplace_thrownDowning_8024b3dc_b");
}

// Overwrites loading from mThrownBrake at 8024b3fc
void paramsReplace_thrownDowning_8024b3fc() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x888 (9)");
	__asm("b paramsReplace_thrownDowning_8024b3fc_b");
}

// Overwrites loading from mFireDownControl at 8024b594
void paramsReplace_fireDowning_8024b594() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x658 (9)");
	__asm("b paramsReplace_fireDowning_8024b594_b");
}

// Overwrites loading from mJumpSpeedBrake at 8024b7e8
void paramsReplace_slipFalling_8024b7e8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x5e0 (9)");
	__asm("b paramsReplace_slipFalling_8024b7e8_b");
}

// Overwrites loading from mMotorWall at 8024b9c8
void paramsReplace_slipFalling_8024b9c8() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_slipFalling_8024b9c8_b");
}

// Overwrites loading from mJumpJumpCatchSp at 8024bc50
void paramsReplace_stayWall_8024bc50() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x900 (9)");
	__asm("b paramsReplace_stayWall_8024bc50_b");
}

// Overwrites loading from mDamageFallHeight at 8024bfc8
void paramsReplace_jumpCatch_8024bfc8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x34c (9)");
	__asm("b paramsReplace_jumpCatch_8024bfc8_b");
}

// Overwrites loading from mJumpJumpCatchSp at 8024c27c
void paramsReplace_landing_8024c27c() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x900 (9)");
	__asm("b paramsReplace_landing_8024c27c_b");
}

// Overwrites loading from mJumpJumpCatchSp at 8024c3a0
void paramsReplace_checkBackTrig_8024c3a0() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x900 (9)");
	__asm("b paramsReplace_checkBackTrig_8024c3a0_b");
}

// Overwrites loading from mDamageFallHeight at 8024c528
void paramsReplace_jumpingBasic_8024c528() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x34c (9)");
	__asm("b paramsReplace_jumpingBasic_8024c528_b");
}

// Overwrites loading from mTrembleBrake at 8024c6ac
void paramsReplace_jumpingBasic_8024c6ac() {
	toRegister(9, newMarioParams);
	__asm("lfs 3, 0x8c4 (9)");
	__asm("b paramsReplace_jumpingBasic_8024c6ac_b");
}

// Overwrites loading from mTrembleAccele at 8024c6b0
void paramsReplace_jumpingBasic_8024c6b0() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x8b0 (9)");
	__asm("b paramsReplace_jumpingBasic_8024c6b0_b");
}

// Overwrites loading from mTremblePower at 8024c6b4
void paramsReplace_jumpingBasic_8024c6b4() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x89c (9)");
	__asm("b paramsReplace_jumpingBasic_8024c6b4_b");
}

// Overwrites loading from mMotorHipDrop at 8024c6d0
void paramsReplace_jumpingBasic_8024c6d0() {
	toRegister(5, ((short *)newMarioParams)[0x1138]);
	__asm("b paramsReplace_jumpingBasic_8024c6d0_b");
}

// Overwrites loading from mMotorReturn at 8024c728
void paramsReplace_jumpingBasic_8024c728() {
	toRegister(7, ((short *)newMarioParams)[0x1124]);
	__asm("b paramsReplace_jumpingBasic_8024c728_b");
}

// Overwrites loading from mMotorWall at 8024c764
void paramsReplace_jumpingBasic_8024c764() {
	toRegister(0, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_jumpingBasic_8024c764_b");
}

// Overwrites loading from mClashSpeed at 8024c7c4
void paramsReplace_jumpingBasic_8024c7c4() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x374 (9)");
	__asm("b paramsReplace_jumpingBasic_8024c7c4_b");
}

// Overwrites loading from mMotorWall at 8024c8e4
void paramsReplace_jumpingBasic_8024c8e4() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_jumpingBasic_8024c8e4_b");
}

// Overwrites loading from mMotorWall at 8024c978
void paramsReplace_jumpingBasic_8024c978() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_jumpingBasic_8024c978_b");
}

// Overwrites loading from mMotorWall at 8024ca98
void paramsReplace_jumpingBasic_8024ca98() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_jumpingBasic_8024ca98_b");
}

// Overwrites loading from mJumpSpeedBrake at 8024cafc
void paramsReplace_doJumping_8024cafc() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x5e0 (9)");
	__asm("b paramsReplace_doJumping_8024cafc_b");
}

// Overwrites loading from mHoldOutAccCtrlF at 8024cbf0
void paramsReplace_doJumping_8024cbf0() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x1cf8 (9)");
	__asm("b paramsReplace_doJumping_8024cbf0_b");
}

// Overwrites loading from mHoldOutAccCtrlB at 8024cbf8
void paramsReplace_doJumping_8024cbf8() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x1d0c (9)");
	__asm("b paramsReplace_doJumping_8024cbf8_b");
}

// Overwrites loading from mTrampleRadius at 8024cd4c
void paramsReplace_doJumping_8024cd4c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1e4 (9)");
	__asm("b paramsReplace_doJumping_8024cd4c_b");
}

// Overwrites loading from mAttackHeight at 8024cd5c
void paramsReplace_doJumping_8024cd5c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1d0 (9)");
	__asm("b paramsReplace_doJumping_8024cd5c_b");
}

// Overwrites loading from mPushupRadius at 8024cd70
void paramsReplace_doJumping_8024cd70() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1f8 (9)");
	__asm("b paramsReplace_doJumping_8024cd70_b");
}

// Overwrites loading from mPushupHeight at 8024cd80
void paramsReplace_doJumping_8024cd80() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x20c (9)");
	__asm("b paramsReplace_doJumping_8024cd80_b");
}

// Overwrites loading from mNoFreezeTime at 8024d364
void paramsReplace_perform_8024d364() {
	toRegister(0, ((short *)newMarioParams)[0x1d8]);
	__asm("b paramsReplace_perform_8024d364_b");
}

// Overwrites loading from mToroccoRotSp at 8024dff8
void paramsReplace_playerControl_8024dff8() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2fc (9)");
	__asm("b paramsReplace_playerControl_8024dff8_b");
}

// Overwrites loading from mFootEraseFront at 8024e680
void paramsReplace_gunExec_8024e680() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2044 (9)");
	__asm("b paramsReplace_gunExec_8024e680_b");
}

// Overwrites loading from mFootEraseSize at 8024e688
void paramsReplace_gunExec_8024e688() {
	toRegister(9, newMarioParams);
	__asm("lfs 31, 0x2030 (9)");
	__asm("b paramsReplace_gunExec_8024e688_b");
}

// Overwrites loading from mFootEraseTimes at 8024e718
void paramsReplace_gunExec_8024e718() {
	toRegister(0, ((short *)newMarioParams)[0x100e]);
	__asm("b paramsReplace_gunExec_8024e718_b");
}

// Overwrites loading from mHeadFront at 8024ea1c
void paramsReplace_thinkYoshiHeadCollision_8024ea1c() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x1cd0 (9)");
	__asm("b paramsReplace_thinkYoshiHeadCollision_8024ea1c_b");
}

// Overwrites loading from mHeadRadius at 8024ea50
void paramsReplace_thinkYoshiHeadCollision_8024ea50() {
	toRegister(9, newMarioParams);
	__asm("lfs 3, 0x1ce4 (9)");
	__asm("b paramsReplace_thinkYoshiHeadCollision_8024ea50_b");
}

// Overwrites loading from mGetOffYoshiY at 8024ebcc
void paramsReplace_getOffYoshi_8024ebcc() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x914 (9)");
	__asm("b paramsReplace_getOffYoshi_8024ebcc_b");
}

// Overwrites loading from mCanBreathDepth at 8024ecf4
void paramsReplace_thinkParams_8024ecf4() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xcd0 (9)");
	__asm("b paramsReplace_thinkParams_8024ecf4_b");
}

// Overwrites loading from mHotTimer at 8024ee34
void paramsReplace_thinkParams_8024ee34() {
	toRegister(0, ((short *)newMarioParams)[0x192]);
	__asm("b paramsReplace_thinkParams_8024ee34_b");
}

// Overwrites loading from mHotTimer at 8024eebc
void paramsReplace_thinkParams_8024eebc() {
	toRegister(3, ((short *)newMarioParams)[0x192]);
	__asm("b paramsReplace_thinkParams_8024eebc_b");
}

// Overwrites loading from mWaterLevelCheckHeight at 8024f114
void paramsReplace_thinkWaterSurface_8024f114() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xc94 (9)");
	__asm("b paramsReplace_thinkWaterSurface_8024f114_b");
}

// Overwrites loading from mSwimDepth at 8024f204
void paramsReplace_thinkWaterSurface_8024f204() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xa48 (9)");
	__asm("b paramsReplace_thinkWaterSurface_8024f204_b");
}

// Overwrites loading from mStartVMult at 8024f33c
void paramsReplace_thinkWaterSurface_8024f33c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xc08 (9)");
	__asm("b paramsReplace_thinkWaterSurface_8024f33c_b");
}

// Overwrites loading from mStartVYMult at 8024f34c
void paramsReplace_thinkWaterSurface_8024f34c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xc1c (9)");
	__asm("b paramsReplace_thinkWaterSurface_8024f34c_b");
}

// Overwrites loading from mRunningRippleDepth at 8024f3fc
void paramsReplace_thinkWaterSurface_8024f3fc() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1dc8 (9)");
	__asm("b paramsReplace_thinkWaterSurface_8024f3fc_b");
}

// Overwrites loading from mCanBreathDepth at 8024f718
void paramsReplace_thinkWaterSurface_8024f718() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xcd0 (9)");
	__asm("b paramsReplace_thinkWaterSurface_8024f718_b");
}

// Overwrites loading from mAirDecDive at 8024f784
void paramsReplace_thinkWaterSurface_8024f784() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xd0c (9)");
	__asm("b paramsReplace_thinkWaterSurface_8024f784_b");
}

// Overwrites loading from mAirDec at 8024f798
void paramsReplace_thinkWaterSurface_8024f798() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xcf8 (9)");
	__asm("b paramsReplace_thinkWaterSurface_8024f798_b");
}

// Overwrites loading from mMotorWall at 8024f7c8
void paramsReplace_thinkWaterSurface_8024f7c8() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_thinkWaterSurface_8024f7c8_b");
}

// Overwrites loading from mAirInc at 8024f82c
void paramsReplace_thinkWaterSurface_8024f82c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xd20 (9)");
	__asm("b paramsReplace_thinkWaterSurface_8024f82c_b");
}

// Overwrites loading from mTrampolineDec at 8024f8a0
void paramsReplace_thinkSituation_8024f8a0() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x798 (9)");
	__asm("b paramsReplace_thinkSituation_8024f8a0_b");
}

// Overwrites loading from mIllegalPlaneCtInc at 8024fa10
void paramsReplace_thinkSituation_8024fa10() {
	toRegister(0, ((short *)newMarioParams)[0x20a]);
	__asm("b paramsReplace_thinkSituation_8024fa10_b");
}

// Overwrites loading from mIllegalPlaneTime at 8024fa20
void paramsReplace_thinkSituation_8024fa20() {
	toRegister(0, ((short *)newMarioParams)[0x214]);
	__asm("b paramsReplace_thinkSituation_8024fa20_b");
}

// Overwrites loading from mHPMax at 8024fa2c
void paramsReplace_thinkSituation_8024fa2c() {
	toRegister(4, ((short *)newMarioParams)[0xc]);
	__asm("b paramsReplace_thinkSituation_8024fa2c_b");
}

// Overwrites loading from mGetOffYoshiY at 8024fd58
void paramsReplace_thinkSituation_8024fd58() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x914 (9)");
	__asm("b paramsReplace_thinkSituation_8024fd58_b");
}

// Overwrites loading from mZ at 8024fdf4
void paramsReplace_thinkSituation_8024fdf4() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x3cf0 (9)");
	__asm("b paramsReplace_thinkSituation_8024fdf4_b");
}

// Overwrites loading from mXMin at 8024fe00
void paramsReplace_thinkSituation_8024fe00() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x3d04 (9)");
	__asm("b paramsReplace_thinkSituation_8024fe00_b");
}

// Overwrites loading from mXMax at 8024fe14
void paramsReplace_thinkSituation_8024fe14() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x3d18 (9)");
	__asm("b paramsReplace_thinkSituation_8024fe14_b");
}

// Overwrites loading from mHPMax at 80250914
void paramsReplace_checkCurrentPlane_80250914() {
	toRegister(4, ((short *)newMarioParams)[0xc]);
	__asm("b paramsReplace_checkCurrentPlane_80250914_b");
}

// Overwrites loading from mMotorReturn at 8025091c
void paramsReplace_checkCurrentPlane_8025091c() {
	toRegister(7, ((short *)newMarioParams)[0x1124]);
	__asm("b paramsReplace_checkCurrentPlane_8025091c_b");
}

// Overwrites loading from mSlipStart at 80250fa4
void paramsReplace_checkCurrentPlane_80250fa4() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2c0 (9)");
	__asm("b paramsReplace_checkCurrentPlane_80250fa4_b");
}

// Overwrites loading from mStickRotateTime at 80251224
void paramsReplace_makeHistory_80251224() {
	toRegister(0, ((short *)newMarioParams)[0xf24]);
	__asm("b paramsReplace_makeHistory_80251224_b");
}

// Overwrites loading from mStickRotateTime at 80251254
void paramsReplace_makeHistory_80251254() {
	toRegister(0, ((short *)newMarioParams)[0xf24]);
	__asm("b paramsReplace_makeHistory_80251254_b");
}

// Overwrites loading from mSinkTime at 80251518
void paramsReplace_checkController_80251518() {
	toRegister(0, ((short *)newMarioParams)[0xf5a]);
	__asm("b paramsReplace_checkController_80251518_b");
}

// Overwrites loading from mSinkMoveMin at 8025153c
void paramsReplace_checkController_8025153c() {
	toRegister(9, newMarioParams);
	__asm("lfs 6, 0x1ef0 (9)");
	__asm("b paramsReplace_checkController_8025153c_b");
}

// Overwrites loading from mSinkMoveMax at 8025154c
void paramsReplace_checkController_8025154c() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x1f04 (9)");
	__asm("b paramsReplace_checkController_8025154c_b");
}

// Overwrites loading from mAnalogLRToZeroVal at 802516f4
void paramsReplace_checkController_802516f4() {
	toRegister(11, ((char *)newMarioParams)[0x1de4]);
	__asm("b paramsReplace_checkController_802516f4_b");
}

// Overwrites loading from mAnalogLRToMiddleVal at 80251704
void paramsReplace_checkController_80251704() {
	toRegister(10, ((char *)newMarioParams)[0x1df8]);
	__asm("b paramsReplace_checkController_80251704_b");
}

// Overwrites loading from mAnalogLRToMaxVal at 8025170c
void paramsReplace_checkController_8025170c() {
	toRegister(9, ((char *)newMarioParams)[0x1e0c]);
	__asm("b paramsReplace_checkController_8025170c_b");
}

// Overwrites loading from mAnalogLRMiddleLevel at 80251710
void paramsReplace_checkController_80251710() {
	toRegister(9, newMarioParams);
	__asm("lfs 4, 0x1e20 (9)");
	__asm("b paramsReplace_checkController_80251710_b");
}

// Overwrites loading from mLengthMultTimes at 80251b9c
void paramsReplace_checkController_80251b9c() {
	toRegister(3, ((short *)newMarioParams)[0xf2e]);
	__asm("b paramsReplace_checkController_80251b9c_b");
}

// Overwrites loading from mLengthMult at 80251bd0
void paramsReplace_checkController_80251bd0() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1e70 (9)");
	__asm("b paramsReplace_checkController_80251bd0_b");
}

// Overwrites loading from mLengthMult at 80251c10
void paramsReplace_checkController_80251c10() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1e70 (9)");
	__asm("b paramsReplace_checkController_80251c10_b");
}

// Overwrites loading from mDizzyAngleY at 80251cb0
void paramsReplace_checkController_80251cb0() {
	toRegister(0, ((short *)newMarioParams)[0xfdc]);
	__asm("b paramsReplace_checkController_80251cb0_b");
}

// Overwrites loading from mDizzyWalkCtMax at 80251cc0
void paramsReplace_checkController_80251cc0() {
	toRegister(0, ((short *)newMarioParams)[0xfd2]);
	__asm("b paramsReplace_checkController_80251cc0_b");
}

// Overwrites loading from mDizzyAngleRate at 80251cdc
void paramsReplace_checkController_80251cdc() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1fcc (9)");
	__asm("b paramsReplace_checkController_80251cdc_b");
}

// Overwrites loading from mDizzyPowerRate at 80251d20
void paramsReplace_checkController_80251d20() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1fe0 (9)");
	__asm("b paramsReplace_checkController_80251d20_b");
}

// Overwrites loading from mDizzyPower at 80251d5c
void paramsReplace_checkController_80251d5c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1ff4 (9)");
	__asm("b paramsReplace_checkController_80251d5c_b");
}

// Overwrites loading from mDashAcc at 80251e7c
void paramsReplace_checkController_80251e7c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x54 (9)");
	__asm("b paramsReplace_checkController_80251e7c_b");
}

// Overwrites loading from mDashStartTime at 80251eb0
void paramsReplace_checkController_80251eb0() {
	toRegister(5, ((short *)newMarioParams)[0x3e]);
	__asm("b paramsReplace_checkController_80251eb0_b");
}

// Overwrites loading from mDashBrake at 80251fe8
void paramsReplace_checkController_80251fe8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x68 (9)");
	__asm("b paramsReplace_checkController_80251fe8_b");
}

// Overwrites loading from mLengthMultTimes at 802521ec
void paramsReplace_checkController_802521ec() {
	toRegister(3, ((short *)newMarioParams)[0xf2e]);
	__asm("b paramsReplace_checkController_802521ec_b");
}

// Overwrites loading from mMotorWall at 80252470
void paramsReplace_checkEnforceJump_80252470() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_checkEnforceJump_80252470_b");
}

// Overwrites loading from mFootPrintTimerMax at 802526ec
void paramsReplace_checkSink_802526ec() {
	toRegister(0, ((short *)newMarioParams)[0x8e]);
	__asm("b paramsReplace_checkSink_802526ec_b");
}

// Overwrites loading from mSinkTime at 80252700
void paramsReplace_checkSink_80252700() {
	toRegister(3, ((short *)newMarioParams)[0xf5a]);
	__asm("b paramsReplace_checkSink_80252700_b");
}

// Overwrites loading from mSinkDmgDepth at 80252710
void paramsReplace_checkSink_80252710() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x1f68 (9)");
	__asm("b paramsReplace_checkSink_80252710_b");
}

// Overwrites loading from mSinkDmgTime at 8025273c
void paramsReplace_checkSink_8025273c() {
	toRegister(3, ((short *)newMarioParams)[0xf64]);
	__asm("b paramsReplace_checkSink_8025273c_b");
}

// Overwrites loading from mMotorReturn at 80252754
void paramsReplace_checkSink_80252754() {
	toRegister(7, ((short *)newMarioParams)[0x1124]);
	__asm("b paramsReplace_checkSink_80252754_b");
}

// Overwrites loading from mSinkTime at 8025279c
void paramsReplace_checkSink_8025279c() {
	toRegister(3, ((short *)newMarioParams)[0xf5a]);
	__asm("b paramsReplace_checkSink_8025279c_b");
}

// Overwrites loading from mGravity at 8025283c
void paramsReplace_checkSink_8025283c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x5a4 (9)");
	__asm("b paramsReplace_checkSink_8025283c_b");
}

// Overwrites loading from mIncRunning at 80252a58
void paramsReplace_thinkDirty_80252a58() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2060 (9)");
	__asm("b paramsReplace_thinkDirty_80252a58_b");
}

// Overwrites loading from mIncCatching at 80252a90
void paramsReplace_thinkDirty_80252a90() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2074 (9)");
	__asm("b paramsReplace_thinkDirty_80252a90_b");
}

// Overwrites loading from mIncSlipping at 80252aac
void paramsReplace_thinkDirty_80252aac() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2088 (9)");
	__asm("b paramsReplace_thinkDirty_80252aac_b");
}

// Overwrites loading from mDecSwimming at 80252b04
void paramsReplace_thinkDirty_80252b04() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x209c (9)");
	__asm("b paramsReplace_thinkDirty_80252b04_b");
}

// Overwrites loading from mDecRotJump at 80252b2c
void paramsReplace_thinkDirty_80252b2c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x20c4 (9)");
	__asm("b paramsReplace_thinkDirty_80252b2c_b");
}

// Overwrites loading from mDecWaterHit at 80252b64
void paramsReplace_thinkDirty_80252b64() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x20b0 (9)");
	__asm("b paramsReplace_thinkDirty_80252b64_b");
}

// Overwrites loading from mDirtyMax at 80252b88
void paramsReplace_thinkDirty_80252b88() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x218c (9)");
	__asm("b paramsReplace_thinkDirty_80252b88_b");
}

// Overwrites loading from mDirtyMax at 80252bc4
void paramsReplace_dirtyLimitCheck_80252bc4() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x218c (9)");
	__asm("b paramsReplace_dirtyLimitCheck_80252bc4_b");
}

// Overwrites loading from mFootPrintTimerMax at 8025318c
void paramsReplace_checkGraffito_8025318c() {
	toRegister(0, ((short *)newMarioParams)[0x8e]);
	__asm("b paramsReplace_checkGraffito_8025318c_b");
}

// Overwrites loading from mGraffitoNoDmgTime at 80253258
void paramsReplace_checkGraffitoElec_80253258() {
	toRegister(0, ((char *)newMarioParams)[0x144]);
	__asm("b paramsReplace_checkGraffitoElec_80253258_b");
}

// Overwrites loading from mFootPrintTimerMax at 80253420
void paramsReplace_checkGraffitoSlip_80253420() {
	toRegister(0, ((short *)newMarioParams)[0x8e]);
	__asm("b paramsReplace_checkGraffitoSlip_80253420_b");
}

// Overwrites loading from mBrakeStartValSlip at 80253444
void paramsReplace_checkGraffitoSlip_80253444() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x20d8 (9)");
	__asm("b paramsReplace_checkGraffitoSlip_80253444_b");
}

// Overwrites loading from mDirtyTimeSlip at 8025344c
void paramsReplace_checkGraffitoSlip_8025344c() {
	toRegister(0, ((short *)newMarioParams)[0x1080]);
	__asm("b paramsReplace_checkGraffitoSlip_8025344c_b");
}

// Overwrites loading from mBrakeStartValRun at 8025346c
void paramsReplace_checkGraffitoSlip_8025346c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x20ec (9)");
	__asm("b paramsReplace_checkGraffitoSlip_8025346c_b");
}

// Overwrites loading from mDirtyTimeRun at 80253474
void paramsReplace_checkGraffitoSlip_80253474() {
	toRegister(0, ((short *)newMarioParams)[0x108a]);
	__asm("b paramsReplace_checkGraffitoSlip_80253474_b");
}

// Overwrites loading from mSlopeAngle at 80253480
void paramsReplace_checkGraffitoSlip_80253480() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2178 (9)");
	__asm("b paramsReplace_checkGraffitoSlip_80253480_b");
}

// Overwrites loading from mBrakeStartValSlip at 80253494
void paramsReplace_checkGraffitoSlip_80253494() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x20d8 (9)");
	__asm("b paramsReplace_checkGraffitoSlip_80253494_b");
}

// Overwrites loading from mDirtyTimeSlip at 802534ac
void paramsReplace_checkGraffitoSlip_802534ac() {
	toRegister(0, ((short *)newMarioParams)[0x1080]);
	__asm("b paramsReplace_checkGraffitoSlip_802534ac_b");
}

// Overwrites loading from mBrakeStartValSlip at 802534fc
void paramsReplace_checkGraffitoSlip_802534fc() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x20d8 (9)");
	__asm("b paramsReplace_checkGraffitoSlip_802534fc_b");
}

// Overwrites loading from mDirtyTimeSlip at 80253514
void paramsReplace_checkGraffitoSlip_80253514() {
	toRegister(0, ((short *)newMarioParams)[0x1080]);
	__asm("b paramsReplace_checkGraffitoSlip_80253514_b");
}

// Overwrites loading from mBrakeStartValRun at 8025354c
void paramsReplace_checkGraffitoSlip_8025354c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x20ec (9)");
	__asm("b paramsReplace_checkGraffitoSlip_8025354c_b");
}

// Overwrites loading from mDirtyTimeRun at 80253554
void paramsReplace_checkGraffitoSlip_80253554() {
	toRegister(0, ((short *)newMarioParams)[0x108a]);
	__asm("b paramsReplace_checkGraffitoSlip_80253554_b");
}

// Overwrites loading from mFogTimeYellow at 802535bc
void paramsReplace_checkGraffitoSlip_802535bc() {
	toRegister(3, ((short *)newMarioParams)[0x110c]);
	__asm("b paramsReplace_checkGraffitoSlip_802535bc_b");
}

// Overwrites loading from mFogTimeRed at 802535c0
void paramsReplace_checkGraffitoSlip_802535c0() {
	toRegister(0, ((short *)newMarioParams)[0x1116]);
	__asm("b paramsReplace_checkGraffitoSlip_802535c0_b");
}

// Overwrites loading from mFogTimeRed at 802535e4
void paramsReplace_checkGraffitoSlip_802535e4() {
	toRegister(0, ((short *)newMarioParams)[0x1116]);
	__asm("b paramsReplace_checkGraffitoSlip_802535e4_b");
}

// Overwrites loading from mMotorReturn at 802535f0
void paramsReplace_checkGraffitoSlip_802535f0() {
	toRegister(7, ((short *)newMarioParams)[0x1124]);
	__asm("b paramsReplace_checkGraffitoSlip_802535f0_b");
}

// Overwrites loading from mFogTimeYellow at 8025360c
void paramsReplace_checkGraffitoSlip_8025360c() {
	toRegister(3, ((short *)newMarioParams)[0x110c]);
	__asm("b paramsReplace_checkGraffitoSlip_8025360c_b");
}

// Overwrites loading from mFogTimeRed at 80253610
void paramsReplace_checkGraffitoSlip_80253610() {
	toRegister(0, ((short *)newMarioParams)[0x1116]);
	__asm("b paramsReplace_checkGraffitoSlip_80253610_b");
}

// Overwrites loading from mBrakeSlipNoPollute at 8025363c
void paramsReplace_checkGraffitoSlip_8025363c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2204 (9)");
	__asm("b paramsReplace_checkGraffitoSlip_8025363c_b");
}

// Overwrites loading from mDirtyTimeSlip at 80253644
void paramsReplace_checkGraffitoSlip_80253644() {
	toRegister(0, ((short *)newMarioParams)[0x1080]);
	__asm("b paramsReplace_checkGraffitoSlip_80253644_b");
}

// Overwrites loading from mFireHeight at 80253764
void paramsReplace_checkGraffitoFire_80253764() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1f7c (9)");
	__asm("b paramsReplace_checkGraffitoFire_80253764_b");
}

// Overwrites loading from mDamage at 80253808
void paramsReplace_checkGraffitoFire_80253808() {
	toRegister(5, ((char *)newMarioParams)[0x3394]);
	__asm("b paramsReplace_checkGraffitoFire_80253808_b");
}

// Overwrites loading from mDownType at 80253810
void paramsReplace_checkGraffitoFire_80253810() {
	toRegister(6, ((char *)newMarioParams)[0x33a8]);
	__asm("b paramsReplace_checkGraffitoFire_80253810_b");
}

// Overwrites loading from mMinSpeed at 8025381c
void paramsReplace_checkGraffitoFire_8025381c() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x33e4 (9)");
	__asm("b paramsReplace_checkGraffitoFire_8025381c_b");
}

// Overwrites loading from mDirty at 80253824
void paramsReplace_checkGraffitoFire_80253824() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x33f8 (9)");
	__asm("b paramsReplace_checkGraffitoFire_80253824_b");
}

// Overwrites loading from mFireInvincibleTime at 8025384c
void paramsReplace_checkGraffitoFire_8025384c() {
	toRegister(0, ((short *)newMarioParams)[0x1004]);
	__asm("b paramsReplace_checkGraffitoFire_8025384c_b");
}

// Overwrites loading from mMissJump at 80253a98
void paramsReplace_changePlayerJumping_80253a98() {
	toRegister(0, ((char *)newMarioParams)[0x2658]);
	__asm("b paramsReplace_changePlayerJumping_80253a98_b");
}

// Overwrites loading from mMissJump at 80253ad4
void paramsReplace_changePlayerJumping_80253ad4() {
	toRegister(0, ((char *)newMarioParams)[0x273c]);
	__asm("b paramsReplace_changePlayerJumping_80253ad4_b");
}

// Overwrites loading from mMissJump at 80253b10
void paramsReplace_changePlayerJumping_80253b10() {
	toRegister(0, ((char *)newMarioParams)[0x2820]);
	__asm("b paramsReplace_changePlayerJumping_80253b10_b");
}

// Overwrites loading from mMissJump at 80253b5c
void paramsReplace_changePlayerJumping_80253b5c() {
	toRegister(0, ((char *)newMarioParams)[0x29e8]);
	__asm("b paramsReplace_changePlayerJumping_80253b5c_b");
}

// Overwrites loading from mMissJump at 80253b64
void paramsReplace_changePlayerJumping_80253b64() {
	toRegister(0, ((char *)newMarioParams)[0x2904]);
	__asm("b paramsReplace_changePlayerJumping_80253b64_b");
}

// Overwrites loading from mMissJump at 80253b6c
void paramsReplace_changePlayerJumping_80253b6c() {
	toRegister(0, ((char *)newMarioParams)[0x2490]);
	__asm("b paramsReplace_changePlayerJumping_80253b6c_b");
}

// Overwrites loading from mMissJump at 80253d78
void paramsReplace_changePlayerTriJump_80253d78() {
	toRegister(0, ((char *)newMarioParams)[0x2658]);
	__asm("b paramsReplace_changePlayerTriJump_80253d78_b");
}

// Overwrites loading from mMissJump at 80253db4
void paramsReplace_changePlayerTriJump_80253db4() {
	toRegister(0, ((char *)newMarioParams)[0x273c]);
	__asm("b paramsReplace_changePlayerTriJump_80253db4_b");
}

// Overwrites loading from mMissJump at 80253df0
void paramsReplace_changePlayerTriJump_80253df0() {
	toRegister(0, ((char *)newMarioParams)[0x2820]);
	__asm("b paramsReplace_changePlayerTriJump_80253df0_b");
}

// Overwrites loading from mMissJump at 80253e3c
void paramsReplace_changePlayerTriJump_80253e3c() {
	toRegister(0, ((char *)newMarioParams)[0x29e8]);
	__asm("b paramsReplace_changePlayerTriJump_80253e3c_b");
}

// Overwrites loading from mMissJump at 80253e44
void paramsReplace_changePlayerTriJump_80253e44() {
	toRegister(0, ((char *)newMarioParams)[0x2904]);
	__asm("b paramsReplace_changePlayerTriJump_80253e44_b");
}

// Overwrites loading from mMissJump at 80253e4c
void paramsReplace_changePlayerTriJump_80253e4c() {
	toRegister(0, ((char *)newMarioParams)[0x2490]);
	__asm("b paramsReplace_changePlayerTriJump_80253e4c_b");
}

// Overwrites loading from mFootPrintTimerMax at 802543cc
void paramsReplace_setStatusToJumping_802543cc() {
	toRegister(0, ((short *)newMarioParams)[0x8e]);
	__asm("b paramsReplace_setStatusToJumping_802543cc_b");
}

// Overwrites loading from mPolSizeJump at 802543e4
void paramsReplace_setStatusToJumping_802543e4() {
	toRegister(9, newMarioParams);
	__asm("lfs 4, 0x2164 (9)");
	__asm("b paramsReplace_setStatusToJumping_802543e4_b");
}

// Overwrites loading from mFeelDeep at 8025465c
void paramsReplace_setStatusToJumping_8025465c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x338 (9)");
	__asm("b paramsReplace_setStatusToJumping_8025465c_b");
}

// Overwrites loading from mSecJumpSpeedMult at 802546a4
void paramsReplace_setStatusToJumping_802546a4() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x7d4 (9)");
	__asm("b paramsReplace_setStatusToJumping_802546a4_b");
}

// Overwrites loading from mSecJumpForce at 802546ac
void paramsReplace_setStatusToJumping_802546ac() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x7c0 (9)");
	__asm("b paramsReplace_setStatusToJumping_802546ac_b");
}

// Overwrites loading from mSecJumpXZMult at 802546bc
void paramsReplace_setStatusToJumping_802546bc() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x7e8 (9)");
	__asm("b paramsReplace_setStatusToJumping_802546bc_b");
}

// Overwrites loading from mUltraJumpSpeedMult at 802546d8
void paramsReplace_setStatusToJumping_802546d8() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x824 (9)");
	__asm("b paramsReplace_setStatusToJumping_802546d8_b");
}

// Overwrites loading from mUltraJumpForce at 802546e0
void paramsReplace_setStatusToJumping_802546e0() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x810 (9)");
	__asm("b paramsReplace_setStatusToJumping_802546e0_b");
}

// Overwrites loading from mUltraJumpXZMult at 802546f0
void paramsReplace_setStatusToJumping_802546f0() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x838 (9)");
	__asm("b paramsReplace_setStatusToJumping_802546f0_b");
}

// Overwrites loading from mRotateJumpForceY at 80254748
void paramsReplace_setStatusToJumping_80254748() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x6a8 (9)");
	__asm("b paramsReplace_setStatusToJumping_80254748_b");
}

// Overwrites loading from mJumpXZRatio at 802547ec
void paramsReplace_setStatusToJumping_802547ec() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x127c (9)");
	__asm("b paramsReplace_setStatusToJumping_802547ec_b");
}

// Overwrites loading from mJumpPow at 802547f0
void paramsReplace_setStatusToJumping_802547f0() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1268 (9)");
	__asm("b paramsReplace_setStatusToJumping_802547f0_b");
}

// Overwrites loading from mJumpXZRatio at 80254804
void paramsReplace_setStatusToJumping_80254804() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x1450 (9)");
	__asm("b paramsReplace_setStatusToJumping_80254804_b");
}

// Overwrites loading from mJumpPow at 80254808
void paramsReplace_setStatusToJumping_80254808() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x143c (9)");
	__asm("b paramsReplace_setStatusToJumping_80254808_b");
}

// Overwrites loading from mBackJumpForce at 80254818
void paramsReplace_setStatusToJumping_80254818() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x6e4 (9)");
	__asm("b paramsReplace_setStatusToJumping_80254818_b");
}

// Overwrites loading from mBackJumpForceY at 80254830
void paramsReplace_setStatusToJumping_80254830() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x6f8 (9)");
	__asm("b paramsReplace_setStatusToJumping_80254830_b");
}

// Overwrites loading from mTurnJumpForce at 80254880
void paramsReplace_setStatusToJumping_80254880() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x61c (9)");
	__asm("b paramsReplace_setStatusToJumping_80254880_b");
}

// Overwrites loading from mFireDownForce at 802548d4
void paramsReplace_setStatusToJumping_802548d4() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x644 (9)");
	__asm("b paramsReplace_setStatusToJumping_802548d4_b");
}

// Overwrites loading from mFireBackVelocity at 802548e8
void paramsReplace_setStatusToJumping_802548e8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x66c (9)");
	__asm("b paramsReplace_setStatusToJumping_802548e8_b");
}

// Overwrites loading from mBroadJumpForce at 8025498c
void paramsReplace_setStatusToJumping_8025498c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x680 (9)");
	__asm("b paramsReplace_setStatusToJumping_8025498c_b");
}

// Overwrites loading from mBroadJumpForceY at 80254994
void paramsReplace_setStatusToJumping_80254994() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x694 (9)");
	__asm("b paramsReplace_setStatusToJumping_80254994_b");
}

// Overwrites loading from mRotBroadJumpForce at 802549ac
void paramsReplace_setStatusToJumping_802549ac() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x770 (9)");
	__asm("b paramsReplace_setStatusToJumping_802549ac_b");
}

// Overwrites loading from mRotBroadJumpForceY at 802549b4
void paramsReplace_setStatusToJumping_802549b4() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x784 (9)");
	__asm("b paramsReplace_setStatusToJumping_802549b4_b");
}

// Overwrites loading from mTramplePowStep1 at 80254a70
void paramsReplace_setStatusToJumping_80254a70() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x25c (9)");
	__asm("b paramsReplace_setStatusToJumping_80254a70_b");
}

// Overwrites loading from mTramplePowStep2 at 80254a94
void paramsReplace_setStatusToJumping_80254a94() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x270 (9)");
	__asm("b paramsReplace_setStatusToJumping_80254a94_b");
}

// Overwrites loading from mTramplePowStep3 at 80254ab8
void paramsReplace_setStatusToJumping_80254ab8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x284 (9)");
	__asm("b paramsReplace_setStatusToJumping_80254ab8_b");
}

// Overwrites loading from mJumpRate at 80254b8c
void paramsReplace_setStatusToJumping_80254b8c() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0xe78 (9)");
	__asm("b paramsReplace_setStatusToJumping_80254b8c_b");
}

// Overwrites loading from mJumpRate at 80254c58
void paramsReplace_setStatusToJumping_80254c58() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0xe78 (9)");
	__asm("b paramsReplace_setStatusToJumping_80254c58_b");
}

// Overwrites loading from mSinkTime at 80254dac
void paramsReplace_setStatusToJumping_80254dac() {
	toRegister(0, ((short *)newMarioParams)[0xf5a]);
	__asm("b paramsReplace_setStatusToJumping_80254dac_b");
}

// Overwrites loading from mSinkJumpRateMin at 80254dbc
void paramsReplace_setStatusToJumping_80254dbc() {
	toRegister(9, newMarioParams);
	__asm("lfs 6, 0x1f2c (9)");
	__asm("b paramsReplace_setStatusToJumping_80254dbc_b");
}

// Overwrites loading from mSinkJumpRateMax at 80254dc4
void paramsReplace_setStatusToJumping_80254dc4() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1f40 (9)");
	__asm("b paramsReplace_setStatusToJumping_80254dc4_b");
}

// Overwrites loading from mSinkTime at 80254e00
void paramsReplace_setStatusToJumping_80254e00() {
	toRegister(0, ((short *)newMarioParams)[0xf5a]);
	__asm("b paramsReplace_setStatusToJumping_80254e00_b");
}

// Overwrites loading from mSinkRecover at 80254e0c
void paramsReplace_setStatusToJumping_80254e0c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1f18 (9)");
	__asm("b paramsReplace_setStatusToJumping_80254e0c_b");
}

// Overwrites loading from mJumpYoshiMult at 80254e90
void paramsReplace_setStatusToJumping_80254e90() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1ca8 (9)");
	__asm("b paramsReplace_setStatusToJumping_80254e90_b");
}

// Overwrites loading from mSlopeAngle at 80254fe0
void paramsReplace_getSlideStopCatch_80254fe0() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2178 (9)");
	__asm("b paramsReplace_getSlideStopCatch_80254fe0_b");
}

// Overwrites loading from mForceSlipAngle at 80254ff8
void paramsReplace_getSlideStopCatch_80254ff8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x360 (9)");
	__asm("b paramsReplace_getSlideStopCatch_80254ff8_b");
}

// Overwrites loading from mSlideStopCatch at 80255018
void paramsReplace_getSlideStopCatch_80255018() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2630 (9)");
	__asm("b paramsReplace_getSlideStopCatch_80255018_b");
}

// Overwrites loading from mSlideStopCatch at 8025504c
void paramsReplace_getSlideStopCatch_8025504c() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2714 (9)");
	__asm("b paramsReplace_getSlideStopCatch_8025504c_b");
}

// Overwrites loading from mSlideStopCatch at 80255088
void paramsReplace_getSlideStopCatch_80255088() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x27f8 (9)");
	__asm("b paramsReplace_getSlideStopCatch_80255088_b");
}

// Overwrites loading from mSlideStopCatch at 802550d4
void paramsReplace_getSlideStopCatch_802550d4() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x29c0 (9)");
	__asm("b paramsReplace_getSlideStopCatch_802550d4_b");
}

// Overwrites loading from mSlideStopCatch at 802550dc
void paramsReplace_getSlideStopCatch_802550dc() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x28dc (9)");
	__asm("b paramsReplace_getSlideStopCatch_802550dc_b");
}

// Overwrites loading from mSlideStopCatch at 802550e4
void paramsReplace_getSlideStopCatch_802550e4() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2468 (9)");
	__asm("b paramsReplace_getSlideStopCatch_802550e4_b");
}

// Overwrites loading from mSlopeAngle at 80255160
void paramsReplace_getSlideStopNormal_80255160() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2178 (9)");
	__asm("b paramsReplace_getSlideStopNormal_80255160_b");
}

// Overwrites loading from mForceSlipAngle at 80255178
void paramsReplace_getSlideStopNormal_80255178() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x360 (9)");
	__asm("b paramsReplace_getSlideStopNormal_80255178_b");
}

// Overwrites loading from mSlideStopNormal at 80255198
void paramsReplace_getSlideStopNormal_80255198() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x261c (9)");
	__asm("b paramsReplace_getSlideStopNormal_80255198_b");
}

// Overwrites loading from mSlideStopNormal at 802551cc
void paramsReplace_getSlideStopNormal_802551cc() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2700 (9)");
	__asm("b paramsReplace_getSlideStopNormal_802551cc_b");
}

// Overwrites loading from mSlideStopNormal at 80255208
void paramsReplace_getSlideStopNormal_80255208() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x27e4 (9)");
	__asm("b paramsReplace_getSlideStopNormal_80255208_b");
}

// Overwrites loading from mSlideStopNormal at 80255254
void paramsReplace_getSlideStopNormal_80255254() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x29ac (9)");
	__asm("b paramsReplace_getSlideStopNormal_80255254_b");
}

// Overwrites loading from mSlideStopNormal at 8025525c
void paramsReplace_getSlideStopNormal_8025525c() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x28c8 (9)");
	__asm("b paramsReplace_getSlideStopNormal_8025525c_b");
}

// Overwrites loading from mSlopeAngle at 802552d8
void paramsReplace_canSlipJump_802552d8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2178 (9)");
	__asm("b paramsReplace_canSlipJump_802552d8_b");
}

// Overwrites loading from mForceSlipAngle at 802552f0
void paramsReplace_canSlipJump_802552f0() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x360 (9)");
	__asm("b paramsReplace_canSlipJump_802552f0_b");
}

// Overwrites loading from mJumpEnable at 80255310
void paramsReplace_canSlipJump_80255310() {
	toRegister(3, ((char *)newMarioParams)[0x2644]);
	__asm("b paramsReplace_canSlipJump_80255310_b");
}

// Overwrites loading from mJumpEnable at 80255344
void paramsReplace_canSlipJump_80255344() {
	toRegister(3, ((char *)newMarioParams)[0x2728]);
	__asm("b paramsReplace_canSlipJump_80255344_b");
}

// Overwrites loading from mJumpEnable at 80255370
void paramsReplace_canSlipJump_80255370() {
	toRegister(3, ((char *)newMarioParams)[0x280c]);
	__asm("b paramsReplace_canSlipJump_80255370_b");
}

// Overwrites loading from mJumpEnable at 802553bc
void paramsReplace_canSlipJump_802553bc() {
	toRegister(3, ((char *)newMarioParams)[0x29d4]);
	__asm("b paramsReplace_canSlipJump_802553bc_b");
}

// Overwrites loading from mJumpEnable at 802553c4
void paramsReplace_canSlipJump_802553c4() {
	toRegister(3, ((char *)newMarioParams)[0x28f0]);
	__asm("b paramsReplace_canSlipJump_802553c4_b");
}

// Overwrites loading from mSlopeAngle at 80255474
void paramsReplace_isSlipStart_80255474() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2178 (9)");
	__asm("b paramsReplace_isSlipStart_80255474_b");
}

// Overwrites loading from mForceSlipAngle at 8025548c
void paramsReplace_isSlipStart_8025548c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x360 (9)");
	__asm("b paramsReplace_isSlipStart_8025548c_b");
}

// Overwrites loading from mSlipStart at 80255554
void paramsReplace_isSlipStart_80255554() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2c0 (9)");
	__asm("b paramsReplace_isSlipStart_80255554_b");
}

// Overwrites loading from mHoldRadius at 802557a8
void paramsReplace_setNormalAttackArea_802557a8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x194 (9)");
	__asm("b paramsReplace_setNormalAttackArea_802557a8_b");
}

// Overwrites loading from mAttackHeight at 802557b4
void paramsReplace_setNormalAttackArea_802557b4() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1d0 (9)");
	__asm("b paramsReplace_setNormalAttackArea_802557b4_b");
}

// Overwrites loading from mSlopeAngle at 80255d8c
void paramsReplace_isForceSlip_80255d8c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2178 (9)");
	__asm("b paramsReplace_isForceSlip_80255d8c_b");
}

// Overwrites loading from mForceSlipAngle at 80255da4
void paramsReplace_isForceSlip_80255da4() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x360 (9)");
	__asm("b paramsReplace_isForceSlip_80255da4_b");
}

// Overwrites loading from mCanBreathDepth at 80255f7c
void paramsReplace_isUnderWater_80255f7c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xcd0 (9)");
	__asm("b paramsReplace_isUnderWater_80255f7c_b");
}

// Overwrites loading from mWireJumpSlideControl at 80256050
void paramsReplace_getJumpSlideControl_80256050() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0xeb4 (9)");
	__asm("b paramsReplace_getJumpSlideControl_80256050_b");
}

// Overwrites loading from mHoldOutSldCtrl at 802560a4
void paramsReplace_getJumpSlideControl_802560a4() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x1d20 (9)");
	__asm("b paramsReplace_getJumpSlideControl_802560a4_b");
}

// Overwrites loading from mJumpSlideControl at 802560ac
void paramsReplace_getJumpSlideControl_802560ac() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x608 (9)");
	__asm("b paramsReplace_getJumpSlideControl_802560ac_b");
}

// Overwrites loading from mWireJumpAccelControl at 802560d4
void paramsReplace_getJumpAccelControl_802560d4() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0xea0 (9)");
	__asm("b paramsReplace_getJumpAccelControl_802560d4_b");
}

// Overwrites loading from mJumpAccelControl at 802560dc
void paramsReplace_getJumpAccelControl_802560dc() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x5f4 (9)");
	__asm("b paramsReplace_getJumpAccelControl_802560dc_b");
}

// Overwrites loading from mJumpingMax at 8025646c
void paramsReplace_jumpProcess_8025646c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x5cc (9)");
	__asm("b paramsReplace_jumpProcess_8025646c_b");
}

// Overwrites loading from mGravity at 80256570
void paramsReplace_fallProcess_80256570() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1c3c (9)");
	__asm("b paramsReplace_fallProcess_80256570_b");
}

// Overwrites loading from mSpinJumpGravity at 80256634
void paramsReplace_fallProcess_80256634() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x5b8 (9)");
	__asm("b paramsReplace_fallProcess_80256634_b");
}

// Overwrites loading from mGravity at 80256648
void paramsReplace_fallProcess_80256648() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x5a4 (9)");
	__asm("b paramsReplace_fallProcess_80256648_b");
}

// Overwrites loading from mClashAngle at 80256c00
void paramsReplace_checkGroundAtJumping_80256c00() {
	toRegister(5, ((short *)newMarioParams)[0x476]);
	__asm("b paramsReplace_checkGroundAtJumping_80256c00_b");
}

// Overwrites loading from mDescentSp at 802575b8
void paramsReplace_checkDescent_802575b8() {
	toRegister(9, newMarioParams);
	__asm("lfs 31, 0xda0 (9)");
	__asm("b paramsReplace_checkDescent_802575b8_b");
}

// Overwrites loading from mClashSpeed at 80257834
void paramsReplace_keepDistance_80257834() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x374 (9)");
	__asm("b paramsReplace_keepDistance_80257834_b");
}

// Overwrites loading from mPolSizeSlip at 80258924
void paramsReplace_moveMain_80258924() {
	toRegister(9, newMarioParams);
	__asm("lfs 4, 0x2128 (9)");
	__asm("b paramsReplace_moveMain_80258924_b");
}

// Overwrites loading from mMotorWall at 8025897c
void paramsReplace_moveMain_8025897c() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_moveMain_8025897c_b");
}

// Overwrites loading from mMotorWall at 802589c8
void paramsReplace_moveMain_802589c8() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_moveMain_802589c8_b");
}

// Overwrites loading from mMotorWall at 80258a14
void paramsReplace_moveMain_80258a14() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_moveMain_80258a14_b");
}

// Overwrites loading from mMotorWall at 80258a60
void paramsReplace_moveMain_80258a60() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_moveMain_80258a60_b");
}

// Overwrites loading from mMotorWall at 80258aac
void paramsReplace_moveMain_80258aac() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_moveMain_80258aac_b");
}

// Overwrites loading from mMotorWall at 80258af8
void paramsReplace_moveMain_80258af8() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_moveMain_80258af8_b");
}

// Overwrites loading from mMotorWall at 80258b44
void paramsReplace_moveMain_80258b44() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_moveMain_80258b44_b");
}

// Overwrites loading from mSecJumpEnableSp at 80258da0
void paramsReplace_jumpSlipEvents_80258da0() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x7ac (9)");
	__asm("b paramsReplace_jumpSlipEvents_80258da0_b");
}

// Overwrites loading from mTriJumpEnableSp at 80258dd0
void paramsReplace_jumpSlipEvents_80258dd0() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x7fc (9)");
	__asm("b paramsReplace_jumpSlipEvents_80258dd0_b");
}

// Overwrites loading from mSlipCatchRotate at 8025924c
void paramsReplace_oilSlip_8025924c() {
	toRegister(3, ((short *)newMarioParams)[0x10f8]);
	__asm("b paramsReplace_oilSlip_8025924c_b");
}

// Overwrites loading from mPolSizeSlip at 802592e4
void paramsReplace_oilSlip_802592e4() {
	toRegister(9, newMarioParams);
	__asm("lfs 4, 0x2128 (9)");
	__asm("b paramsReplace_oilSlip_802592e4_b");
}

// Overwrites loading from mSlipCatchSp at 80259354
void paramsReplace_oilSlip_80259354() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x21c8 (9)");
	__asm("b paramsReplace_oilSlip_80259354_b");
}

// Overwrites loading from mPolSizeRun at 80259500
void paramsReplace_oilRun_80259500() {
	toRegister(9, newMarioParams);
	__asm("lfs 4, 0x213c (9)");
	__asm("b paramsReplace_oilRun_80259500_b");
}

// Overwrites loading from mSlipRotate at 8025951c
void paramsReplace_oilRun_8025951c() {
	toRegister(3, ((short *)newMarioParams)[0x10ee]);
	__asm("b paramsReplace_oilRun_8025951c_b");
}

// Overwrites loading from mSlipRunSp at 8025958c
void paramsReplace_oilRun_8025958c() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x21b4 (9)");
	__asm("b paramsReplace_oilRun_8025958c_b");
}

// Overwrites loading from mSlipRunSp at 802595bc
void paramsReplace_oilRun_802595bc() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x21b4 (9)");
	__asm("b paramsReplace_oilRun_802595bc_b");
}

// Overwrites loading from mSlipAnmSpeed at 80259674
void paramsReplace_oilRun_80259674() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x21a0 (9)");
	__asm("b paramsReplace_oilRun_80259674_b");
}

// Overwrites loading from mRotBroadEnableV at 80259738
void paramsReplace_catching_80259738() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x75c (9)");
	__asm("b paramsReplace_catching_80259738_b");
}

// Overwrites loading from mClashSpeed at 80259b40
void paramsReplace_slippingBasic_80259b40() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x374 (9)");
	__asm("b paramsReplace_slippingBasic_80259b40_b");
}

// Overwrites loading from mHPMax at 8025a338
void paramsReplace_surfing_8025a338() {
	toRegister(4, ((short *)newMarioParams)[0xc]);
	__asm("b paramsReplace_surfing_8025a338_b");
}

// Overwrites loading from mDashMax at 8025ada0
void paramsReplace_running_8025ada0() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x40 (9)");
	__asm("b paramsReplace_running_8025ada0_b");
}

// Overwrites loading from mDoJumpCatchSp at 8025ae04
void paramsReplace_running_8025ae04() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xaac (9)");
	__asm("b paramsReplace_running_8025ae04_b");
}

// Overwrites loading from mTurnNeedSp at 8025af9c
void paramsReplace_running_8025af9c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xac0 (9)");
	__asm("b paramsReplace_running_8025af9c_b");
}

// Overwrites loading from mClashSpeed at 8025b14c
void paramsReplace_running_8025b14c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x374 (9)");
	__asm("b paramsReplace_running_8025b14c_b");
}

// Overwrites loading from mJumpWallHeight at 8025b18c
void paramsReplace_running_8025b18c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x298 (9)");
	__asm("b paramsReplace_running_8025b18c_b");
}

// Overwrites loading from mDashMax at 8025b2a8
void paramsReplace_running_8025b2a8() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x40 (9)");
	__asm("b paramsReplace_running_8025b2a8_b");
}

// Overwrites loading from mMaxSpeed at 8025b894
void paramsReplace_doRunning_8025b894() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x944 (9)");
	__asm("b paramsReplace_doRunning_8025b894_b");
}

// Overwrites loading from mRunYoshiMult at 8025b8c0
void paramsReplace_doRunning_8025b8c0() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1c94 (9)");
	__asm("b paramsReplace_doRunning_8025b8c0_b");
}

// Overwrites loading from mVelMinusBrake at 8025b8dc
void paramsReplace_doRunning_8025b8dc() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x958 (9)");
	__asm("b paramsReplace_doRunning_8025b8dc_b");
}

// Overwrites loading from mAddVelDiv at 8025b8f8
void paramsReplace_doRunning_8025b8f8() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x980 (9)");
	__asm("b paramsReplace_doRunning_8025b8f8_b");
}

// Overwrites loading from mAddBase at 8025b8fc
void paramsReplace_doRunning_8025b8fc() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x96c (9)");
	__asm("b paramsReplace_doRunning_8025b8fc_b");
}

// Overwrites loading from mDecStartNrmY at 8025b914
void paramsReplace_doRunning_8025b914() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x994 (9)");
	__asm("b paramsReplace_doRunning_8025b914_b");
}

// Overwrites loading from mDecBrake at 8025b928
void paramsReplace_doRunning_8025b928() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x9a8 (9)");
	__asm("b paramsReplace_doRunning_8025b928_b");
}

// Overwrites loading from mDecBrake at 8025b938
void paramsReplace_doRunning_8025b938() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1d34 (9)");
	__asm("b paramsReplace_doRunning_8025b938_b");
}

// Overwrites loading from mPumpingRotSpMin at 8025b980
void paramsReplace_doRunning_8025b980() {
	toRegister(5, ((short *)newMarioParams)[0x70]);
	__asm("b paramsReplace_doRunning_8025b980_b");
}

// Overwrites loading from mPumpingRotSpMax at 8025b988
void paramsReplace_doRunning_8025b988() {
	toRegister(4, ((short *)newMarioParams)[0x7a]);
	__asm("b paramsReplace_doRunning_8025b988_b");
}

// Overwrites loading from mRunningRotSpMin at 8025b9dc
void paramsReplace_doRunning_8025b9dc() {
	toRegister(5, ((short *)newMarioParams)[0x52]);
	__asm("b paramsReplace_doRunning_8025b9dc_b");
}

// Overwrites loading from mRunningRotSpMax at 8025b9e4
void paramsReplace_doRunning_8025b9e4() {
	toRegister(4, ((short *)newMarioParams)[0x5c]);
	__asm("b paramsReplace_doRunning_8025b9e4_b");
}

// Overwrites loading from mRotYoshiMult at 8025ba50
void paramsReplace_doRunning_8025ba50() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1cbc (9)");
	__asm("b paramsReplace_doRunning_8025ba50_b");
}

// Overwrites loading from mDashRotSp at 8025ba98
void paramsReplace_doRunning_8025ba98() {
	toRegister(30, ((short *)newMarioParams)[0x56a]);
	__asm("b paramsReplace_doRunning_8025ba98_b");
}

// Overwrites loading from mSwimDepth at 8025babc
void paramsReplace_doRunning_8025babc() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xa48 (9)");
	__asm("b paramsReplace_doRunning_8025babc_b");
}

// Overwrites loading from mSwimDepth at 8025baec
void paramsReplace_doRunning_8025baec() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0xa48 (9)");
	__asm("b paramsReplace_doRunning_8025baec_b");
}

// Overwrites loading from mInWaterBrake at 8025baf8
void paramsReplace_doRunning_8025baf8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xa5c (9)");
	__asm("b paramsReplace_doRunning_8025baf8_b");
}

// Overwrites loading from mRunningMax at 8025bc44
void paramsReplace_slopeProcess_8025bc44() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2c (9)");
	__asm("b paramsReplace_slopeProcess_8025bc44_b");
}

// Overwrites loading from mSlipFriction at 8025bd78
void paramsReplace_doSliding_8025bd78() {
	toRegister(9, newMarioParams);
	__asm("lfs 5, 0x24d4 (9)");
	__asm("b paramsReplace_doSliding_8025bd78_b");
}

// Overwrites loading from mSlipFriction at 8025bd90
void paramsReplace_doSliding_8025bd90() {
	toRegister(9, newMarioParams);
	__asm("lfs 5, 0x25b8 (9)");
	__asm("b paramsReplace_doSliding_8025bd90_b");
}

// Overwrites loading from mSlipFriction at 8025bdcc
void paramsReplace_doSliding_8025bdcc() {
	toRegister(9, newMarioParams);
	__asm("lfs 5, 0x269c (9)");
	__asm("b paramsReplace_doSliding_8025bdcc_b");
}

// Overwrites loading from mSlipFriction at 8025bdf8
void paramsReplace_doSliding_8025bdf8() {
	toRegister(9, newMarioParams);
	__asm("lfs 5, 0x2780 (9)");
	__asm("b paramsReplace_doSliding_8025bdf8_b");
}

// Overwrites loading from mSlipFriction at 8025be44
void paramsReplace_doSliding_8025be44() {
	toRegister(9, newMarioParams);
	__asm("lfs 5, 0x2948 (9)");
	__asm("b paramsReplace_doSliding_8025be44_b");
}

// Overwrites loading from mSlipFriction at 8025be4c
void paramsReplace_doSliding_8025be4c() {
	toRegister(9, newMarioParams);
	__asm("lfs 5, 0x2864 (9)");
	__asm("b paramsReplace_doSliding_8025be4c_b");
}

// Overwrites loading from mSlipFriction at 8025be64
void paramsReplace_doSliding_8025be64() {
	toRegister(9, newMarioParams);
	__asm("lfs 5, 0x2a2c (9)");
	__asm("b paramsReplace_doSliding_8025be64_b");
}

// Overwrites loading from mSlipFriction at 8025be70
void paramsReplace_doSliding_8025be70() {
	toRegister(9, newMarioParams);
	__asm("lfs 5, 0x23f0 (9)");
	__asm("b paramsReplace_doSliding_8025be70_b");
}

// Overwrites loading from mWasOnWaterSlip at 8025be8c
void paramsReplace_doSliding_8025be8c() {
	toRegister(9, newMarioParams);
	__asm("lfs 5, 0x2d4 (9)");
	__asm("b paramsReplace_doSliding_8025be8c_b");
}

// Overwrites loading from mInWaterSlip at 8025beb0
void paramsReplace_doSliding_8025beb0() {
	toRegister(9, newMarioParams);
	__asm("lfs 5, 0x2e8 (9)");
	__asm("b paramsReplace_doSliding_8025beb0_b");
}

// Overwrites loading from mStickSlideMult at 8025c4ac
void paramsReplace_getSlideStickMult_8025c4ac() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2680 (9)");
	__asm("b paramsReplace_getSlideStickMult_8025c4ac_b");
}

// Overwrites loading from mStickSlideMult at 8025c4e8
void paramsReplace_getSlideStickMult_8025c4e8() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2764 (9)");
	__asm("b paramsReplace_getSlideStickMult_8025c4e8_b");
}

// Overwrites loading from mStickSlideMult at 8025c514
void paramsReplace_getSlideStickMult_8025c514() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2848 (9)");
	__asm("b paramsReplace_getSlideStickMult_8025c514_b");
}

// Overwrites loading from mStickSlideMult at 8025c51c
void paramsReplace_getSlideStickMult_8025c51c() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x24b8 (9)");
	__asm("b paramsReplace_getSlideStickMult_8025c51c_b");
}

// Overwrites loading from mSlideAngleYSp at 8025c554
void paramsReplace_getChangeAngleSpeed_8025c554() {
	toRegister(3, ((short *)newMarioParams)[0x1336]);
	__asm("b paramsReplace_getChangeAngleSpeed_8025c554_b");
}

// Overwrites loading from mSlideAngleYSp at 8025c5ac
void paramsReplace_getChangeAngleSpeed_8025c5ac() {
	toRegister(3, ((short *)newMarioParams)[0x13a8]);
	__asm("b paramsReplace_getChangeAngleSpeed_8025c5ac_b");
}

// Overwrites loading from mSlideAngleYSp at 8025c5f4
void paramsReplace_getChangeAngleSpeed_8025c5f4() {
	toRegister(3, ((short *)newMarioParams)[0x141a]);
	__asm("b paramsReplace_getChangeAngleSpeed_8025c5f4_b");
}

// Overwrites loading from mSlideAngleYSp at 8025c65c
void paramsReplace_getChangeAngleSpeed_8025c65c() {
	toRegister(3, ((short *)newMarioParams)[0x14fe]);
	__asm("b paramsReplace_getChangeAngleSpeed_8025c65c_b");
}

// Overwrites loading from mSlideAngleYSp at 8025c680
void paramsReplace_getChangeAngleSpeed_8025c680() {
	toRegister(3, ((short *)newMarioParams)[0x148c]);
	__asm("b paramsReplace_getChangeAngleSpeed_8025c680_b");
}

// Overwrites loading from mSlideAngleYSp at 8025c6a4
void paramsReplace_getChangeAngleSpeed_8025c6a4() {
	toRegister(3, ((short *)newMarioParams)[0x1252]);
	__asm("b paramsReplace_getChangeAngleSpeed_8025c6a4_b");
}

// Overwrites loading from mSlideAcceleUp at 8025c718
void paramsReplace_getSlopeSlideAccele_8025c718() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x25f4 (9)");
	__asm("b paramsReplace_getSlopeSlideAccele_8025c718_b");
}

// Overwrites loading from mSlideAcceleDown at 8025c720
void paramsReplace_getSlopeSlideAccele_8025c720() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2608 (9)");
	__asm("b paramsReplace_getSlopeSlideAccele_8025c720_b");
}

// Overwrites loading from mSlideAcceleUp at 8025c760
void paramsReplace_getSlopeSlideAccele_8025c760() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x26d8 (9)");
	__asm("b paramsReplace_getSlopeSlideAccele_8025c760_b");
}

// Overwrites loading from mSlideAcceleDown at 8025c768
void paramsReplace_getSlopeSlideAccele_8025c768() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x26ec (9)");
	__asm("b paramsReplace_getSlopeSlideAccele_8025c768_b");
}

// Overwrites loading from mSlideAcceleUp at 8025c798
void paramsReplace_getSlopeSlideAccele_8025c798() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x27bc (9)");
	__asm("b paramsReplace_getSlopeSlideAccele_8025c798_b");
}

// Overwrites loading from mSlideAcceleDown at 8025c7a0
void paramsReplace_getSlopeSlideAccele_8025c7a0() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x27d0 (9)");
	__asm("b paramsReplace_getSlopeSlideAccele_8025c7a0_b");
}

// Overwrites loading from mSlideAcceleUp at 8025c7f0
void paramsReplace_getSlopeSlideAccele_8025c7f0() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2984 (9)");
	__asm("b paramsReplace_getSlopeSlideAccele_8025c7f0_b");
}

// Overwrites loading from mSlideAcceleDown at 8025c7f8
void paramsReplace_getSlopeSlideAccele_8025c7f8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2998 (9)");
	__asm("b paramsReplace_getSlopeSlideAccele_8025c7f8_b");
}

// Overwrites loading from mSlideAcceleUp at 8025c804
void paramsReplace_getSlopeSlideAccele_8025c804() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x28a0 (9)");
	__asm("b paramsReplace_getSlopeSlideAccele_8025c804_b");
}

// Overwrites loading from mSlideAcceleDown at 8025c80c
void paramsReplace_getSlopeSlideAccele_8025c80c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x28b4 (9)");
	__asm("b paramsReplace_getSlopeSlideAccele_8025c80c_b");
}

// Overwrites loading from mSlideAcceleUp at 8025c818
void paramsReplace_getSlopeSlideAccele_8025c818() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x242c (9)");
	__asm("b paramsReplace_getSlopeSlideAccele_8025c818_b");
}

// Overwrites loading from mSlideAcceleDown at 8025c820
void paramsReplace_getSlopeSlideAccele_8025c820() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2440 (9)");
	__asm("b paramsReplace_getSlopeSlideAccele_8025c820_b");
}

// Overwrites loading from mSlopeAcceleUp at 8025c874
void paramsReplace_getSlopeNormalAccele_8025c874() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x25cc (9)");
	__asm("b paramsReplace_getSlopeNormalAccele_8025c874_b");
}

// Overwrites loading from mSlopeAcceleDown at 8025c87c
void paramsReplace_getSlopeNormalAccele_8025c87c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x25e0 (9)");
	__asm("b paramsReplace_getSlopeNormalAccele_8025c87c_b");
}

// Overwrites loading from mSlopeAcceleUp at 8025c8bc
void paramsReplace_getSlopeNormalAccele_8025c8bc() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x26b0 (9)");
	__asm("b paramsReplace_getSlopeNormalAccele_8025c8bc_b");
}

// Overwrites loading from mSlopeAcceleDown at 8025c8c4
void paramsReplace_getSlopeNormalAccele_8025c8c4() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x26c4 (9)");
	__asm("b paramsReplace_getSlopeNormalAccele_8025c8c4_b");
}

// Overwrites loading from mSlopeAcceleUp at 8025c8f4
void paramsReplace_getSlopeNormalAccele_8025c8f4() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2794 (9)");
	__asm("b paramsReplace_getSlopeNormalAccele_8025c8f4_b");
}

// Overwrites loading from mSlopeAcceleDown at 8025c8fc
void paramsReplace_getSlopeNormalAccele_8025c8fc() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x27a8 (9)");
	__asm("b paramsReplace_getSlopeNormalAccele_8025c8fc_b");
}

// Overwrites loading from mSlopeAcceleUp at 8025c94c
void paramsReplace_getSlopeNormalAccele_8025c94c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x295c (9)");
	__asm("b paramsReplace_getSlopeNormalAccele_8025c94c_b");
}

// Overwrites loading from mSlopeAcceleDown at 8025c954
void paramsReplace_getSlopeNormalAccele_8025c954() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2970 (9)");
	__asm("b paramsReplace_getSlopeNormalAccele_8025c954_b");
}

// Overwrites loading from mSlopeAcceleUp at 8025c960
void paramsReplace_getSlopeNormalAccele_8025c960() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2878 (9)");
	__asm("b paramsReplace_getSlopeNormalAccele_8025c960_b");
}

// Overwrites loading from mSlopeAcceleDown at 8025c968
void paramsReplace_getSlopeNormalAccele_8025c968() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x288c (9)");
	__asm("b paramsReplace_getSlopeNormalAccele_8025c968_b");
}

// Overwrites loading from mSlopeAcceleUp at 8025c974
void paramsReplace_getSlopeNormalAccele_8025c974() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2404 (9)");
	__asm("b paramsReplace_getSlopeNormalAccele_8025c974_b");
}

// Overwrites loading from mSlopeAcceleDown at 8025c97c
void paramsReplace_getSlopeNormalAccele_8025c97c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2418 (9)");
	__asm("b paramsReplace_getSlopeNormalAccele_8025c97c_b");
}

// Overwrites loading from mDashMax at 8025ca38
void paramsReplace_doRunningAnimation_8025ca38() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x40 (9)");
	__asm("b paramsReplace_doRunningAnimation_8025ca38_b");
}

// Overwrites loading from mWalk2Soft at 8025ca68
void paramsReplace_doRunningAnimation_8025ca68() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x9d0 (9)");
	__asm("b paramsReplace_doRunningAnimation_8025ca68_b");
}

// Overwrites loading from mRunAnmSpeedMult at 8025ca90
void paramsReplace_doRunningAnimation_8025ca90() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0xa0c (9)");
	__asm("b paramsReplace_doRunningAnimation_8025ca90_b");
}

// Overwrites loading from mRunAnmSpeedBase at 8025ca94
void paramsReplace_doRunningAnimation_8025ca94() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x9f8 (9)");
	__asm("b paramsReplace_doRunningAnimation_8025ca94_b");
}

// Overwrites loading from mSwimDepth at 8025cabc
void paramsReplace_doRunningAnimation_8025cabc() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xa48 (9)");
	__asm("b paramsReplace_doRunningAnimation_8025cabc_b");
}

// Overwrites loading from mInWaterBrake at 8025caec
void paramsReplace_doRunningAnimation_8025caec() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xa5c (9)");
	__asm("b paramsReplace_doRunningAnimation_8025caec_b");
}

// Overwrites loading from mSwimDepth at 8025caf4
void paramsReplace_doRunningAnimation_8025caf4() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0xa48 (9)");
	__asm("b paramsReplace_doRunningAnimation_8025caf4_b");
}

// Overwrites loading from mInWaterAnmBrake at 8025cafc
void paramsReplace_doRunningAnimation_8025cafc() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xa70 (9)");
	__asm("b paramsReplace_doRunningAnimation_8025cafc_b");
}

// Overwrites loading from mMotBlendWalkSp at 8025cb20
void paramsReplace_doRunningAnimation_8025cb20() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xa20 (9)");
	__asm("b paramsReplace_doRunningAnimation_8025cb20_b");
}

// Overwrites loading from mMotBlendRunSp at 8025cb24
void paramsReplace_doRunningAnimation_8025cb24() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0xa34 (9)");
	__asm("b paramsReplace_doRunningAnimation_8025cb24_b");
}

// Overwrites loading from mSoft2Walk at 8025cbac
void paramsReplace_doRunningAnimation_8025cbac() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x9bc (9)");
	__asm("b paramsReplace_doRunningAnimation_8025cbac_b");
}

// Overwrites loading from mSoftStepAnmMult at 8025cbe0
void paramsReplace_doRunningAnimation_8025cbe0() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x9e4 (9)");
	__asm("b paramsReplace_doRunningAnimation_8025cbe0_b");
}

// Overwrites loading from mDashMax at 8025cbfc
void paramsReplace_doRunningAnimation_8025cbfc() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x40 (9)");
	__asm("b paramsReplace_doRunningAnimation_8025cbfc_b");
}

// Overwrites loading from mRunAnmSpeedMult at 8025cc28
void paramsReplace_doRunningAnimation_8025cc28() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0xa0c (9)");
	__asm("b paramsReplace_doRunningAnimation_8025cc28_b");
}

// Overwrites loading from mRunAnmSpeedBase at 8025cc30
void paramsReplace_doRunningAnimation_8025cc30() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x9f8 (9)");
	__asm("b paramsReplace_doRunningAnimation_8025cc30_b");
}

// Overwrites loading from mSwimDepth at 8025ccb4
void paramsReplace_isRunningInWater_8025ccb4() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xa48 (9)");
	__asm("b paramsReplace_isRunningInWater_8025ccb4_b");
}

// Overwrites loading from mSwingRate at 8025d094
void paramsReplace_specMain_8025d094() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0xe8c (9)");
	__asm("b paramsReplace_specMain_8025d094_b");
}

// Overwrites loading from mWireSwingBrake at 8025d0b8
void paramsReplace_specMain_8025d0b8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xef0 (9)");
	__asm("b paramsReplace_specMain_8025d0b8_b");
}

// Overwrites loading from mWireSwingMax at 8025d0c4
void paramsReplace_specMain_8025d0c4() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xf04 (9)");
	__asm("b paramsReplace_specMain_8025d0c4_b");
}

// Overwrites loading from mMotorWall at 8025d304
void paramsReplace_specMain_8025d304() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_specMain_8025d304_b");
}

// Overwrites loading from mRadius at 8025d498
void paramsReplace_specMain_8025d498() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x574 (9)");
	__asm("b paramsReplace_specMain_8025d498_b");
}

// Overwrites loading from mHeight at 8025d4a8
void paramsReplace_specMain_8025d4a8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x588 (9)");
	__asm("b paramsReplace_specMain_8025d4a8_b");
}

// Overwrites loading from mMotorWall at 8025def8
void paramsReplace_fencePunch_8025def8() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_fencePunch_8025def8_b");
}

// Overwrites loading from mRadius at 8025df84
void paramsReplace_fencePunch_8025df84() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x544 (9)");
	__asm("b paramsReplace_fencePunch_8025df84_b");
}

// Overwrites loading from mHeight at 8025df94
void paramsReplace_fencePunch_8025df94() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x558 (9)");
	__asm("b paramsReplace_fencePunch_8025df94_b");
}

// Overwrites loading from mMotorWall at 8025dfe0
void paramsReplace_fencePunch_8025dfe0() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_fencePunch_8025dfe0_b");
}

// Overwrites loading from mFenceSpeed at 8025e1c0
void paramsReplace_fenceMove_8025e1c0() {
	toRegister(9, newMarioParams);
	__asm("lfs 6, 0x630 (9)");
	__asm("b paramsReplace_fenceMove_8025e1c0_b");
}

// Overwrites loading from mMotorWall at 8025e5d4
void paramsReplace_fenceMove_8025e5d4() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_fenceMove_8025e5d4_b");
}

// Overwrites loading from mRotSpeedMax at 8025f028
void paramsReplace_wireRolling_8025f028() {
	toRegister(29, ((short *)newMarioParams)[0x714]);
	__asm("b paramsReplace_wireRolling_8025f028_b");
}

// Overwrites loading from mRotSpeedTrgRocket at 8025f16c
void paramsReplace_wireRolling_8025f16c() {
	toRegister(0, ((short *)newMarioParams)[0x70a]);
	__asm("b paramsReplace_wireRolling_8025f16c_b");
}

// Overwrites loading from mRotSpeedTrgHover at 8025f174
void paramsReplace_wireRolling_8025f174() {
	toRegister(0, ((short *)newMarioParams)[0x6f6]);
	__asm("b paramsReplace_wireRolling_8025f174_b");
}

// Overwrites loading from mRotSpeedTrgTurbo at 8025f17c
void paramsReplace_wireRolling_8025f17c() {
	toRegister(0, ((short *)newMarioParams)[0x700]);
	__asm("b paramsReplace_wireRolling_8025f17c_b");
}

// Overwrites loading from mRotSpeed at 8025f184
void paramsReplace_wireRolling_8025f184() {
	toRegister(0, ((short *)newMarioParams)[0x6ec]);
	__asm("b paramsReplace_wireRolling_8025f184_b");
}

// Overwrites loading from mRotGravity at 8025f198
void paramsReplace_wireRolling_8025f198() {
	toRegister(0, ((short *)newMarioParams)[0x728]);
	__asm("b paramsReplace_wireRolling_8025f198_b");
}

// Overwrites loading from mRotBrake at 8025f21c
void paramsReplace_wireRolling_8025f21c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xe64 (9)");
	__asm("b paramsReplace_wireRolling_8025f21c_b");
}

// Overwrites loading from mRotStop at 8025f4c0
void paramsReplace_wireRolling_8025f4c0() {
	toRegister(4, ((short *)newMarioParams)[0x71e]);
	__asm("b paramsReplace_wireRolling_8025f4c0_b");
}

// Overwrites loading from mRotSpeedTrgRocket at 8025fa84
void paramsReplace_wireHanging_8025fa84() {
	toRegister(0, ((short *)newMarioParams)[0x70a]);
	__asm("b paramsReplace_wireHanging_8025fa84_b");
}

// Overwrites loading from mRotSpeedTrgHover at 8025fa8c
void paramsReplace_wireHanging_8025fa8c() {
	toRegister(0, ((short *)newMarioParams)[0x6f6]);
	__asm("b paramsReplace_wireHanging_8025fa8c_b");
}

// Overwrites loading from mRotSpeedTrgTurbo at 8025fa94
void paramsReplace_wireHanging_8025fa94() {
	toRegister(0, ((short *)newMarioParams)[0x700]);
	__asm("b paramsReplace_wireHanging_8025fa94_b");
}

// Overwrites loading from mRotSpeed at 8025fa9c
void paramsReplace_wireHanging_8025fa9c() {
	toRegister(0, ((short *)newMarioParams)[0x6ec]);
	__asm("b paramsReplace_wireHanging_8025fa9c_b");
}

// Overwrites loading from mRotStop at 8025faac
void paramsReplace_wireHanging_8025faac() {
	toRegister(0, ((short *)newMarioParams)[0x71e]);
	__asm("b paramsReplace_wireHanging_8025faac_b");
}

// Overwrites loading from mRotStop at 8025fac4
void paramsReplace_wireHanging_8025fac4() {
	toRegister(3, ((short *)newMarioParams)[0x71e]);
	__asm("b paramsReplace_wireHanging_8025fac4_b");
}

// Overwrites loading from mRotSpeedTrgRocket at 8025fb18
void paramsReplace_wireHanging_8025fb18() {
	toRegister(0, ((short *)newMarioParams)[0x70a]);
	__asm("b paramsReplace_wireHanging_8025fb18_b");
}

// Overwrites loading from mRotSpeedTrgHover at 8025fb20
void paramsReplace_wireHanging_8025fb20() {
	toRegister(0, ((short *)newMarioParams)[0x6f6]);
	__asm("b paramsReplace_wireHanging_8025fb20_b");
}

// Overwrites loading from mRotSpeedTrgTurbo at 8025fb28
void paramsReplace_wireHanging_8025fb28() {
	toRegister(0, ((short *)newMarioParams)[0x700]);
	__asm("b paramsReplace_wireHanging_8025fb28_b");
}

// Overwrites loading from mRotSpeed at 8025fb30
void paramsReplace_wireHanging_8025fb30() {
	toRegister(0, ((short *)newMarioParams)[0x6ec]);
	__asm("b paramsReplace_wireHanging_8025fb30_b");
}

// Overwrites loading from mWireJumpMult at 802601f8
void paramsReplace_wireWait_802601f8() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0xec8 (9)");
	__asm("b paramsReplace_wireWait_802601f8_b");
}

// Overwrites loading from mWireJumpBase at 8026020c
void paramsReplace_wireWait_8026020c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xedc (9)");
	__asm("b paramsReplace_wireWait_8026020c_b");
}

// Overwrites loading from mLimitTime at 8026077c
void paramsReplace_hanging_8026077c() {
	toRegister(0, ((short *)newMarioParams)[0x6bc]);
	__asm("b paramsReplace_hanging_8026077c_b");
}

// Overwrites loading from mRapidTime at 80260c34
void paramsReplace_hanging_80260c34() {
	toRegister(0, ((short *)newMarioParams)[0x6b2]);
	__asm("b paramsReplace_hanging_80260c34_b");
}

// Overwrites loading from mMoveSp at 80260c50
void paramsReplace_hanging_80260c50() {
	toRegister(9, newMarioParams);
	__asm("lfs 3, 0xd3c (9)");
	__asm("b paramsReplace_hanging_80260c50_b");
}

// Overwrites loading from mHangWallMovableAngle at 80260ec0
void paramsReplace_hanging_80260ec0() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x388 (9)");
	__asm("b paramsReplace_hanging_80260ec0_b");
}

// Overwrites loading from mAnmRate at 802610c4
void paramsReplace_hanging_802610c4() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xd50 (9)");
	__asm("b paramsReplace_hanging_802610c4_b");
}

// Overwrites loading from mRapidTime at 802610f8
void paramsReplace_hanging_802610f8() {
	toRegister(0, ((short *)newMarioParams)[0x6b2]);
	__asm("b paramsReplace_hanging_802610f8_b");
}

// Overwrites loading from mAnmRapid at 80261118
void paramsReplace_hanging_80261118() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0xd8c (9)");
	__asm("b paramsReplace_hanging_80261118_b");
}

// Overwrites loading from mMotorWall at 802612b4
void paramsReplace_moveRoof_802612b4() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_moveRoof_802612b4_b");
}

// Overwrites loading from mAnmMult at 8026141c
void paramsReplace_moveRoof_8026141c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xdbc (9)");
	__asm("b paramsReplace_moveRoof_8026141c_b");
}

// Overwrites loading from mMotorWall at 8026151c
void paramsReplace_roofCommonEvents_8026151c() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_roofCommonEvents_8026151c_b");
}

// Overwrites loading from mClimbSp at 802619a0
void paramsReplace_barClimb_802619a0() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x1080 (9)");
	__asm("b paramsReplace_barClimb_802619a0_b");
}

// Overwrites loading from mClimbAnmRate at 80261a28
void paramsReplace_barClimb_80261a28() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x10a8 (9)");
	__asm("b paramsReplace_barClimb_80261a28_b");
}

// Overwrites loading from mRotateSp at 80261ee8
void paramsReplace_barWait_80261ee8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1094 (9)");
	__asm("b paramsReplace_barWait_80261ee8_b");
}

// Overwrites loading from mSinkTime at 80262534
void paramsReplace_checkPumpEnable_80262534() {
	toRegister(3, ((short *)newMarioParams)[0xf5a]);
	__asm("b paramsReplace_checkPumpEnable_80262534_b");
}

// Overwrites loading from mSinkPumpLimit at 80262544
void paramsReplace_checkPumpEnable_80262544() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1f54 (9)");
	__asm("b paramsReplace_checkPumpEnable_80262544_b");
}

// Overwrites loading from mToroccoWind at 80262c84
void paramsReplace_toroccoEffect_80262c84() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2354 (9)");
	__asm("b paramsReplace_toroccoEffect_80262c84_b");
}

// Overwrites loading from mToroccoSpark at 80262cb8
void paramsReplace_toroccoEffect_80262cb8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2368 (9)");
	__asm("b paramsReplace_toroccoEffect_80262cb8_b");
}

// Overwrites loading from mMotorWall at 80262dc0
void paramsReplace_kickRoofEffect_80262dc0() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_kickRoofEffect_80262dc0_b");
}

// Overwrites loading from mMeltInWaterMax at 80262f9c
void paramsReplace_meltInWaterEffect_80262f9c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x22a0 (9)");
	__asm("b paramsReplace_meltInWaterEffect_80262f9c_b");
}

// Overwrites loading from mBubbleDepth at 80263f88
void paramsReplace_swimmingBubbleEffect_80263f88() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x22dc (9)");
	__asm("b paramsReplace_swimmingBubbleEffect_80263f88_b");
}

// Overwrites loading from mBodyBubbleSpMax at 80264038
void paramsReplace_bubbleFromBody_80264038() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x2304 (9)");
	__asm("b paramsReplace_bubbleFromBody_80264038_b");
}

// Overwrites loading from mBodyBubbleSpMin at 80264048
void paramsReplace_bubbleFromBody_80264048() {
	toRegister(9, newMarioParams);
	__asm("lfs 3, 0x22f0 (9)");
	__asm("b paramsReplace_bubbleFromBody_80264048_b");
}

// Overwrites loading from mBodyBubbleEmitMin at 8026406c
void paramsReplace_bubbleFromBody_8026406c() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2318 (9)");
	__asm("b paramsReplace_bubbleFromBody_8026406c_b");
}

// Overwrites loading from mBodyBubbleEmitMax at 80264074
void paramsReplace_bubbleFromBody_80264074() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x232c (9)");
	__asm("b paramsReplace_bubbleFromBody_80264074_b");
}

// Overwrites loading from mBubbleToRipple at 802641b0
void paramsReplace_execute_802641b0() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2340 (9)");
	__asm("b paramsReplace_execute_802641b0_b");
}

// Overwrites loading from mJumpIntoMdlEffectSpY at 8026429c
void paramsReplace_inOutWaterEffect_8026429c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1d50 (9)");
	__asm("b paramsReplace_inOutWaterEffect_8026429c_b");
}

// Overwrites loading from mMotorWall at 802642a8
void paramsReplace_inOutWaterEffect_802642a8() {
	toRegister(5, ((short *)newMarioParams)[0x1142]);
	__asm("b paramsReplace_inOutWaterEffect_802642a8_b");
}

// Overwrites loading from mWaveEmitSpeed at 80264414
void paramsReplace_rippleEffect_80264414() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x22b4 (9)");
	__asm("b paramsReplace_rippleEffect_80264414_b");
}

// Overwrites loading from mWaveAlphaDec at 802648cc
void paramsReplace_moveParticle_802648cc() {
	toRegister(3, ((short *)newMarioParams)[0x1164]);
	__asm("b paramsReplace_moveParticle_802648cc_b");
}

// Overwrites loading from mMotorHipDrop at 802658e4
void paramsReplace_squating_802658e4() {
	toRegister(5, ((short *)newMarioParams)[0x1138]);
	__asm("b paramsReplace_squating_802658e4_b");
}

// Overwrites loading from mSquatRotMidAnalog at 80265a54
void paramsReplace_squating_80265a54() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1e84 (9)");
	__asm("b paramsReplace_squating_80265a54_b");
}

// Overwrites loading from mSquatRotMidValue at 80265a58
void paramsReplace_squating_80265a58() {
	toRegister(9, newMarioParams);
	__asm("lfs 4, 0x1e98 (9)");
	__asm("b paramsReplace_squating_80265a58_b");
}

// Overwrites loading from mWaitingRotSp at 80265a94
void paramsReplace_squating_80265a94() {
	toRegister(4, ((short *)newMarioParams)[0x48]);
	__asm("b paramsReplace_squating_80265a94_b");
}

// Overwrites loading from mPumpingSlideSp at 80265b44
void paramsReplace_getSideWalkValues_80265b44() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xa84 (9)");
	__asm("b paramsReplace_getSideWalkValues_80265b44_b");
}

// Overwrites loading from mPumpingSlideAnmSp at 80265b80
void paramsReplace_getSideWalkValues_80265b80() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xa98 (9)");
	__asm("b paramsReplace_getSideWalkValues_80265b80_b");
}

// Overwrites loading from mWaitingRotSp at 802662cc
void paramsReplace_waitingCommonEvents_802662cc() {
	toRegister(5, ((short *)newMarioParams)[0x48]);
	__asm("b paramsReplace_waitingCommonEvents_802662cc_b");
}

// Overwrites loading from mStartToWalkLevel at 802662f0
void paramsReplace_waitingCommonEvents_802662f0() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1e34 (9)");
	__asm("b paramsReplace_waitingCommonEvents_802662f0_b");
}

// Overwrites loading from mSleepingCheckDist at 80266528
void paramsReplace_canSleep_80266528() {
	toRegister(9, newMarioParams);
	__asm("lfs 31, 0x3ec (9)");
	__asm("b paramsReplace_canSleep_80266528_b");
}

// Overwrites loading from mSleepingCheckHeight at 80266540
void paramsReplace_canSleep_80266540() {
	toRegister(9, newMarioParams);
	__asm("lfs 30, 0x400 (9)");
	__asm("b paramsReplace_canSleep_80266540_b");
}

// Overwrites loading from mGravity at 8026ea20
void paramsReplace_movement_8026ea20() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x5a4 (9)");
	__asm("b paramsReplace_movement_8026ea20_b");
}

// Overwrites loading from mJumpIntoMdlEffectSpY at 80271ed8
void paramsReplace_setJumpIntoWaterEffect_80271ed8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1d50 (9)");
	__asm("b paramsReplace_setJumpIntoWaterEffect_80271ed8_b");
}

// Overwrites loading from mJumpIntoMinY at 80271f38
void paramsReplace_setJumpIntoWaterEffect_80271f38() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1d64 (9)");
	__asm("b paramsReplace_setJumpIntoWaterEffect_80271f38_b");
}

// Overwrites loading from mJumpIntoMaxY at 80271f3c
void paramsReplace_setJumpIntoWaterEffect_80271f3c() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x1d78 (9)");
	__asm("b paramsReplace_setJumpIntoWaterEffect_80271f3c_b");
}

// Overwrites loading from mJumpIntoScaleWidth at 80271f7c
void paramsReplace_setJumpIntoWaterEffect_80271f7c() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x1da0 (9)");
	__asm("b paramsReplace_setJumpIntoWaterEffect_80271f7c_b");
}

// Overwrites loading from mJumpIntoScaleMin at 80271f84
void paramsReplace_setJumpIntoWaterEffect_80271f84() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1d8c (9)");
	__asm("b paramsReplace_setJumpIntoWaterEffect_80271f84_b");
}

// Overwrites loading from mFloatHeight at 802726f8
void paramsReplace_swimMain_802726f8() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0xbf4 (9)");
	__asm("b paramsReplace_swimMain_802726f8_b");
}

// Overwrites loading from mPaddleSpeedUp at 80272974
void paramsReplace_swimMain_80272974() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xc58 (9)");
	__asm("b paramsReplace_swimMain_80272974_b");
}

// Overwrites loading from mPaddleJumpUp at 80272984
void paramsReplace_swimMain_80272984() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xc6c (9)");
	__asm("b paramsReplace_swimMain_80272984_b");
}

// Overwrites loading from mFloatUp at 80272aec
void paramsReplace_swimMain_80272aec() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xc80 (9)");
	__asm("b paramsReplace_swimMain_80272aec_b");
}

// Overwrites loading from mWaitSinkTime at 80272b8c
void paramsReplace_swimMain_80272b8c() {
	toRegister(0, ((short *)newMarioParams)[0x65e]);
	__asm("b paramsReplace_swimMain_80272b8c_b");
}

// Overwrites loading from mWaitSinkSpeed at 80272bac
void paramsReplace_swimMain_80272bac() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xce4 (9)");
	__asm("b paramsReplace_swimMain_80272bac_b");
}

// Overwrites loading from mDashMax at 80272d38
void paramsReplace_swimPaddle_80272d38() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x40 (9)");
	__asm("b paramsReplace_swimPaddle_80272d38_b");
}

// Overwrites loading from mCanJumpDepth at 80272e84
void paramsReplace_checkSwimJump_80272e84() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0xbcc (9)");
	__asm("b paramsReplace_checkSwimJump_80272e84_b");
}

// Overwrites loading from mEndDepth at 80272fac
void paramsReplace_doSwimming_80272fac() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0xbe0 (9)");
	__asm("b paramsReplace_doSwimming_80272fac_b");
}

// Overwrites loading from mMoveSp at 80272fe0
void paramsReplace_doSwimming_80272fe0() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xb04 (9)");
	__asm("b paramsReplace_doSwimming_80272fe0_b");
}

// Overwrites loading from mMoveBrake at 80272ffc
void paramsReplace_doSwimming_80272ffc() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xb18 (9)");
	__asm("b paramsReplace_doSwimming_80272ffc_b");
}

// Overwrites loading from mPumpingRotSpMin at 80273030
void paramsReplace_doSwimming_80273030() {
	toRegister(4, ((short *)newMarioParams)[0x5aa]);
	__asm("b paramsReplace_doSwimming_80273030_b");
}

// Overwrites loading from mPumpingRotSpMax at 80273038
void paramsReplace_doSwimming_80273038() {
	toRegister(0, ((short *)newMarioParams)[0x5b4]);
	__asm("b paramsReplace_doSwimming_80273038_b");
}

// Overwrites loading from mSwimmingRotSpMin at 8027306c
void paramsReplace_doSwimming_8027306c() {
	toRegister(4, ((short *)newMarioParams)[0x596]);
	__asm("b paramsReplace_doSwimming_8027306c_b");
}

// Overwrites loading from mSwimmingRotSpMax at 80273074
void paramsReplace_doSwimming_80273074() {
	toRegister(0, ((short *)newMarioParams)[0x5a0]);
	__asm("b paramsReplace_doSwimming_80273074_b");
}

// Overwrites loading from mGravity at 80273100
void paramsReplace_doSwimming_80273100() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xb7c (9)");
	__asm("b paramsReplace_doSwimming_80273100_b");
}

// Overwrites loading from mFloatHeight at 80273114
void paramsReplace_doSwimming_80273114() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0xbf4 (9)");
	__asm("b paramsReplace_doSwimming_80273114_b");
}

// Overwrites loading from mWaitBouyancy at 80273160
void paramsReplace_doSwimming_80273160() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xb90 (9)");
	__asm("b paramsReplace_doSwimming_80273160_b");
}

// Overwrites loading from mMoveBouyancy at 8027316c
void paramsReplace_doSwimming_8027316c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xba4 (9)");
	__asm("b paramsReplace_doSwimming_8027316c_b");
}

// Overwrites loading from mUpDownBrake at 8027318c
void paramsReplace_doSwimming_8027318c() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0xbb8 (9)");
	__asm("b paramsReplace_doSwimming_8027318c_b");
}

// Overwrites loading from mGravity at 802738d0
void paramsReplace_SMS_GetMarioGravity_802738d0() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x5a4 (9)");
	__asm("b paramsReplace_SMS_GetMarioGravity_802738d0_b");
}

// Overwrites loading from mHPMax at 802766d0
void paramsReplace_initValues_802766d0() {
	toRegister(0, ((short *)newMarioParams)[0xc]);
	__asm("b paramsReplace_initValues_802766d0_b");
}

// Overwrites loading from mTrampleRadius at 80276a24
void paramsReplace_initValues_80276a24() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x1e4 (9)");
	__asm("b paramsReplace_initValues_80276a24_b");
}

// Overwrites loading from mAttackHeight at 80276a28
void paramsReplace_initValues_80276a28() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x1d0 (9)");
	__asm("b paramsReplace_initValues_80276a28_b");
}

// Overwrites loading from mDamageRadius at 80276a2c
void paramsReplace_initValues_80276a2c() {
	toRegister(9, newMarioParams);
	__asm("lfs 3, 0x1a8 (9)");
	__asm("b paramsReplace_initValues_80276a2c_b");
}

// Overwrites loading from mDamageHeight at 80276a30
void paramsReplace_initValues_80276a30() {
	toRegister(9, newMarioParams);
	__asm("lfs 4, 0x1bc (9)");
	__asm("b paramsReplace_initValues_80276a30_b");
}

// Overwrites loading from mHPMax at 8027b770
void paramsReplace_TMario_8027b770() {
	toRegister(5, ((short *)newMarioParams)[0xc]);
	__asm("b paramsReplace_TMario_8027b770_b");
}

// Overwrites loading from mCatchRadius at 802824ec
void paramsReplace_hangPole_802824ec() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x10bc (9)");
	__asm("b paramsReplace_hangPole_802824ec_b");
}

// Overwrites loading from mCatchAngle at 80282500
void paramsReplace_hangPole_80282500() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x10d0 (9)");
	__asm("b paramsReplace_hangPole_80282500_b");
}

// Overwrites loading from mHPMax at 80282fcc
void paramsReplace_receiveMessage_80282fcc() {
	toRegister(0, ((short *)newMarioParams)[0xc]);
	__asm("b paramsReplace_receiveMessage_80282fcc_b");
}

// Overwrites loading from mHPMax at 802833e0
void paramsReplace_receiveMessage_802833e0() {
	toRegister(0, ((short *)newMarioParams)[0xc]);
	__asm("b paramsReplace_receiveMessage_802833e0_b");
}

// Overwrites loading from mHPMax at 80283544
void paramsReplace_receiveMessage_80283544() {
	toRegister(0, ((short *)newMarioParams)[0xc]);
	__asm("b paramsReplace_receiveMessage_80283544_b");
}

// Overwrites loading from mInvincibleTime at 80283620
void paramsReplace_receiveMessage_80283620() {
	toRegister(9, ((short *)newMarioParams)[0x18de]);
	__asm("b paramsReplace_receiveMessage_80283620_b");
}

// Overwrites loading from mDirty at 80283628
void paramsReplace_receiveMessage_80283628() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x31a8 (9)");
	__asm("b paramsReplace_receiveMessage_80283628_b");
}

// Overwrites loading from mMinSpeed at 80283634
void paramsReplace_receiveMessage_80283634() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x3194 (9)");
	__asm("b paramsReplace_receiveMessage_80283634_b");
}

// Overwrites loading from mWaterEmit at 80283638
void paramsReplace_receiveMessage_80283638() {
	toRegister(7, ((char *)newMarioParams)[0x316c]);
	__asm("b paramsReplace_receiveMessage_80283638_b");
}

// Overwrites loading from mDownType at 8028363c
void paramsReplace_receiveMessage_8028363c() {
	toRegister(6, ((char *)newMarioParams)[0x3158]);
	__asm("b paramsReplace_receiveMessage_8028363c_b");
}

// Overwrites loading from mInvincibleTime at 802836dc
void paramsReplace_receiveMessage_802836dc() {
	toRegister(9, ((short *)newMarioParams)[0x1928]);
	__asm("b paramsReplace_receiveMessage_802836dc_b");
}

// Overwrites loading from mDirty at 802836e4
void paramsReplace_receiveMessage_802836e4() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x323c (9)");
	__asm("b paramsReplace_receiveMessage_802836e4_b");
}

// Overwrites loading from mMinSpeed at 802836f0
void paramsReplace_receiveMessage_802836f0() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x3228 (9)");
	__asm("b paramsReplace_receiveMessage_802836f0_b");
}

// Overwrites loading from mWaterEmit at 802836f4
void paramsReplace_receiveMessage_802836f4() {
	toRegister(7, ((char *)newMarioParams)[0x3200]);
	__asm("b paramsReplace_receiveMessage_802836f4_b");
}

// Overwrites loading from mDownType at 802836f8
void paramsReplace_receiveMessage_802836f8() {
	toRegister(6, ((char *)newMarioParams)[0x31ec]);
	__asm("b paramsReplace_receiveMessage_802836f8_b");
}

// Overwrites loading from mInvincibleTime at 80283774
void paramsReplace_receiveMessage_80283774() {
	toRegister(9, ((short *)newMarioParams)[0x1722]);
	__asm("b paramsReplace_receiveMessage_80283774_b");
}

// Overwrites loading from mDirty at 8028377c
void paramsReplace_receiveMessage_8028377c() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x2e30 (9)");
	__asm("b paramsReplace_receiveMessage_8028377c_b");
}

// Overwrites loading from mMinSpeed at 80283788
void paramsReplace_receiveMessage_80283788() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2e1c (9)");
	__asm("b paramsReplace_receiveMessage_80283788_b");
}

// Overwrites loading from mWaterEmit at 8028378c
void paramsReplace_receiveMessage_8028378c() {
	toRegister(7, ((char *)newMarioParams)[0x2df4]);
	__asm("b paramsReplace_receiveMessage_8028378c_b");
}

// Overwrites loading from mDownType at 80283790
void paramsReplace_receiveMessage_80283790() {
	toRegister(6, ((char *)newMarioParams)[0x2de0]);
	__asm("b paramsReplace_receiveMessage_80283790_b");
}

// Overwrites loading from mInvincibleTime at 80283c48
void paramsReplace_receiveMessage_80283c48() {
	toRegister(9, ((short *)newMarioParams)[0x168e]);
	__asm("b paramsReplace_receiveMessage_80283c48_b");
}

// Overwrites loading from mDirty at 80283c50
void paramsReplace_receiveMessage_80283c50() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x2d08 (9)");
	__asm("b paramsReplace_receiveMessage_80283c50_b");
}

// Overwrites loading from mMinSpeed at 80283c5c
void paramsReplace_receiveMessage_80283c5c() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2cf4 (9)");
	__asm("b paramsReplace_receiveMessage_80283c5c_b");
}

// Overwrites loading from mWaterEmit at 80283c60
void paramsReplace_receiveMessage_80283c60() {
	toRegister(7, ((char *)newMarioParams)[0x2ccc]);
	__asm("b paramsReplace_receiveMessage_80283c60_b");
}

// Overwrites loading from mDownType at 80283c64
void paramsReplace_receiveMessage_80283c64() {
	toRegister(6, ((char *)newMarioParams)[0x2cb8]);
	__asm("b paramsReplace_receiveMessage_80283c64_b");
}

// Overwrites loading from mDownType at 80283cc4
void paramsReplace_receiveMessage_80283cc4() {
	toRegister(6, ((char *)newMarioParams)[0x2b90]);
	__asm("b paramsReplace_receiveMessage_80283cc4_b");
}

// Overwrites loading from mMinSpeed at 80283cd8
void paramsReplace_receiveMessage_80283cd8() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2bcc (9)");
	__asm("b paramsReplace_receiveMessage_80283cd8_b");
}

// Overwrites loading from mDirty at 80283ce0
void paramsReplace_receiveMessage_80283ce0() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x2be0 (9)");
	__asm("b paramsReplace_receiveMessage_80283ce0_b");
}

// Overwrites loading from mInvincibleTime at 80283d18
void paramsReplace_receiveMessage_80283d18() {
	toRegister(9, ((short *)newMarioParams)[0x1644]);
	__asm("b paramsReplace_receiveMessage_80283d18_b");
}

// Overwrites loading from mDirty at 80283d20
void paramsReplace_receiveMessage_80283d20() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x2c74 (9)");
	__asm("b paramsReplace_receiveMessage_80283d20_b");
}

// Overwrites loading from mMinSpeed at 80283d2c
void paramsReplace_receiveMessage_80283d2c() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2c60 (9)");
	__asm("b paramsReplace_receiveMessage_80283d2c_b");
}

// Overwrites loading from mWaterEmit at 80283d30
void paramsReplace_receiveMessage_80283d30() {
	toRegister(7, ((char *)newMarioParams)[0x2c38]);
	__asm("b paramsReplace_receiveMessage_80283d30_b");
}

// Overwrites loading from mDownType at 80283d34
void paramsReplace_receiveMessage_80283d34() {
	toRegister(6, ((char *)newMarioParams)[0x2c24]);
	__asm("b paramsReplace_receiveMessage_80283d34_b");
}

// Overwrites loading from mInvincibleTime at 80283d74
void paramsReplace_receiveMessage_80283d74() {
	toRegister(9, ((short *)newMarioParams)[0x1644]);
	__asm("b paramsReplace_receiveMessage_80283d74_b");
}

// Overwrites loading from mDirty at 80283d7c
void paramsReplace_receiveMessage_80283d7c() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x2c74 (9)");
	__asm("b paramsReplace_receiveMessage_80283d7c_b");
}

// Overwrites loading from mMinSpeed at 80283d88
void paramsReplace_receiveMessage_80283d88() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2c60 (9)");
	__asm("b paramsReplace_receiveMessage_80283d88_b");
}

// Overwrites loading from mWaterEmit at 80283d8c
void paramsReplace_receiveMessage_80283d8c() {
	toRegister(7, ((char *)newMarioParams)[0x2c38]);
	__asm("b paramsReplace_receiveMessage_80283d8c_b");
}

// Overwrites loading from mDownType at 80283d90
void paramsReplace_receiveMessage_80283d90() {
	toRegister(6, ((char *)newMarioParams)[0x2c24]);
	__asm("b paramsReplace_receiveMessage_80283d90_b");
}

// Overwrites loading from mInvincibleTime at 80283e3c
void paramsReplace_receiveMessage_80283e3c() {
	toRegister(9, ((short *)newMarioParams)[0x1894]);
	__asm("b paramsReplace_receiveMessage_80283e3c_b");
}

// Overwrites loading from mDirty at 80283e44
void paramsReplace_receiveMessage_80283e44() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x3114 (9)");
	__asm("b paramsReplace_receiveMessage_80283e44_b");
}

// Overwrites loading from mMinSpeed at 80283e50
void paramsReplace_receiveMessage_80283e50() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x3100 (9)");
	__asm("b paramsReplace_receiveMessage_80283e50_b");
}

// Overwrites loading from mWaterEmit at 80283e54
void paramsReplace_receiveMessage_80283e54() {
	toRegister(7, ((char *)newMarioParams)[0x30d8]);
	__asm("b paramsReplace_receiveMessage_80283e54_b");
}

// Overwrites loading from mDownType at 80283e58
void paramsReplace_receiveMessage_80283e58() {
	toRegister(6, ((char *)newMarioParams)[0x30c4]);
	__asm("b paramsReplace_receiveMessage_80283e58_b");
}

// Overwrites loading from mInvincibleTime at 80283ef8
void paramsReplace_receiveMessage_80283ef8() {
	toRegister(9, ((short *)newMarioParams)[0x15fa]);
	__asm("b paramsReplace_receiveMessage_80283ef8_b");
}

// Overwrites loading from mDirty at 80283f00
void paramsReplace_receiveMessage_80283f00() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x2be0 (9)");
	__asm("b paramsReplace_receiveMessage_80283f00_b");
}

// Overwrites loading from mMinSpeed at 80283f0c
void paramsReplace_receiveMessage_80283f0c() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2bcc (9)");
	__asm("b paramsReplace_receiveMessage_80283f0c_b");
}

// Overwrites loading from mWaterEmit at 80283f10
void paramsReplace_receiveMessage_80283f10() {
	toRegister(7, ((char *)newMarioParams)[0x2ba4]);
	__asm("b paramsReplace_receiveMessage_80283f10_b");
}

// Overwrites loading from mDownType at 80283f14
void paramsReplace_receiveMessage_80283f14() {
	toRegister(6, ((char *)newMarioParams)[0x2b90]);
	__asm("b paramsReplace_receiveMessage_80283f14_b");
}

// Overwrites loading from mInvincibleTime at 80283f98
void paramsReplace_receiveMessage_80283f98() {
	toRegister(9, ((short *)newMarioParams)[0x15fa]);
	__asm("b paramsReplace_receiveMessage_80283f98_b");
}

// Overwrites loading from mDirty at 80283fa0
void paramsReplace_receiveMessage_80283fa0() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x2be0 (9)");
	__asm("b paramsReplace_receiveMessage_80283fa0_b");
}

// Overwrites loading from mMinSpeed at 80283fac
void paramsReplace_receiveMessage_80283fac() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2bcc (9)");
	__asm("b paramsReplace_receiveMessage_80283fac_b");
}

// Overwrites loading from mWaterEmit at 80283fb0
void paramsReplace_receiveMessage_80283fb0() {
	toRegister(7, ((char *)newMarioParams)[0x2ba4]);
	__asm("b paramsReplace_receiveMessage_80283fb0_b");
}

// Overwrites loading from mDownType at 80283fb4
void paramsReplace_receiveMessage_80283fb4() {
	toRegister(6, ((char *)newMarioParams)[0x2b90]);
	__asm("b paramsReplace_receiveMessage_80283fb4_b");
}

// Overwrites loading from mInvincibleTime at 80284030
void paramsReplace_receiveMessage_80284030() {
	toRegister(9, ((short *)newMarioParams)[0x184a]);
	__asm("b paramsReplace_receiveMessage_80284030_b");
}

// Overwrites loading from mDirty at 80284038
void paramsReplace_receiveMessage_80284038() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x3080 (9)");
	__asm("b paramsReplace_receiveMessage_80284038_b");
}

// Overwrites loading from mMinSpeed at 80284044
void paramsReplace_receiveMessage_80284044() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x306c (9)");
	__asm("b paramsReplace_receiveMessage_80284044_b");
}

// Overwrites loading from mWaterEmit at 80284048
void paramsReplace_receiveMessage_80284048() {
	toRegister(7, ((char *)newMarioParams)[0x3044]);
	__asm("b paramsReplace_receiveMessage_80284048_b");
}

// Overwrites loading from mDownType at 8028404c
void paramsReplace_receiveMessage_8028404c() {
	toRegister(6, ((char *)newMarioParams)[0x3030]);
	__asm("b paramsReplace_receiveMessage_8028404c_b");
}

// Overwrites loading from mInvincibleTime at 8028408c
void paramsReplace_receiveMessage_8028408c() {
	toRegister(9, ((short *)newMarioParams)[0x1722]);
	__asm("b paramsReplace_receiveMessage_8028408c_b");
}

// Overwrites loading from mDirty at 80284094
void paramsReplace_receiveMessage_80284094() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x2e30 (9)");
	__asm("b paramsReplace_receiveMessage_80284094_b");
}

// Overwrites loading from mMinSpeed at 802840a0
void paramsReplace_receiveMessage_802840a0() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2e1c (9)");
	__asm("b paramsReplace_receiveMessage_802840a0_b");
}

// Overwrites loading from mWaterEmit at 802840a4
void paramsReplace_receiveMessage_802840a4() {
	toRegister(7, ((char *)newMarioParams)[0x2df4]);
	__asm("b paramsReplace_receiveMessage_802840a4_b");
}

// Overwrites loading from mDownType at 802840a8
void paramsReplace_receiveMessage_802840a8() {
	toRegister(6, ((char *)newMarioParams)[0x2de0]);
	__asm("b paramsReplace_receiveMessage_802840a8_b");
}

// Overwrites loading from mInvincibleTime at 802840ec
void paramsReplace_receiveMessage_802840ec() {
	toRegister(9, ((short *)newMarioParams)[0x1722]);
	__asm("b paramsReplace_receiveMessage_802840ec_b");
}

// Overwrites loading from mDirty at 802840f4
void paramsReplace_receiveMessage_802840f4() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x2e30 (9)");
	__asm("b paramsReplace_receiveMessage_802840f4_b");
}

// Overwrites loading from mMinSpeed at 80284100
void paramsReplace_receiveMessage_80284100() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2e1c (9)");
	__asm("b paramsReplace_receiveMessage_80284100_b");
}

// Overwrites loading from mWaterEmit at 80284104
void paramsReplace_receiveMessage_80284104() {
	toRegister(7, ((char *)newMarioParams)[0x2df4]);
	__asm("b paramsReplace_receiveMessage_80284104_b");
}

// Overwrites loading from mDownType at 80284108
void paramsReplace_receiveMessage_80284108() {
	toRegister(6, ((char *)newMarioParams)[0x2de0]);
	__asm("b paramsReplace_receiveMessage_80284108_b");
}

// Overwrites loading from mInvincibleTime at 802843a4
void paramsReplace_receiveMessage_802843a4() {
	toRegister(9, ((short *)newMarioParams)[0x1722]);
	__asm("b paramsReplace_receiveMessage_802843a4_b");
}

// Overwrites loading from mDirty at 802843ac
void paramsReplace_receiveMessage_802843ac() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x2e30 (9)");
	__asm("b paramsReplace_receiveMessage_802843ac_b");
}

// Overwrites loading from mMinSpeed at 802843b8
void paramsReplace_receiveMessage_802843b8() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2e1c (9)");
	__asm("b paramsReplace_receiveMessage_802843b8_b");
}

// Overwrites loading from mWaterEmit at 802843bc
void paramsReplace_receiveMessage_802843bc() {
	toRegister(7, ((char *)newMarioParams)[0x2df4]);
	__asm("b paramsReplace_receiveMessage_802843bc_b");
}

// Overwrites loading from mDownType at 802843c0
void paramsReplace_receiveMessage_802843c0() {
	toRegister(6, ((char *)newMarioParams)[0x2de0]);
	__asm("b paramsReplace_receiveMessage_802843c0_b");
}

// Overwrites loading from mInvincibleTime at 80284468
void paramsReplace_receiveMessage_80284468() {
	toRegister(9, ((short *)newMarioParams)[0x15fa]);
	__asm("b paramsReplace_receiveMessage_80284468_b");
}

// Overwrites loading from mDirty at 80284470
void paramsReplace_receiveMessage_80284470() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x2be0 (9)");
	__asm("b paramsReplace_receiveMessage_80284470_b");
}

// Overwrites loading from mMinSpeed at 8028447c
void paramsReplace_receiveMessage_8028447c() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2bcc (9)");
	__asm("b paramsReplace_receiveMessage_8028447c_b");
}

// Overwrites loading from mWaterEmit at 80284480
void paramsReplace_receiveMessage_80284480() {
	toRegister(7, ((char *)newMarioParams)[0x2ba4]);
	__asm("b paramsReplace_receiveMessage_80284480_b");
}

// Overwrites loading from mDownType at 80284484
void paramsReplace_receiveMessage_80284484() {
	toRegister(6, ((char *)newMarioParams)[0x2b90]);
	__asm("b paramsReplace_receiveMessage_80284484_b");
}

// Overwrites loading from mInvincibleTime at 802844c4
void paramsReplace_receiveMessage_802844c4() {
	toRegister(9, ((short *)newMarioParams)[0x16d8]);
	__asm("b paramsReplace_receiveMessage_802844c4_b");
}

// Overwrites loading from mDirty at 802844cc
void paramsReplace_receiveMessage_802844cc() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x2d9c (9)");
	__asm("b paramsReplace_receiveMessage_802844cc_b");
}

// Overwrites loading from mMinSpeed at 802844d8
void paramsReplace_receiveMessage_802844d8() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2d88 (9)");
	__asm("b paramsReplace_receiveMessage_802844d8_b");
}

// Overwrites loading from mWaterEmit at 802844dc
void paramsReplace_receiveMessage_802844dc() {
	toRegister(7, ((char *)newMarioParams)[0x2d60]);
	__asm("b paramsReplace_receiveMessage_802844dc_b");
}

// Overwrites loading from mDownType at 802844e0
void paramsReplace_receiveMessage_802844e0() {
	toRegister(6, ((char *)newMarioParams)[0x2d4c]);
	__asm("b paramsReplace_receiveMessage_802844e0_b");
}

// Overwrites loading from mInvincibleTime at 802845d4
void paramsReplace_receiveMessage_802845d4() {
	toRegister(9, ((short *)newMarioParams)[0x176c]);
	__asm("b paramsReplace_receiveMessage_802845d4_b");
}

// Overwrites loading from mDirty at 802845dc
void paramsReplace_receiveMessage_802845dc() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x2ec4 (9)");
	__asm("b paramsReplace_receiveMessage_802845dc_b");
}

// Overwrites loading from mMinSpeed at 802845e8
void paramsReplace_receiveMessage_802845e8() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2eb0 (9)");
	__asm("b paramsReplace_receiveMessage_802845e8_b");
}

// Overwrites loading from mWaterEmit at 802845ec
void paramsReplace_receiveMessage_802845ec() {
	toRegister(7, ((char *)newMarioParams)[0x2e88]);
	__asm("b paramsReplace_receiveMessage_802845ec_b");
}

// Overwrites loading from mDownType at 802845f0
void paramsReplace_receiveMessage_802845f0() {
	toRegister(6, ((char *)newMarioParams)[0x2e74]);
	__asm("b paramsReplace_receiveMessage_802845f0_b");
}

// Overwrites loading from mInvincibleTime at 80284690
void paramsReplace_receiveMessage_80284690() {
	toRegister(9, ((short *)newMarioParams)[0x1722]);
	__asm("b paramsReplace_receiveMessage_80284690_b");
}

// Overwrites loading from mDirty at 80284698
void paramsReplace_receiveMessage_80284698() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x2e30 (9)");
	__asm("b paramsReplace_receiveMessage_80284698_b");
}

// Overwrites loading from mMinSpeed at 802846a4
void paramsReplace_receiveMessage_802846a4() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2e1c (9)");
	__asm("b paramsReplace_receiveMessage_802846a4_b");
}

// Overwrites loading from mWaterEmit at 802846a8
void paramsReplace_receiveMessage_802846a8() {
	toRegister(7, ((char *)newMarioParams)[0x2df4]);
	__asm("b paramsReplace_receiveMessage_802846a8_b");
}

// Overwrites loading from mDownType at 802846ac
void paramsReplace_receiveMessage_802846ac() {
	toRegister(6, ((char *)newMarioParams)[0x2de0]);
	__asm("b paramsReplace_receiveMessage_802846ac_b");
}

// Overwrites loading from mInvincibleTime at 802847b4
void paramsReplace_receiveMessage_802847b4() {
	toRegister(9, ((short *)newMarioParams)[0x176c]);
	__asm("b paramsReplace_receiveMessage_802847b4_b");
}

// Overwrites loading from mDirty at 802847bc
void paramsReplace_receiveMessage_802847bc() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x2ec4 (9)");
	__asm("b paramsReplace_receiveMessage_802847bc_b");
}

// Overwrites loading from mMinSpeed at 802847c8
void paramsReplace_receiveMessage_802847c8() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2eb0 (9)");
	__asm("b paramsReplace_receiveMessage_802847c8_b");
}

// Overwrites loading from mWaterEmit at 802847cc
void paramsReplace_receiveMessage_802847cc() {
	toRegister(7, ((char *)newMarioParams)[0x2e88]);
	__asm("b paramsReplace_receiveMessage_802847cc_b");
}

// Overwrites loading from mDownType at 802847d0
void paramsReplace_receiveMessage_802847d0() {
	toRegister(6, ((char *)newMarioParams)[0x2e74]);
	__asm("b paramsReplace_receiveMessage_802847d0_b");
}

// Overwrites loading from mInvincibleTime at 8028488c
void paramsReplace_receiveMessage_8028488c() {
	toRegister(9, ((short *)newMarioParams)[0x176c]);
	__asm("b paramsReplace_receiveMessage_8028488c_b");
}

// Overwrites loading from mDirty at 80284894
void paramsReplace_receiveMessage_80284894() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x2ec4 (9)");
	__asm("b paramsReplace_receiveMessage_80284894_b");
}

// Overwrites loading from mMinSpeed at 802848a0
void paramsReplace_receiveMessage_802848a0() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2eb0 (9)");
	__asm("b paramsReplace_receiveMessage_802848a0_b");
}

// Overwrites loading from mWaterEmit at 802848a4
void paramsReplace_receiveMessage_802848a4() {
	toRegister(7, ((char *)newMarioParams)[0x2e88]);
	__asm("b paramsReplace_receiveMessage_802848a4_b");
}

// Overwrites loading from mDownType at 802848a8
void paramsReplace_receiveMessage_802848a8() {
	toRegister(6, ((char *)newMarioParams)[0x2e74]);
	__asm("b paramsReplace_receiveMessage_802848a8_b");
}

// Overwrites loading from mInvincibleTime at 80284900
void paramsReplace_receiveMessage_80284900() {
	toRegister(9, ((short *)newMarioParams)[0x1800]);
	__asm("b paramsReplace_receiveMessage_80284900_b");
}

// Overwrites loading from mDirty at 80284908
void paramsReplace_receiveMessage_80284908() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x2fec (9)");
	__asm("b paramsReplace_receiveMessage_80284908_b");
}

// Overwrites loading from mMinSpeed at 80284914
void paramsReplace_receiveMessage_80284914() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x2fd8 (9)");
	__asm("b paramsReplace_receiveMessage_80284914_b");
}

// Overwrites loading from mWaterEmit at 80284918
void paramsReplace_receiveMessage_80284918() {
	toRegister(7, ((char *)newMarioParams)[0x2fb0]);
	__asm("b paramsReplace_receiveMessage_80284918_b");
}

// Overwrites loading from mDownType at 8028491c
void paramsReplace_receiveMessage_8028491c() {
	toRegister(6, ((char *)newMarioParams)[0x2f9c]);
	__asm("b paramsReplace_receiveMessage_8028491c_b");
}

// Overwrites loading from mInvincibleTime at 80284c30
void paramsReplace_receiveMessage_80284c30() {
	toRegister(9, ((short *)newMarioParams)[0x1972]);
	__asm("b paramsReplace_receiveMessage_80284c30_b");
}

// Overwrites loading from mDirty at 80284c38
void paramsReplace_receiveMessage_80284c38() {
	toRegister(9, newMarioParams);
	__asm("lfs 2, 0x32d0 (9)");
	__asm("b paramsReplace_receiveMessage_80284c38_b");
}

// Overwrites loading from mMinSpeed at 80284c44
void paramsReplace_receiveMessage_80284c44() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x32bc (9)");
	__asm("b paramsReplace_receiveMessage_80284c44_b");
}

// Overwrites loading from mWaterEmit at 80284c48
void paramsReplace_receiveMessage_80284c48() {
	toRegister(7, ((char *)newMarioParams)[0x3294]);
	__asm("b paramsReplace_receiveMessage_80284c48_b");
}

// Overwrites loading from mDownType at 80284c4c
void paramsReplace_receiveMessage_80284c4c() {
	toRegister(6, ((char *)newMarioParams)[0x3280]);
	__asm("b paramsReplace_receiveMessage_80284c4c_b");
}

// Overwrites loading from mKickFreezeTime at 80284d60
void paramsReplace_receiveMessage_80284d60() {
	toRegister(0, ((short *)newMarioParams)[0x1e2]);
	__asm("b paramsReplace_receiveMessage_80284d60_b");
}

// Overwrites loading from mSinkTime at 802855a8
void paramsReplace_animSound_802855a8() {
	toRegister(3, ((short *)newMarioParams)[0xf5a]);
	__asm("b paramsReplace_animSound_802855a8_b");
}

// Overwrites loading from mSinkDmgDepth at 802855b8
void paramsReplace_animSound_802855b8() {
	toRegister(9, newMarioParams);
	__asm("lfs 0, 0x1f68 (9)");
	__asm("b paramsReplace_animSound_802855b8_b");
}

// Overwrites loading from mSinkTime at 802856dc
void paramsReplace_animSound_802856dc() {
	toRegister(3, ((short *)newMarioParams)[0xf5a]);
	__asm("b paramsReplace_animSound_802856dc_b");
}

// Overwrites loading from mSinkHeight at 802856ec
void paramsReplace_animSound_802856ec() {
	toRegister(9, newMarioParams);
	__asm("lfs 1, 0x1edc (9)");
	__asm("b paramsReplace_animSound_802856ec_b");
}
