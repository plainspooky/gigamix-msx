; DMsystem2 global driver header file

EOF		equ	1Ah

DRIVER_ID_FONT	equ	00h
DRIVER_ID_PCM	equ	01h
DRIVER_ID_DEV	equ	02h
DRIVER_ID_BGM	equ	03h
DRIVER_ID_SE	equ	04h

FONT_TYPE_16	equ	01h
FONT_TYPE_12	equ	02h
FONT_TYPE_EX	equ	03h

ADDR_FONT16	equ	7400h
ADDR_FONT12	equ	7600h
ADDR_PCM	equ	2C00h
ADDR_BGM	equ	0400h
ADDR_SE		equ	2800h

