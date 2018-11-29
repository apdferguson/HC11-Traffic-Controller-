;;;-----------------------------------------
;;; Start MC68HC11 gcc assembly output
;;; gcc compiler 3.3.6-m68hc1x-20060122
;;; Command:	/usr/lib/gcc-lib/m68hc11/3.3.6-m68hc1x-20060122/cc1 -quiet -D__GNUC__=3 -D__GNUC_MINOR__=3 -D__GNUC_PATCHLEVEL__=6 -Dmc68hc1x -D__mc68hc1x__ -D__mc68hc1x -D__HAVE_SHORT_INT__ -D__INT__=16 -Dmc6811 -DMC6811 -Dmc68hc11 main.c -quiet -dumpbase main.c -mshort -auxbase main -Os -fomit-frame-pointer -o main.s
;;; Compiled:	Thu Nov 29 12:11:55 2018
;;; (META)compiled by GNU C version 6.3.0 20170221.
;;;-----------------------------------------
	.file	"main.c"
	.mode mshort
	.globl	highwayG
	.sect	.data
	.type	highwayG, @object
	.size	highwayG, 2
highwayG:
	.word	0
	.globl	fRd
	.type	fRd, @object
	.size	fRd, 1
fRd:
	.byte	0
	.globl	hCheck
	.type	hCheck, @object
	.size	hCheck, 1
hCheck:
	.byte	0
	.globl	state
	.type	state, @object
	.size	state, 1
state:
	.byte	0
	.sect	.text
	.globl	whereWePretendToDoOtherStuff
	.type	whereWePretendToDoOtherStuff,@function
whereWePretendToDoOtherStuff:
.L2:
	bra	.L2
	.size	whereWePretendToDoOtherStuff, .-whereWePretendToDoOtherStuff
	.globl	Amber
	.type	Amber,@function
Amber:
	ldab	state
	bne	.L6
	ldab	#1
	stab	state
	rts
.L6:
	cmpb	#2
	bne	.L5
	ldab	#3
	stab	state
.L5:
	rts
	.size	Amber, .-Amber
	.globl	tractorComin
	.type	tractorComin,@function
tractorComin:
	ldx	#4131
	ldab	#64
	stab	0,x
	ldab	fRd
	bne	.L10
	ldx	#4110
	ldd	0,x
	addd	#3000
	ldx	#4120
	std	0,x
	ldab	#1
	stab	fRd
	rts
.L10:
	cmpb	#1
	bne	.L9
	ldx	#4110
	ldd	0,x
	addd	#7000
	ldx	#4120
	std	0,x
	ldab	#2
	stab	fRd
.L9:
	rts
	.size	tractorComin, .-tractorComin
	.globl	highwayLighToggle
	.type	highwayLighToggle,@function
highwayLighToggle:
	ldd	highwayG
	bne	.L14
	ldd	#1
	std	highwayG
	rts
.L14:
	cpd	#1
	bne	.L13
	clr	highwayG+1
	clr	highwayG
.L13:
	rts
	.size	highwayLighToggle, .-highwayLighToggle
	.ident	"GCC: (GNU) 3.3.6-m68hc1x-20060122"
