;PCM driver for MSXturboR PCM BIOS
;Copyright 1996 GIGAMIX/nf_ban


;ＭＳＸシステムワーク

INTFLG	EQU	0FC9BH


;ＤＭシステム２関係

CALSLT	EQU	001CH		;インタースロットコール(DMシステム2専用)
MSXVER	EQU	4303H		;ＭＳＸ本体のバージョン番号


	ORG	2C00H

	DEFM	'PCMDRV for MSXturboR PCM BIOS (C)GIGAMIX'
	DEFB	1Ah		;EOF
	DEFB	01h		;PCMドライバの意
	DEFM	'うなぎ'	;未使用
	JP	PCMPLY		;PCM再生

PCMPLY:	EX	AF,AF'		;Aへの設定値を保存

	LD	A,(MSXVER)
	CP	3
	RET	NZ		;MSXturboR以外は即ret

	EX	AF,AF'		;Aへの設定値を復帰
	LD	IY,(0FCC0H)	;ROMのスロット
	LD	IX,0186H	;PCM BIOS(PCMPLY)
	CALL	CALSLT		;PCM再生

	OR	A
	LD	(INTFLG),A	;Ctrl+STOPフラグをクリアしておく

	RET

	END
