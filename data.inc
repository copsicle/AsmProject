
.CONST

	

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