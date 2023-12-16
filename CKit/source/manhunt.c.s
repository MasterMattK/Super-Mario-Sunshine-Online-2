	.file	"manhunt.c"
	.machine ppc
	.section	".text"
	.align 2
	.globl manhunt_checkIfReset
	.type	manhunt_checkIfReset, @function
manhunt_checkIfReset:
	lis 9,manhuntReset@ha
	lbz 9,manhuntReset@l(9)
	cmpwi 0,9,0
	beqlr- 0
	li 9,0
	lis 10,manhuntBool@ha
	stb 9,manhuntBool@l(10)
	lis 10,manhuntReset@ha
	stb 9,manhuntReset@l(10)
	blr
	.size	manhunt_checkIfReset, .-manhunt_checkIfReset
	.align 2
	.globl checkHunterFlags
	.type	checkHunterFlags, @function
checkHunterFlags:
	lis 9,gamemode@ha
	lwz 9,gamemode@l(9)
	cmpwi 0,9,2
	bnelr- 0
#APP
 # 72 "../source/defines.h" 1
	lwz 9, -24792(13)
 # 0 "" 2
#NO_APP
	lbz 10,281(9)
	lwz 7,992(9)
	lis 8,isHunter@ha
	lbz 8,isHunter@l(8)
	cmpwi 0,8,0
	beq- 0,.L5
	andi. 8,10,0x10
	bnelr- 0
	addi 10,10,16
	stb 10,281(9)
	li 9,5
	stb 9,5(7)
	blr
.L5:
	andi. 8,10,0x10
	beqlr- 0
	addi 10,10,-16
	stb 10,281(9)
	li 9,1
	stb 9,5(7)
	blr
	.size	checkHunterFlags, .-checkHunterFlags
	.align 2
	.globl setCooldown
	.type	setCooldown, @function
setCooldown:
	lis 9,cooldown@ha
	stw 3,cooldown@l(9)
	lis 9,currentTime@ha
	lwz 10,currentTime@l(9)
	lis 9,cooldownStarted@ha
	stw 10,cooldownStarted@l(9)
	blr
	.size	setCooldown, .-setCooldown
	.align 2
	.globl isInCooldown
	.type	isInCooldown, @function
isInCooldown:
	lis 9,currentTime@ha
	lwz 10,currentTime@l(9)
	lis 9,cooldown@ha
	lwz 9,cooldown@l(9)
	subf 9,9,10
	lis 10,cooldownStarted@ha
	lwz 10,cooldownStarted@l(10)
	subfc 10,10,9
	subfe 3,3,3
	neg 3,3
	blr
	.size	isInCooldown, .-isInCooldown
	.align 2
	.globl manhunt_checkIfTagged
	.type	manhunt_checkIfTagged, @function
manhunt_checkIfTagged:
	lis 9,gamemode@ha
	lwz 9,gamemode@l(9)
	cmpwi 0,9,2
	bnelr- 0
	lis 9,manhuntBool@ha
	lbz 9,manhuntBool@l(9)
	cmpwi 0,9,0
	beqlr- 0
	stwu 1,-16(1)
	stw 31,12(1)
#APP
 # 54 "../source/defines.h" 1
	mr 3, 30
 # 0 "" 2
 # 72 "../source/defines.h" 1
	lwz 31, -24792(13)
 # 0 "" 2
#NO_APP
	cmplw 0,3,31
	beq- 0,.L8
	lbz 9,281(3)
	slwi 9,9,3
	cmpwi 0,9,127
	ble- 0,.L8
	lbz 9,281(31)
	slwi 9,9,3
	cmpwi 0,9,127
	ble- 0,.L17
.L8:
	lwz 31,12(1)
	addi 1,1,16
	blr
.L17:
	mflr 0
	stw 0,20(1)
	lis 9,.LC0@ha
	lfs 4,.LC0@l(9)
	lis 9,.LC1@ha
	lfs 3,.LC1@l(9)
	lis 9,.LC2@ha
	lfs 2,.LC2@l(9)
	lis 9,.LC3@ha
	lfs 1,.LC3@l(9)
	addi 4,31,16
	addi 3,3,16
	bl checkDistance
	cmpwi 0,3,1
	beq- 0,.L18
	lwz 0,20(1)
	mtlr 0
	b .L8
.L18:
	lwz 10,124(31)
	lis 9,0x2
	ori 9,9,0x467
	cmpw 0,10,9
	beq- 0,.L15
	bl isInCooldown
	cmpwi 0,3,0
	beq- 0,.L19
	lwz 0,20(1)
	mtlr 0
	b .L8
.L19:
	li 7,15
	li 6,0
	li 5,3
	li 4,2
	mr 3,31
	bl floorDamageExec
	li 3,2
	crxor 6,6,6
	bl setCooldown
	lwz 0,20(1)
	mtlr 0
	b .L8
.L15:
	lwz 0,20(1)
	mtlr 0
	b .L8
	.size	manhunt_checkIfTagged, .-manhunt_checkIfTagged
	.align 2
	.globl manhuntMain
	.type	manhuntMain, @function
manhuntMain:
	stwu 1,-8(1)
	mflr 0
	stw 0,12(1)
	bl manhunt_checkIfReset
	bl manhunt_checkIfTagged
	bl checkHunterFlags
	lwz 0,12(1)
	mtlr 0
	addi 1,1,8
	blr
	.size	manhuntMain, .-manhuntMain
	.align 2
	.globl manhunt_onStageLoad
	.type	manhunt_onStageLoad, @function
manhunt_onStageLoad:
	stwu 1,-8(1)
	mflr 0
	stw 0,12(1)
	li 3,3
	bl setCooldown
	lwz 0,12(1)
	mtlr 0
	addi 1,1,8
	blr
	.size	manhunt_onStageLoad, .-manhunt_onStageLoad
	.globl cooldownStarted
	.globl cooldown
	.globl manhuntReset
	.globl manhuntBool
	.globl isHunter
	.section	.rodata.cst4,"aM",@progbits,4
	.align 2
.LC0:
	.long	1126825984
	.align 2
.LC1:
	.long	1118044160
	.align 2
.LC2:
	.long	1119092736
	.align 2
.LC3:
	.long	1123024896
	.section	.sbss,"aw",@nobits
	.align 2
	.type	cooldownStarted, @object
	.size	cooldownStarted, 4
cooldownStarted:
	.zero	4
	.type	cooldown, @object
	.size	cooldown, 4
cooldown:
	.zero	4
	.type	manhuntReset, @object
	.size	manhuntReset, 1
manhuntReset:
	.zero	1
	.type	manhuntBool, @object
	.size	manhuntBool, 1
manhuntBool:
	.zero	1
	.type	isHunter, @object
	.size	isHunter, 1
isHunter:
	.zero	1
	.ident	"GCC: (devkitPPC release 41) 12.1.0"
	.gnu_attribute 4, 1
