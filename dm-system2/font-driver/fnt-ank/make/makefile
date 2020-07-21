#
# makefile for LSI-C86 MAKE.EXE
#
.suffixes : .z80 .rel

.z80.rel :
	xm80 $< -r -m

all :	fnt-ank.drv inst-ank.bin

fnt-ank.drv :	fnt-ank.rel
	xl80 -p 100 -d 300 $# -n $@ -e
	copy fnt-ank.com fnt-ank.drv >nul
	del fnt-ank.com

fnt-ank.bin :	fnt-ank.rel inst-ank.rel
	xl80 -p c000 -d c000 $# -n $@ -x -e INSTAN
	bsave fnt-ank.hex fnt-ank.bin
	del fnt-ank.hex

