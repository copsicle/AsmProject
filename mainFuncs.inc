
INCLUDE drd.inc

INCLUDELIB drd.lib

;Include the inc and library of drd

INCLUDE data.inc

INCLUDE funcs.inc

;Include all the data and other functions

.CODE
	
	init PROC
	
	;Start of initializing function

		INVOKE drd_init, xlen, ylen, winMode

		;Open a new drd window

		INVOKE drd_imageLoadFile, OFFSET hddBG, OFFSET BG1.info

		INVOKE drd_imageLoadFile, OFFSET hddBG, OFFSET BG2.info

		INVOKE drd_imageLoadFile, OFFSET hddPlayer, OFFSET player1.info

		INVOKE drd_imageLoadFile, OFFSET hddPlayer, OFFSET player2.info

		INVOKE drd_imageLoadFile, OFFSET hddBall, OFFSET ball.info

		;Load all the images to memory

		INVOKE drd_imageSetTransparent, OFFSET ball.info, black

		;Set the background color of pictures to transparent

		RET
	init ENDP

	update PROC
	
	;Start of update function

		PUSHA

		;Push all registers because drd is evil

		INVOKE drd_processMessages

		;Process window interactions

		INVOKE drd_pixelsClear, black

		;Clear back buffer

		INVOKE Sleep, 3

		;Slow down drawing (this is for fast computers, un/comment this if too slow/fast)

		POPA

		;Pop all registers to prevent drd from being evil

		INVOKE pauseGame

		INVOKE moveWithKeys, OFFSET player1

		INVOKE moveWithKeys, OFFSET player2

		INVOKE moveObject, OFFSET player1

		INVOKE moveObject, OFFSET player2

		RET
	update ENDP

	draw PROC

	;Start of draw function
		
		PUSHA

		;Keeps my register values from the evil hands of drd

		INVOKE drd_imageDraw, OFFSET BG1.info, BG1.pos.x, BG1.pos.y

		INVOKE drd_imageDraw, OFFSET BG2.info, BG2.pos.x, BG2.pos.y

		INVOKE drd_imageDraw, OFFSET ball.info, ball.pos.x, ball.pos.y

		INVOKE drd_imageDraw, OFFSET player1.info, player1.pos.x, player1.pos.y

		INVOKE drd_imageDraw, OFFSET player2.info, player2.pos.x, player2.pos.y

		;Draws all the images using the image info in the struct and the positions

		INVOKE drd_flip

		;Flip the windows buffers
		
		POPA

		;Ha! no register values for you this time drd

		RET
	draw ENDP