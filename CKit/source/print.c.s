	.file	"print.c"
	.machine ppc
	.section	".text"
	.align 2
	.globl initPrint
	.type	initPrint, @function
initPrint:
	stwu 1,-16(1)
	mflr 0
	stw 0,20(1)
	stw 31,12(1)
	mr 31,3
#APP
 # 97 "../source/defines.h" 1
	lwz 9, -24632(13)
 # 0 "" 2
#NO_APP
	mr 4,9
	cmpwi 0,9,0
	bne- 0,.L2
#APP
 # 97 "../source/defines.h" 1
	lwz 4, -24628(13)
 # 0 "" 2
#NO_APP
.L2:
	li 5,0
	mr 3,31
	crxor 6,6,6
	bl ct_Print
	mr 3,31
	crxor 6,6,6
	bl initiatePrint
	lwz 0,20(1)
	mtlr 0
	lwz 31,12(1)
	addi 1,1,16
	blr
	.size	initPrint, .-initPrint
	.align 2
	.globl initPrintDefaultSize
	.type	initPrintDefaultSize, @function
initPrintDefaultSize:
	stwu 1,-16(1)
	mflr 0
	stw 0,20(1)
	stw 31,12(1)
	mr 31,3
#APP
 # 97 "../source/defines.h" 1
	lwz 9, -24632(13)
 # 0 "" 2
#NO_APP
	mr 4,9
	cmpwi 0,9,0
	bne- 0,.L5
#APP
 # 97 "../source/defines.h" 1
	lwz 4, -24628(13)
 # 0 "" 2
#NO_APP
.L5:
	li 5,0
	mr 3,31
	crxor 6,6,6
	bl ct_Print
	mr 3,31
	crxor 6,6,6
	bl initiatePrint
	lwz 0,20(1)
	mtlr 0
	lwz 31,12(1)
	addi 1,1,16
	blr
	.size	initPrintDefaultSize, .-initPrintDefaultSize
	.ident	"GCC: (devkitPPC release 40) 11.2.0"
