;   Copyright(c) 2013, 2014 Renesas Electronics Corporation
;   RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY.
;   This program must be used solely for the purpose for which
;   it was furnished by Renesas Electronics Corporation. No part of this
;   program may be reproduced or disclosed to others, in any
;   form, without the prior written permission of Renesas Electronics
;   Corporation.

;   NOTE       : THIS IS A TYPICAL EXAMPLE FOR SINGLE CORE PROJECT.

	; example of using eiint as table reference method
	USE_TABLE_REFERENCE_METHOD .set 1

	; The following is the addresses in R7F7010352AFP.
	; Specify values suitable to your system if needed.
	PRIMARY_LOCAL_RAM_ADDR	.set	0xfede0000
	PRIMARY_LOCAL_RAM_END	.set	0xfedfffff

	SECONDARY_LOCAL_RAM_ADDR .set	0xfedd8000
	SECONDARY_LOCAL_RAM_END  .set	0xfeddffff

	RETENTION_RAM_ADDR	.set	0xfee00000
	RETENTION_RAM_END	.set	0xfee07fff


;-----------------------------------------------------------------------------
;	system stack
;-----------------------------------------------------------------------------
STACKSIZE	.set	0x200
	.section	".stack.bss", bss
	.align	4
	.ds	(STACKSIZE)
	.align	4
_stacktop:

;-----------------------------------------------------------------------------
;	section initialize table
;-----------------------------------------------------------------------------
	.section	".INIT_DSEC.const", const
	.align	4
	.dw	#__s.data,	#__e.data,	#__s.data.R

	.section	".INIT_BSEC.const", const
	.align	4
	.dw	#__s.bss,	#__e.bss

;-----------------------------------------------------------------------------
;	startup
;-----------------------------------------------------------------------------
	.section	".text", text
	.public	__start
	.align	2
__start:
$if 1	; initialize register
	$nowarning
	mov	r0, r1
	$warning
	mov	r0, r2
	mov	r0, r3
	mov	r0, r4
	mov	r0, r5
	mov	r0, r6
	mov	r0, r7
	mov	r0, r8
	mov	r0, r9
	mov	r0, r10
	mov	r0, r11
	mov	r0, r12
	mov	r0, r13
	mov	r0, r14
	mov	r0, r15
	mov	r0, r16
	mov	r0, r17
	mov	r0, r18
	mov	r0, r19
	mov	r0, r20
	mov	r0, r21
	mov	r0, r22
	mov	r0, r23
	mov	r0, r24
	mov	r0, r25
	mov	r0, r26
	mov	r0, r27
	mov	r0, r28
	mov	r0, r29
	mov	r0, r30
	mov	r0, r31
	ldsr	r0, 0, 0		;  EIPC
	ldsr	r0, 16, 0		;  CTPC
$endif

	mov	#_stacktop, sp		;  set sp register
	mov	#__gp_data, gp		;  set gp register
	mov	#__ep_data, ep		;  set ep register

	jarl	_hdwinit, lp		;  initialize hardware

	mov	#__s.INIT_DSEC.const, r6
	mov	#__e.INIT_DSEC.const, r7
	mov	#__s.INIT_BSEC.const, r8
	mov	#__e.INIT_BSEC.const, r9
	jarl32	__INITSCT_RH, lp	;  initialize RAM area

$ifdef USE_TABLE_REFERENCE_METHOD
	jarl	_init_eiint, lp		; initialize exception
$endif

	; set various flags to PSW via FEPSW

	stsr	5, r10, 0		; r10 <- PSW

	;movhi	0x0001, r0, r11
	;or	r11, r10
	;ldsr	r10, 5, 0		; enable FPU

	;movhi	0x0002, r0, r11
	;ldsr	r11, 6, 0		; initialize FPSR
	;ldsr	r0, 7, 0		; initialize FPEPC

	;xori	0x0020, r10, r10	; enable interrupt

	;movhi	0x4000, r0, r11
	;or	r11, r10		; supervisor mode -> user mode

	ldsr	r10, 3, 0		; FEPSW <- r10

	mov	#_exit, lp		; lp <- #_exit
	mov	#_main, r10
	ldsr	r10, 2, 0		; FEPC <- #_main

	; apply PSW and PC to start user mode
	feret

_exit:
	br	_exit			;  end of program
;-----------------------------------------------------------------------------
;	abort
;-----------------------------------------------------------------------------
	.public	_abort
	.align	2
_abort:
	br	_abort


;-----------------------------------------------------------------------------
;	hdwinit
;-----------------------------------------------------------------------------
	.section	".text", text
	.align	2
_hdwinit:
	mov	lp, r14			; save return address

	mov	PRIMARY_LOCAL_RAM_ADDR, r6
	mov	PRIMARY_LOCAL_RAM_END, r7
	jarl	_zeroclr4, lp		; clear Primary local RAM

	mov	SECONDARY_LOCAL_RAM_ADDR, r6
	mov	SECONDARY_LOCAL_RAM_END, r7
	jarl	_zeroclr4, lp		; clear Secondary local RAM

	;mov	RETENTION_RAM_ADDR, r6
	;mov	RETENTION_RAM_END, r7
	;jarl	_zeroclr4, lp		; clear Retention RAM

	mov	r14, lp
	jmp	[lp]

;-----------------------------------------------------------------------------
;	zeroclr4
;-----------------------------------------------------------------------------
	.align	2
_zeroclr4:
	br	.L.zeroclr4.2
.L.zeroclr4.1:
	st.w	r0, [r6]
	add	4, r6
.L.zeroclr4.2:
	cmp	r6, r7
	bh	.L.zeroclr4.1
	jmp	[lp]

$ifdef USE_TABLE_REFERENCE_METHOD
;-----------------------------------------------------------------------------
;	init_eiint
;-----------------------------------------------------------------------------
	; interrupt control register address
	ICBASE	.set	0xffff9000

	.align	2
_init_eiint:
	mov	#__sEIINTTBL, r10
	ldsr	r10, 4, 1		; set INTBP

	; Some interrupt channels use the table reference method.
	mov	ICBASE, r10		; get interrupt control register address
	set1	6, 0[r10]		; set INT0 as table reference
	set1	6, 2[r10]		; set INT1 as table reference
	set1	6, 4[r10]		; set INT2 as table reference

	jmp	[lp]
$endif

;-----------------------------------------------------------------------------
;	dummy section
;-----------------------------------------------------------------------------
	.section	".data", data
.L.dummy.data:
	.section	".bss", bss
.L.dummy.bss:
	.section	".const", const
.L.dummy.const:
	.section	".text", text
.L.dummy.text:
;-------------------- end of start up module -------------------;