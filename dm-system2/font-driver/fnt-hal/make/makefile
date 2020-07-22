#
# makefile for LSI-C86 MAKE.EXE
#
.suffixes : .z80 .rel

.z80.rel :
	xm80 $< -r -m

all :	fnt-hal.drv srch-hal.bin inst-hal.bin

fnt-hal.drv :	fnt-hal.rel
	xl80 -p 100 -d 300 $# -n $@ -e
	copy fnt-hal.com fnt-hal.drv >nul
	del fnt-hal.com

srch-hal.bin :	srch-hal.rel
	xl80 -p c000 -d c000 $# -n $@ -x -e SRCHHA
	bsave srch-hal.hex srch-hal.bin
	del srch-hal.hex

fnt-hal.bin :	fnt-hal.rel inst-hal.rel srch-hal.rel
	xl80 -p c000 -d c000 $# -n $@ -x -e INSTHA
	bsave fnt-hal.hex fnt-hal.bin
	del fnt-hal.hex

