;=== DM-system2 [Label List] ===
;(C)1995 GIGAMIX/Influenza
;1994/12/16 - 96/07/31
;========================
P1JUMP	EQU	4010H
INTRPT	EQU	P1JUMP
BCKGND	EQU	P1JUMP+3
CALRAM	EQU	P1JUMP+6
CALROM	EQU	P1JUMP+9
CALBAS	EQU	P1JUMP+12
CHGSLT	EQU	P1JUMP+15
CPUCHG	EQU	P1JUMP+18
CPUGET	EQU	P1JUMP+21
WRTOPL	EQU	P1JUMP+24

ENTRY	EQU	P1JUMP+27
VMON	EQU	ENTRY+0
VMOFF	EQU	ENTRY+5
CHGPLT	EQU	ENTRY+10
MCRINT	EQU	ENTRY+15
BGMON	EQU	ENTRY+20
BGMOFF	EQU	ENTRY+25
BGMPAU	EQU	ENTRY+30
BGMTMP	EQU	ENTRY+35
BGMTRS	EQU	ENTRY+40
MASVOL	EQU	ENTRY+45
PSGCHN	EQU	ENTRY+50
BGMINT	EQU	ENTRY+55
SEON	EQU	ENTRY+60
SEINT	EQU	ENTRY+65
DMM	EQU	ENTRY+70
DMMINT	EQU	ENTRY+75
DEVINI	EQU	ENTRY+80
DEVMOU	EQU	ENTRY+85
DEVSTK	EQU	ENTRY+90
DEVTRG	EQU	ENTRY+95

BLTRVR	EQU	ENTRY+100
BLTRVW	EQU	ENTRY+105
BLTRVV	EQU	ENTRY+110
CEWAIT	EQU	ENTRY+115
TMWAIT	EQU	ENTRY+120
PACLOA	EQU	ENTRY+125
PACSAV	EQU	ENTRY+130
LOAD	EQU	ENTRY+135
FILES	EQU	ENTRY+140
FSIZE	EQU	ENTRY+145
KANJI	EQU	ENTRY+150
PCMON	EQU	ENTRY+155
PCMDRV	EQU	ENTRY+160
DBPE	EQU	ENTRY+165
LCOPY	EQU	ENTRY+195
VCOPY	EQU	ENTRY+200
SIN	EQU	ENTRY+205
COS	EQU	ENTRY+210
CELLO	EQU	ENTRY+215
CELMNA	EQU	ENTRY+220
CELMNB	EQU	ENTRY+225
SETBIN	EQU	ENTRY+230
BINLOA	EQU	ENTRY+235
MAPINI	EQU	411BH
SAVE	EQU	411EH
;PRTHEX	EQU	4123h
;CHGBDF	equ	4126h	;同名ラベルがあるためグローバルラベル化できない
SETRDV	equ	4129h
SETWTV	equ	412Ch
;REQTBL	equ	412Fh
MAPALC	equ	4132h
MAPFRE	equ	4135h
MAPSUP	equ	4138h
BLTRSP	equ	413Bh
FIXPRM	equ	413Eh
;-----------------------
;4300H Information
XINFO	EQU	4300H
VER	EQU	XINFO
DMSLT0	EQU	XINFO+1
DMSLT1	EQU	XINFO+2
MSXVER	EQU	XINFO+3
VDPIN	EQU	XINFO+4
VDPOUT	EQU	XINFO+5
NEWCPU	EQU	XINFO+6
NATION	EQU	XINFO+7
PHYDRV	EQU	XINFO+8
MEDIA	EQU	XINFO+9
INTERL	EQU	XINFO+10
DOSVER	EQU	XINFO+11
MAXCPU  EQU     XINFO+12
EXTSW0	EQU	XINFO+13	;b0:AutoPause

BGFLAG	EQU	XINFO+15

SLTOPL	EQU	XINFO+16
SLTSCC	EQU	XINFO+17
SLTPAC	EQU	XINFO+18
SLTHAL	EQU	XINFO+19
SLTVIW	EQU	XINFO+20

PLTADD	EQU	XINFO+24	;2
SEADD	EQU	XINFO+26	;2
BINADD	EQU	XINFO+28	;2
BINDIR	EQU	XINFO+30	;8

VMADD	EQU	XINFO+38	;2

VOLMAS	EQU	XINFO+48
VOLOPL	EQU	XINFO+49
VOLPSG	EQU	XINFO+50
VOLSCC	EQU	XINFO+51
VOLTIM	EQU	XINFO+52	;2
BGMCOU	EQU	XINFO+54	;2
TMPTIM	EQU	XINFO+56	;2
FADVOL	EQU	XINFO+58
SEMSKA	EQU	XINFO+59
SEMSKB	EQU	XINFO+60
SEMSKC	EQU	XINFO+61
PAUFLG	equ	XINFO+62

RETDMM	EQU	XINFO+64
DMMDEV	EQU	XINFO+65
DMMX	EQU	XINFO+66
DMMY	EQU	XINFO+67
DMMPO1	EQU	XINFO+68
DMMPO2	EQU	XINFO+69
DMMTIM	EQU	XINFO+70	;2
DMMMOD	EQU	XINFO+72		;Low
DMMSPR	EQU	XINFO+73		;High
DMMKEY	EQU	XINFO+74	;16
ACCEL	EQU	Xinfo+90
VMVAR0	EQU	Xinfo+91
VMVAR1	EQU	Xinfo+92
MAPHDL	equ	Xinfo+93

RETAF	EQU	XINFO+96	;12
DIRSW	EQU	XINFO+108

MAPSL0	EQU	XINFO+109
MAPBK0	EQU	XINFO+110
MAPSZ0	EQU	XINFO+111
MAPSL1	EQU	XINFO+112
MAPBK1	EQU	XINFO+113
MAPSZ1	EQU	XINFO+114

TMPPRM	EQU	XINFO+122	;6

KPRM	EQU	XINFO+128;75(Max80)

NEWPLT	EQU	XINFO+208;32

SVHOOK	EQU	XINFO+240;5
SAVEAD	EQU	XINFO+245;2
TXTPTR	EQU	XINFO+247;2
VAL	EQU	XINFO+249;3
;SEMAPH	EQU	XINFO+252
;	EQU	XINFO+253
;---- Kanji Data
AKSIZE	EQU	KPRM+0	;2 Ank Size
KJSIZE	EQU	KPRM+2	;2 Kanji Size
AKPITC	EQU	KPRM+4	;2 Ank Pitch
KJPITC	EQU	KPRM+6	;2 Kanji Pitch
ITATBL	EQU	KPRM+8	;2 Italic Table
COLTBL	EQU	KPRM+10	;2 Color Table
SWITCH	EQU	KPRM+12	;1 Switch

KPAT0	EQU	KPRM+13
KPAT1	EQU	KPRM+21
KPAT2	EQU	KPRM+29
KPAT3	EQU	KPRM+37
;+0 SWITC0
;+1 OFFSE0
;+3 BOLD0
;+5 COLOR0
;+7 LOGIC0
KBACK	EQU	KPRM+45	;Back Color
FNTSEL	EQU	KPRM+46	;1 FNTDRV Sel.
FNTSIZ	EQU	KPRM+47	;6*3 	  Size
EXTFNT	EQU	KPRM+65	;2 FNTDRV#3 ADR
KJWAIT	EQU	KPRM+67	;1 Wait(1/60s)
HKKPUT	EQU	KPRM+68	;3 C9h,C9h,C9h
KJSE	EQU	KPRM+71	;1 ring SEDRV
PUTCOU	EQU	KPRM+72	;1 Put Counter 表示された文字数(全角=2)
KNJPTR	EQU	KPRM+73	;1 LastPointer 処理された文字数(ESCシーケンス含む)



;Switch b0	
;	b1	
;	b2	
;	b3	Hi-Speed Mode Init. Cansel
;	b4	Horizontal/Vertical
;	b5	ANK/Shift-JIS
;	b6	LetterPut/LinePut
;	b7	Hi-Speed Mode
;
;Switc? b0	Letter Color Back/Fore
;	b1	Letter Color Switch
;	b2	Line Color Back/Fore
;	b3	Line Color Switch
;	b4	Italic
;	b5	
;	b6	
;	b7	Put

;===============================
DMWORK	EQU	7A00H	;1024+512
;-----------------------
xINFO0  EQU     0300H
xINFO1  EQU     4300H
xBGMDR  EQU     0400H
xSEDRV	EQU	2800H
xPCMDR  EQU     2C00H

xFNT16  EQU     7400H
xFNT12  EQU     7600H
xDEVDR  EQU     7800H
