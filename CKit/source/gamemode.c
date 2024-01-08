// this file is for shared resources between the gamemodes
#include "defines.h"

// this function links onto TMario::perform which allows us access to TGraphics
void marioDrawMain() {
	u32 performFlag = fromRegister(29);
	u32 *TGraphics = fromRegister(30);
	for (int i = 0; i < pNum; i++) {
		drawTeamTriangle((float *)marios[i], performFlag, TGraphics);
	}
}

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
void drawTeamTriangle(float *mario, u32 performFlag, u32 *TGraphics) {
  	float* cameraMatrix;
  	float matrix[12];
  	Vector3f screenPos, triPos;
	const u32 BLUE = 0x4040FFFF, RED = 0xFC0303FF, BLACK = 0x000000C0;
	u32 color;

	// only draw triangles when this bit is flipped
	if ((performFlag & 0x8) == 0)
    	return;
	else if (((u32 *)mario)[0x7C / 4] == 0x0000133F)
		return;

	u8 shirtFlag = ((u8 *)mario)[0x119];
	if (shirtFlag & 16) 
		color = RED;
	else
		color = BLUE;

	triPos.x = mario[0x10 / 4];
  	triPos.y = mario[0x14 / 4];
  	triPos.z = mario[0x18 / 4];

  	triPos.y += 210;

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
  	GXSetChanMatColor(4, &BLACK);
  	GXSetBlendMode(1, 4, 5, 5);
  	GXBegin(0x90, 0, 3);

  	float left = screenPos.x - 24.0f;
  	float right = screenPos.x + 24.0f;
  	float top = screenPos.y + 24.0f;
  	float bottom = screenPos.y - 24.0f;

  	GXFIFO_Addf(left - 5.0f);
  	GXFIFO_Addf(top + 5.0f);
  	GXFIFO_Addf(screenPos.z);

  	GXFIFO_Addf(right + 5.0f);
  	GXFIFO_Addf(top + 5.0f);
  	GXFIFO_Addf(screenPos.z);

  	GXFIFO_Addf(screenPos.x);
  	GXFIFO_Addf(bottom - 5.0f);
  	GXFIFO_Addf(screenPos.z);

	GXSetChanMatColor(4, &color);
  	GXBegin(0x90, 0, 3);

	GXFIFO_Addf(left);
  	GXFIFO_Addf(top);
  	GXFIFO_Addf(screenPos.z);

  	GXFIFO_Addf(right);
  	GXFIFO_Addf(top);
  	GXFIFO_Addf(screenPos.z);

  	GXFIFO_Addf(screenPos.x);
  	GXFIFO_Addf(bottom);
  	GXFIFO_Addf(screenPos.z);
}