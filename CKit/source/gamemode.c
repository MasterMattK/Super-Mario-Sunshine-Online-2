// this file is for shared resources between the gamemodes
#include "defines.h"

// all of the function prototypes for in-game funcs we use
void PSMTXMultiVec(const Mtx matrix, const Vector3f *source, Vector3f *dest);
void PSMTXIdentity(Mtx matrix);
void GXSetCurrentMtx(u32 mtx);
void GXLoadPosMtxImm(Mtx mt, u32 pnidx);
void GXClearVtxDesc();
void GXSetVtxDesc(u8 attr, u8 type);
void GXSetVtxAttrFmt(u8 vtxfmt, u32 vtxattr, u32 comptype, u32 compsize, u32 frac);
void GXSetNumChans(u8 num);
void GXSetChanCtrl(s32 channel, u8 enable, u8 ambsrc, u8 matsrc, u8 litmask, u8 diff_fn, u8 attn_fn);
void GXSetNumTexGens(u32 nr);
void GXSetNumTevStages(u8 num);
void GXSetTevOrder(u8 tevstage, u8 texcoord, u32 texmap, u8 color);
void GXSetTevOp(u8 tevstage, u8 mode);
void GXSetZMode(u8 enable, u8 func, u8 update_enable);
void GXSetCullMode(u8 mode);
void GXSetChanMatColor(s32 channel, u32 color);
void GXBegin(u8 primitve, u8 vtxfmt, u16 vtxcnt);
void GXSetBlendMode(u8 type, u8 src_fact, u8 dst_fact, u8 op);

// draws a color-coded triangle above other marios' heads to indicate team
void drawTeamTriangle(u32 color, Vector3f *marioPos) {
  	float* cameraMatrix;;
  	float* mario = SDAword(-0x60D8);
  	float matrix[12];
  	Vector3f screenPos, triPos;
	const u32 GRAY = 0x000000C0, BLUE = 0x4040FFFF, BLACK = 0x00000000;

	triPos.x = marioPos->x;
	triPos.y = marioPos->y + 210;
	triPos.z = marioPos->z;

	float *camera = SDAword(-0x7118);
  	cameraMatrix = camera + (0x1ec / 4);

	PSMTXMultiVec(cameraMatrix, &triPos, &screenPos);
  	PSMTXIdentity(matrix);
  	GXSetCurrentMtx(0);
  	GXLoadPosMtxImm(matrix, 0);
  	GXLoadNrmMtxImm(matrix, 0);
  	GXClearVtxDesc();
  	GXSetVtxDesc(9, 1);
  	GXSetVtxAttrFmt(0, 9, 1, 4, 0);
  	GXSetNumChans(1);
  	GXSetChanCtrl(4, 0, 0, 0, 0, 0, 2);
  	GXSetChanCtrl(5, 0, 0, 0, 0, 0, 2);
  	GXSetNumTexGens(0);
  	GXSetNumTevStages(1);
  	GXSetTevOrder(0, 0xff, 0xff, 4);
  	GXSetTevOp(0, 4);
  	GXSetZMode(1, 3, 0);
  	GXSetCullMode(0);
  	GXSetChanMatColor(4, &GRAY);
  	GXSetBlendMode(1, 4, 5, 5);
  	GXBegin(0x80, 0, 4);

  	float healthBarLeft = screenPos.x - 48.0f;
  	float healthBarTop = screenPos.y - 10.0f;
  	float healthBarBottom = screenPos.y + 10.0f;
	
  	float leftMargin = healthBarLeft - 5.0f;
  	float topMargin = healthBarTop - 5.0f;
  	float bottomMargin = healthBarBottom + 5.0f;
  	float rightMargin = healthBarLeft + 101.0f;

  	GXFIFO_Addf(leftMargin);
  	GXFIFO_Addf(topMargin);
  	GXFIFO_Addf(screenPos.z);

  	GXFIFO_Addf(rightMargin);
  	GXFIFO_Addf(topMargin);
  	GXFIFO_Addf(screenPos.z);

  	GXFIFO_Addf(rightMargin);
  	GXFIFO_Addf(bottomMargin);
  	GXFIFO_Addf(screenPos.z);

  	GXFIFO_Addf(leftMargin);
  	GXFIFO_Addf(bottomMargin);
  	GXFIFO_Addf(screenPos.z);

  	GXSetChanMatColor(4, &BLUE);
  	GXBegin(0x80, 0, 4);

  	u16 marioHealth = ((u16*)mario)[0x120 / 2];
  	float healthBarRight = (float)(marioHealth * 12.0f + healthBarLeft);

  	GXFIFO_Addf(healthBarLeft);
  	GXFIFO_Addf(healthBarTop);
  	GXFIFO_Addf(screenPos.z);

  	GXFIFO_Addf(healthBarRight);
  	GXFIFO_Addf(healthBarTop);
  	GXFIFO_Addf(screenPos.z);

  	GXFIFO_Addf(healthBarRight);
  	GXFIFO_Addf(healthBarBottom);
  	GXFIFO_Addf(screenPos.z);

  	GXFIFO_Addf(healthBarLeft);
  	GXFIFO_Addf(healthBarBottom);
  	GXFIFO_Addf(screenPos.z);

  	GXSetBlendMode(0, 4, 5, 0);
}