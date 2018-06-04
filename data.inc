
.CONST

	xlen EQU 1280
	ylen EQU 720
	winMode EQU 0
	bgSpeed EQU 1

	;Window info

	black EQU 0
	white EQU 0FFFFFFFFh

	;colors

	playerW EQU 20
	playerH EQU 160
	xhitbox EQU xlen - playerW
	yhitbox EQU ylen - playerH
	playerMid EQU yhitbox / 2

	;Pong player info
	
	ballBorder EQU 20
	ballMidX EQU (xlen - ballBorder) / 2
	ballMidY EQU (ylen - ballBorder) / 2

	;Pong ball info

	PKEY EQU 50h
	RKEY EQU 52h
	SKEY EQU 53h
	WKEY EQU 57h
	space EQU VK_SPACE
	upArrow EQU VK_UP
	downArrow EQU VK_DOWN

	;Keyboard key constants

.DATA

	hddJeff BYTE "jeff.bmp", 0
	hddBG BYTE "bg2.bmp", 0
	hddPlayer BYTE "pongp.bmp", 0
	hddBall BYTE "ball.bmp", 0

	;Saves locations of images to memory as bytes
	
	blockPlayer BYTE 0, 0

	Keys STRUCT

		Up DWORD ?
		Down DWORD ?

	Keys ENDS

	Character STRUCT

		pos POINT<>

		drc POINT<>

		button Keys<>

		info Img<>

	Character ENDS

	;Struct for characters - kinda like an object

	jeff Character<<0,0>,<0,0>,<upArrow, downArrow>>
	BG1 Character<<0,0>,<bgSpeed,0>,<upArrow, downArrow>>
	BG2 Character<<-xlen,0>,<bgSpeed,0>,<upArrow, downArrow>>
	player1 Character<<playerW * 2, playerMid>,<0,0>,<WKEY, SKEY>>
	player2 Character<<xlen - (playerW * 3), playerMid>,<0,0>,<upArrow, downArrow>>
	ball Character<<ballMidX, ballMidY>,<0,0>,<upArrow, downArrow>>

	;Defining objects for the pictures we need to move