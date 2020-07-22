;===== DM-system2 [BGM Driver <FM BIOS>] =====
;			(C)1996 GIGAMIX/Influenza
;96/08/24

BGFLAG	EQU	4300H+15
SLTOPL	EQU	4300H+16

INIOPL	EQU	4113H
MSTART	EQU	4116H
MSTOP	EQU	4119H
OPLDRV	EQU	411FH

	ORG	0400H
;======================================
;		 0....5....10...15...20...25...30...35...
	DEFM	'BGM:軽さと速さのFMBIOS GIGAMIX/Influenza'
	DEFB	1AH
	DEFB	03H	;Driver ID	[BGM]
	DEFB	02H	;BGM Data Type	[FM BIOS]
	DEFS	5
;======================================
	JP	BGMON	;BGMの演奏準備とデータ形式のチェック
	JP	BGMOFF	;BGMの演奏停止
	JP	BGMPAU	;ポーズとその解除
	JP	BGMTMP	;テンポの設定
	JP	BGMTRS	;トランスポーズの設定
	JP	BGMVOL	;音量の設定
	JP	PSGCHN	;PSGのチャンネルのON/OFF
PLAY:	JP	BGMINT	;1/60秒毎にコールされる、実際のBGMの演奏
;======================================
; BGMON
;[in]	HL	BGMデータの開始アドレス
;	A	ループ回数(0:無限) ※MGSDRVでは無効
;[out]	A	演奏状態 (0:正常 NZ:BASICでのエラーコード)

BGMON:
	LD	(DATADR),HL
	LD	(LOOP),A

	LD	A,(PLYFLG)	;Playing ?
	INC	A
	RET	Z

	LD	A,(SLTOPL)
	INC	A
	JP	Z,NOFM

	LD	A,(HL)		;Check 'Data Type'
	CP	0EH
	JR	Z,BGMON0
	CP	12H
	JR	NZ,TYPMIS
BGMON0:	INC	HL
	LD	A,(HL)
	OR	A
	JR	NZ,TYPMIS

	LD	A,(LOOP)	;ループ回数に 255を指定できない
	INC	A
	JR	Z,ILLGAL

	LD	HL,0038H	;割り込みを死なす
	LD	A,(HL)
	LD	(HL),0C9H
	PUSH	AF
;--- Page 1 [FM-BIOS] ------
	LD	A,(SLTOPL)
	LD	C,A
	AND	03H
	ADD	A,0C5H
	LD	L,A
	LD	H,0FCH		;SLTTBL = 0FCC5H
	LD	(STBADR),HL
	LD	A,(HL)
	AND	0CH
	PUSH	AF
	LD	A,C
	AND	83H
	LD	(SLTMSK),A

	LD	A,C
	LD	H,40H
	CALL	0024H

	LD	HL,FMWORK
	RES	0,L
	CALL	INIOPL

	LD	HL,(DATADR)
	LD	A,(LOOP)
	CALL	MSTART

	POP	BC
	LD	A,(SLTMSK)
	OR	B
	LD	H,40H
	CALL	0024H

	LD	A,(0F342H)
	LD	H,40H
	CALL	0024H
;---------------------------
	POP	AF		;割り込み復活さす
	LD	(0038H),A

	LD	A,0FFH
	LD	(PLYFLG),A

	XOR	A
	RET
;= = = = = = = = = = = = = = = = = =
NOFM:	LD	A,0C9H
	LD	(PLAY),A
	XOR	A
	RET

TYPMIS:	LD	A,13
	RET

ILLGAL:	LD	A,5
	RET
;======================================
; BGMOFF

BGMOFF:
	LD	A,(PLYFLG)	;Playing ?
	OR	A
	RET	Z

	LD	A,(SLTOPL)
	INC	A
	RET	Z

	LD	HL,0038H	;割り込みを死なす
	LD	A,(HL)
	LD	(HL),0C9H
	PUSH	AF
;--- Page 1 [FM-BIOS] ------
	LD	HL,(STBADR)
	LD	A,(HL)
	AND	0CH
	PUSH	AF

	LD	A,(SLTOPL)
	LD	H,40H
	CALL	0024H

	CALL	MSTOP

	POP	BC
	LD	A,(SLTMSK)
	OR	B
	LD	H,40H
	CALL	0024H

	LD	A,(0F342H)
	LD	H,40H
	CALL	0024H
;---------------------------
	POP	AF		;割り込み復活さす
	LD	(0038H),A

	XOR	A
	LD	(PLYFLG),A
	RET
;======================================
; BGMPAUSE

BGMPAU:
	RET
;======================================
; BGMTEMPO

BGMTMP:
	RET
;======================================
; BGMTRANSPOSE
;[in]	A	8bitの2の補数(-128〜127)

BGMTRS:
	RET
;======================================
; BGMVOLUME
;[in]	A	マスターボリューム(0(小)〜15(大))
;	L	OPLLの音量相対値 (-15〜15)
;	E	PSG の音量相対値 (-15〜15)
;	C	SCC の音量相対値 (-15〜15)

BGMVOL:
	RET
;======================================
; PSGCHN
;[in]	L	b7〜b3	未使用
;		b2	PSGチャンネルC (0:OFF 1:ON)
;		b1	PSGチャンネルB (0:OFF 1:ON)
;		b0	PSGチャンネルA (0:OFF 1:ON)

PSGCHN:
	RET
;======================================
; BGMINT

BGMINT:
;	CALL	BLUE

	LD	HL,0038H	;割り込みを死なす
	LD	A,(HL)
	LD	(HL),0C9H
	PUSH	AF
;--- Page 1 [FM-BIOS] ------
	LD	HL,(STBADR)
	LD	A,(HL)
	AND	0CH
	PUSH	AF

	LD	A,(SLTOPL)
	LD	H,40H
	CALL	0024H

	CALL	OPLDRV

	POP	BC
	LD	A,(SLTMSK)
	OR	B
	LD	H,40H
	CALL	0024H

	LD	A,(0F342H)
	LD	H,40H
	CALL	0024H
;---------------------------
	POP	AF		;割り込み復活さす
	LD	(0038H),A

;	CALL	BLACK
	RET
;======================================
;BLUE:	DI
;	XOR	A
;	OUT	(99H),A
;	LD	A,16+80H
;	OUT	(99H),A
;	LD	A,07H
;	OUT	(9AH),A
;	XOR	A
;	OUT	(9AH),A
;	EI
;	RET
;
;BLACK:	DI
;	XOR	A
;	OUT	(99H),A
;	LD	A,16+80H
;	OUT	(99H),A
;	XOR	A
;	OUT	(9AH),A
;	XOR	A
;	OUT	(9AH),A
;	EI
;	RET
;======================================
SLTMSK:	DEFB	0
STBADR:	DEFW	0000		;SLTTBL Address
DATADR:	DEFW	0000
LOOP:	DEFB	0
PLYFLG:	DEFB	0
	DEFB	0
FMWORK:	DEFB	0

	END
