
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

	PKEY EQU 50
	RKEY EQU 52
	SKEY EQU 53
	WKEY EQU 57
	space EQU VK_SPACE
	upArrow EQU VK_UP
	downArrow EQU VK_DOWN
	keypress EQU 1000h

.DATA

	hddJeff BYTE "jeff.bmp", 0
	hddBG BYTE "bg2.bmp", 0
	hddPlayer BYTE "pongp.bmp", 0
	hddBall BYTE "ball.bmp", 0

	;Saves locations of images to memory as bytes

	Keys STRUCT

		Up DWORD ?
		Down DWORD ?
		KeyW DWORD ?
		KeyS DWORD ?
		Space DWORD ?

	Keys ENDS

	Character STRUCT

		pos POINT<>

		drc POINT<>

		button Keys<>

		info Img<>

	Character ENDS

	;Struct for characters - kinda like an object

	jeff Character<<0,0>,<0,0>,<upArrow, downArrow, WKEY, SKEY, space>>
	BG1 Character<<0,0>,<0,0>,<upArrow, downArrow, WKEY, SKEY, space>>
	BG2 Character<<-xlen,0>,<0,0>,<upArrow, downArrow, WKEY, SKEY, space>>
	player1 Character<<playerW * 2, playerMid>,<0,0>,<upArrow, downArrow, WKEY, SKEY, space>>
	player2 Character<<xlen - (playerW * 3), playerMid>,<0,0>,<upArrow, downArrow, WKEY, SKEY, space>>
	ball Character<<ballMidX, ballMidY>,<0,0>,<upArrow, downArrow, WKEY, SKEY, space>>

	;Defining objects for the pictures we need to move