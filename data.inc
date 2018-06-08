
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
	ballSpeed EQU 2

	;Pong ball info

	PKEY EQU 50h
	RKEY EQU 52h
	SKEY EQU 53h
	WKEY EQU 57h
	space EQU VK_SPACE
	upArrow EQU VK_UP
	downArrow EQU VK_DOWN
	escape EQU VK_ESCAPE

	;Keyboard key constants

	endScore EQU 10
	scoreBorder EQU 50
	spacing EQU 10
	p1ScorePos EQU ((xlen / 2) - (scoreBorder * 3))
	p1ScorePos2 EQU ((xlen / 2) - (scoreBorder * 4) - spacing)
	p2ScorePos EQU ((xlen / 2) + (scoreBorder * 3) + spacing)
	p2ScorePos2 EQU ((xlen / 2) + (scoreBorder * 2))

	msgBorderX EQU 220
	msgBorderY EQU 46
	resBorderX EQU 403
	resBorderY EQU 34
	startBorderX EQU 500
	startBorderY EQU 400

	startX EQU ((xlen - startBorderX) / 2)
	startY EQU ((ylen - startBorderY) / 2)
	restX EQU ((xlen - resBorderX) / 2)
	restY EQU ((ylen - resBorderY) / 2)
	p2Msg EQU (xlen - msgBorderX)

.DATA

	hddBG BYTE "bg3.bmp", 0
	hddPlayer BYTE "pongp.bmp", 0
	hddBall BYTE "ball.bmp", 0
	hddScores BYTE "score.bmp", 0
	hddWin BYTE "winmsg.bmp", 0
	hddLose BYTE "losemsg.bmp", 0
	hddRes BYTE "resmsg.bmp", 0
	hddStart BYTE "start.bmp", 0

	;Saves locations of images to memory as bytes

	hddMusic BYTE "music.wav", 0
	hddStart2 BYTE "start.wav", 0
	hddP1 BYTE "p1hit.wav", 0
	hddP2 BYTE "p2hit.wav", 0
	
	p1Score DWORD 0, 0
	p2Score DWORD 0, 0
	pScored BYTE 1, 0
	endTheGame BYTE 0, 0
	restarted BYTE 0, 0

	Keys STRUCT

		Up DWORD ?
		Down DWORD ?

	Keys ENDS

	Character STRUCT

		pos POINT<>;0->4 x 4->8 y

		drc POINT<>;8->12 x 12->16 y

		button Keys<>;16->20 upKey 20->24 downKey

		info Img<>;24->44 image

		src POINT<>;64->68 x 68->72 y

		srcend POINT<>;72->76x 76->80 y

	Character ENDS

	;Struct for characters - kinda like an object

	menu Character<<startX, startY>,<>,<>,<>,<>,<>>
	resMsg Character<<restX, restY>,<>,<>,<>,<>,<>>

	BG1 Character<<(xlen / 2), 0>,<0,0>,<upArrow, downArrow>,<>,<>,<>>
	BG2 Character<<(-xlen / 2), 0>,<0,0>,<upArrow, downArrow>,<>,<>,<>>

	player1 Character<<playerW * 2, playerMid>,<0,0>,<WKEY, SKEY>,<>,<>,<>>
	player2 Character<<xlen - (playerW * 3), playerMid>,<0,0>,<upArrow, downArrow>,<>,<>,<>>

	ball Character<<ballMidX, ballMidY>,<ballSpeed, ballSpeed>,<>,<>,<>,<>>

	scoreImgP1 Character<<p1ScorePos, 0>,<0,0>,<>,<>,<0,0>,<scoreBorder, scoreBorder>>
	scoreImgP2 Character<<p2ScorePos, 0>,<0,0>,<>,<>,<0,0>,<scoreBorder, scoreBorder>>
	scoreImgP12 Character<<p1ScorePos2, 0>,<0,0>,<>,<>,<0,0>,<scoreBorder, scoreBorder>>
	scoreImgP22 Character<<p2ScorePos2, 0>,<0,0>,<>,<>,<0,0>,<scoreBorder, scoreBorder>>

	winMsg Character<<>,<>,<>,<>,<>,<>>
	loseMsg Character<<>,<>,<>,<>,<>,<>>

	;Defining objects for the pictures we need to move