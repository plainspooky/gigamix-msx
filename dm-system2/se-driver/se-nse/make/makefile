#
# makefile for LSI-C86 MAKE.EXE
#
.suffixes : .z80 .rel

.z80.rel :
	xm80 $< -r -m

all :	se-nse.bin

se-nse.bin :	ins-nse.rel nsedrv.inc
	xl80 -p c000 -d c000 $# -n $@ -x -e INST
	bsave se-nse.hex se-nse.bin
	del se-nse.hex

