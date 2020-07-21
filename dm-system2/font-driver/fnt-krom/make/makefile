#
# makefile for LSI-C86 MAKE.EXE
#
.suffixes : .z80 .rel

.z80.rel :
	xm80 $< -r -m

all :	fnt-krom.drv src-krom.bin ins-krom.bin

fnt-krom.drv :	fnt-krom.rel
	xl80 -p 100 -d 300 $# -n $@ -e
	copy fnt-krom.com fnt-krom.drv >nul
	del fnt-krom.com

src-krom.bin :	src-krom.rel
	xl80 -p c000 -d c000 $# -n $@ -x -e SRCHKR
	bsave src-krom.hex src-krom.bin
	del src-krom.hex

fnt-krom.bin :	fnt-krom.rel ins-krom.rel src-krom.rel
	xl80 -p c000 -d c000 $# -n $@ -x -e INSTKR
	bsave fnt-krom.hex fnt-krom.bin
	del fnt-krom.hex

