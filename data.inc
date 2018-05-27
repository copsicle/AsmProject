
.CONST

	xlen EQU 1280
	ylen EQU 720
	winMode EQU 0

	black EQU 0
	white EQU 0FFFFFFFFh
	
	jeffBorder EQU 320
	speed EQU 1

	xhitbox EQU xlen - jeffBorder
	yhitbox EQU ylen - jeffBorder

.DATA

	hddJeff BYTE "jeff.bmp", 0
	hddBG BYTE "bg.bmp", 0

	character STRUCT

		info Img<>

		pos POINT<>

	character ENDS

	jeff character<>
	BG1 character<>
	BG2 character<>