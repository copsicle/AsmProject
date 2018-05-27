
.CONST

	xlen EQU 1280
	ylen EQU 720
	winMode EQU 0

	;Window info

	black EQU 0
	white EQU 0FFFFFFFFh

	;colors
	
	jeffBorder EQU 320
	speed EQU 1

	;Jeff constants

	xhitbox EQU xlen - jeffBorder
	yhitbox EQU ylen - jeffBorder

	;Hitboxes for collisions
	
.DATA

	hddJeff BYTE "jeff.bmp", 0
	hddBG BYTE "bg.bmp", 0

	;Saves locations of images to memory as bytes

	character STRUCT

		info Img<>

		pos POINT<>

	character ENDS

	;Struct for characters - kinda like an object

	jeff character<>
	BG1 character<>
	BG2 character<>

	;Defining objects for the pictures we need to move