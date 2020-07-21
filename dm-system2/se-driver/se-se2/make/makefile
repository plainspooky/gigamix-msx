# makefile for LSI-C86 MAKE.EXE
.suffixes : .z80 .rel

.z80.rel :
	xm80 $< -r -m

all :	se-se2.bin sample.se

se-se2.bin :	ins-se2.rel se-se2.rel
	xl80 -p c000 -d c000 $# -n $@ -x -e INST
	bsave se-se2.hex se-se2.bin

sample.se :	sample.z80
	xm80 $< -r -m
	xl80 -p c000 -d c000 $# -n $@ -x -e
	bsave sample.hex sample.se

# for GNU make
archive:
	lha a se-se2.lzh se-se2.bin sample.se se-se2.z80 ins-se2.z80 sample.z80 drivers.h ds2entry.h ds2se2.txt makefile

clean :
	del se-se2.bin
	del se-se2.hex
	del *.rel

#ins-se2.rel:	ins-se2.z80
#	xm80 $< -r -m

#stdse2.rel:	stdse2.z80
#	xm80 $< -r -m
