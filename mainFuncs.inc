
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

		INVOKE drd_imageLoadFile, OFFSET hddScores, OFFSET scoreImgP1.info
		INVOKE drd_imageLoadFile, OFFSET hddScores, OFFSET scoreImgP2.info
		INVOKE drd_imageLoadFile, OFFSET hddScores, OFFSET scoreImgP12.info
		INVOKE drd_imageLoadFile, OFFSET hddScores, OFFSET scoreImgP22.info

		INVOKE drd_imageLoadFile, OFFSET hddWin, OFFSET winMsg.info
		INVOKE drd_imageLoadFile, OFFSET hddLose, OFFSET loseMsg.info
		INVOKE drd_imageLoadFile, OFFSET hddRes, OFFSET resMsg.info

		INVOKE drd_imageLoadFile, OFFSET hddStart, OFFSET menu.info

		;Load all the images into the according characters

		INVOKE drd_imageSetTransparent, OFFSET ball.info, black

		INVOKE drd_imageSetTransparent, OFFSET scoreImgP1.info, black
		INVOKE drd_imageSetTransparent, OFFSET scoreImgP2.info, black
		INVOKE drd_imageSetTransparent, OFFSET scoreImgP12.info, black
		INVOKE drd_imageSetTransparent, OFFSET scoreImgP22.info, black

		INVOKE drd_imageSetTransparent, OFFSET winMsg.info, black
		INVOKE drd_imageSetTransparent, OFFSET loseMsg.info, black
		INVOKE drd_imageSetTransparent, OFFSET resMsg.info, black

		INVOKE drd_imageSetTransparent, OFFSET menu.info, black

		;Set the background color of images to transparent

		INVOKE gameMenu

		;Handle main menu

		INVOKE PlaySound, OFFSET hddMusic, NULL, SND_ASYNC OR SND_LOOP

		;Start music and game

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
		INVOKE restartGame, OFFSET scoreImgP1, OFFSET scoreImgP2, OFFSET scoreImgP12, OFFSET scoreImgP22

		;Game handling

		CMP restarted, 1
		JE fix
		JMP dontFix
		fix:
			DEC restarted
		dontFix:

		;Checks if the restarted "boolean" was flipped not in endGame and resets it

		INVOKE moveWithKeys, OFFSET player1
		INVOKE moveWithKeys, OFFSET player2

		;Handle key presses for the players

		INVOKE playerBorder, OFFSET player1
		INVOKE playerBorder, OFFSET player2

		;Manage borders for the players

		INVOKE moveObject, OFFSET player1
		INVOKE moveObject, OFFSET player2

		INVOKE moveObject, OFFSET ball

		INVOKE moveObject, OFFSET BG1
		INVOKE moveObject, OFFSET BG2

		;Move all the game objects and background

		INVOKE stopMovement, OFFSET player1
		INVOKE stopMovement, OFFSET player2

		;Stop moving players (until next loop)

		INVOKE bgcmp, OFFSET BG1, OFFSET ball
		INVOKE bgcmp, OFFSET BG2, OFFSET ball

		;Scroll the background

		INVOKE ballHitting, OFFSET player1, OFFSET ball
		INVOKE ballHitting, OFFSET player2, OFFSET ball

		INVOKE ballToWall, OFFSET ball

		;Handle ball "physics"

		INVOKE endGame

		;Handle end game event

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

		INVOKE drd_imageDrawCrop, OFFSET scoreImgP1.info, scoreImgP1.pos.x, scoreImgP1.pos.y, scoreImgP1.src.x, scoreImgP1.src.y, scoreImgP1.srcend.x, scoreImgP1.srcend.y
		INVOKE drd_imageDrawCrop, OFFSET scoreImgP2.info, scoreImgP2.pos.x, scoreImgP2.pos.y, scoreImgP2.src.x, scoreImgP2.src.y, scoreImgP2.srcend.x, scoreImgP2.srcend.y
		INVOKE drd_imageDrawCrop, OFFSET scoreImgP12.info, scoreImgP12.pos.x, scoreImgP12.pos.y, scoreImgP12.src.x, scoreImgP12.src.y, scoreImgP12.srcend.x, scoreImgP12.srcend.y
		INVOKE drd_imageDrawCrop, OFFSET scoreImgP22.info, scoreImgP22.pos.x, scoreImgP22.pos.y, scoreImgP22.src.x, scoreImgP22.src.y, scoreImgP22.srcend.x, scoreImgP22.srcend.y

		;Draws all the images using the image info in the struct and the positions

		INVOKE drd_flip

		;Flip the window buffers
		
		POPA

		;Ha! no register values for you this time drd

		RET
	draw ENDP