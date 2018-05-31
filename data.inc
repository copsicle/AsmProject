
.CONST

	xlen EQU 1280
	ylen EQU 720
	winMode EQU 0

	;Window info

	black EQU 0
	white EQU 0FFFFFFFFh

	;colors
	
	jeffBorder EQU 300
	speed EQU 1

	;Jeff constants

	xhitbox EQU xlen - jeffBorder
	yhitbox EQU ylen - jeffBorder

	;Hitboxes for collisions

	playerW EQU 20
	playerH EQU 160
	playerMid EQU (ylen - playerH) / 2
	
	ballBorder EQU 20
	ballMidX EQU (xlen - ballBorder) / 2
	ballMidY EQU (ylen - ballBorder) / 2

.DATA

	hddJeff BYTE "jeff.bmp", 0
	hddBG BYTE "bg.bmp", 0
	hddPlayer BYTE "pongp.bmp", 0
	hddBall BYTE "ball.bmp", 0

	;Saves locations of images to memory as bytes

	Rev STRUCT
		
	Rev ENDS

	Character STRUCT

		info Img<>

		pos POINT<>

		drc POINT<>

	Character ENDS

	;Struct for characters - kinda like an object

	jeff Character<>
	BG1 Character<>
	BG2 Character<>
	player1 Character<>
	player2 Character<>
	ball Character<>

	;Defining objects for the pictures we need to move