#
# makefile for LSI-C86 MAKE.EXE
#
.suffixes : .z80 .rel

.z80.rel :
	xm80 $< -r -m

all :	fnt-rfil.drv src-rfil.bin fnt-rfil.bin

fnt-rfil.drv :	fnt-rfil.rel
	xl80 -p 100 -d 300 $# -n $@ -e
	copy fnt-rfil.com fnt-rfil.drv >nul
	del fnt-rfil.com

src-rfil.bin :	src-rfil.rel
	xl80 -p c000 -d c000 $# -n $@ -x -e SRCHRF
	bsave src-rfil.hex src-rfil.bin
	del src-rfil.hex

fnt-rfil.bin :	fnt-rfil.rel ins-rfil.rel src-rfil.rel
	xl80 -p c000 -d c000 $# -n $@ -x -e INSTRF
	bsave fnt-rfil.hex fnt-rfil.bin
	del fnt-rfil.hex

