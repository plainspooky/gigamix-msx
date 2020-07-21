#
# makefile for BORLAND MAKE.EXE
#
.suffixes : .z80 .mac .rel
.mac.rel:
	xm80 $< -r -m
.z80.rel:
	xm80 $< -r -m

all :	DEV-WEND.BIN DEV-WEND.DRV

DEV-WEND.BIN :	INS-WEND.REL DEV-WEND.REL
	xl80 -p c000 -d c000 $** -n INSTALL -x -e INSWEND
	bsave INSTALL.HEX DEV-WEND.BIN
	del INSTALL.HEX

DEV-WEND.DRV :	DEV-WEND.REL
	xl80 -p 100 -d 100 $** -n DRIVER -e
	copy DRIVER.COM DEV-WEND.DRV >nul
	del DRIVER.COM

