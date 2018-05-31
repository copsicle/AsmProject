
INCLUDE drd.inc

INCLUDELIB drd.lib

;Include the inc and library of drd

INCLUDE data.inc

;Include all the data

.CODE

	startPos PROC

	;Start of set starting positions function
				
		MOV player1.pos.x, playerW * 2

		MOV player1.pos.y, playerMid 
		
		MOV player2.pos.x, xlen - (playerW * 3)

		MOV player2.pos.y, playerMid

		MOV ball.pos.x, ballMidX

		MOV ball.pos.y, ballMidY

		;Starting positions for all images

		RET
	startPos ENDP
	
	init PROC
	
	;Start of initializing function

		INVOKE drd_init, xlen, ylen, winMode

		;Open a new drd window

		INVOKE drd_imageLoadFile, OFFSET hddJeff, OFFSET jeff.info

		INVOKE drd_imageLoadFile, OFFSET hddBG, OFFSET BG1.info

		INVOKE drd_imageLoadFile, OFFSET hddBG, OFFSET BG2.info

		INVOKE drd_imageLoadFile, OFFSET hddPlayer, OFFSET player1.info

		INVOKE drd_imageLoadFile, OFFSET hddPlayer, OFFSET player2.info

		INVOKE drd_imageLoadFile, OFFSET hddBall, OFFSET ball.info

		;Load all the images to memory

		INVOKE drd_imageSetTransparent, OFFSET jeff.info, white

		INVOKE drd_imageSetTransparent, OFFSET ball.info, black

		;Set the background color of pictures to transparent

		MOV BG2.pos.x, -xlen

		;Setup second background picture for scrolling background

		MOV EAX, speed

		MOV EBX, speed

		;Putting initial speed values into registers

		INVOKE startPos

		;Put all characters in starting positions

		RET
	init ENDP

	update PROC
	
	;Start of update function

		PUSHA

		;Push all registers because drd is evil

		INVOKE drd_processMessages

		;Process window interactions

		INVOKE drd_flip

		;Flip the windows buffers

		INVOKE drd_pixelsClear, black

		;Clear back buffer

		;INVOKE Sleep, 20

		;Slow down drawing (this is for fast computers, un/comment this if too slow/fast)

		POPA

		;Pop all registers to prevent drd from being evil
		
		ADD jeff.pos.x, EAX

		ADD jeff.pos.y, EBX

		;Add register values to position of character

		RET
	update ENDP

	draw PROC

	;Start of draw function
		
		PUSHA

		;Keeps my register values from the evil hands of drd

		INVOKE drd_imageDraw, OFFSET BG1.info, BG1.pos.x, BG1.pos.y

		INVOKE drd_imageDraw, OFFSET BG2.info, BG2.pos.x, BG2.pos.y

		INVOKE drd_imageDraw, OFFSET jeff.info, jeff.pos.x, jeff.pos.y

		INVOKE drd_imageDraw, OFFSET ball.info, ball.pos.x, ball.pos.y

		INVOKE drd_imageDraw, OFFSET player1.info, player1.pos.x, player1.pos.y

		INVOKE drd_imageDraw, OFFSET player2.info, player2.pos.x, player2.pos.y

		;Draws all the images using the image info in the struct and the positions
		
		POPA

		;Ha! no register values for you this time drd

		RET
	draw ENDP

	bgcmp PROC

	;Start of background moving and comparing function

		INC BG1.pos.x

		INC BG2.pos.x

		;Increases background X position by one to create scrolling effect

		CMP BG1.pos.x, xlen
		JE bg1mv

		CMP BG2.pos.x, xlen
		JE bg2mv

		;Checks if any of these conditions are met and if so jumps to the correct tag

		RET

		bg1mv:
			MOV BG1.pos.x, -xlen
		RET

		;If the first background exits out of the frame it's moved to the left

		bg2mv:
			MOV BG2.pos.x, -xlen
		RET

		;Same as last one but for the second image

	bgcmp ENDP

	jeffcmp PROC

	;Start of Jeff comparing and moving function
	;I call this one "The Windows XP ScreenSaver"

		CMP jeff.pos.x, xhitbox
		JGE xchange

		CMP jeff.pos.x, 0
		JLE xchange

		;Checks if Jeff touches the top or bottom of the frame

		goback:

			CMP jeff.pos.y, yhitbox
			JGE ychange

			CMP jeff.pos.y, 0
			JLE ychange

			;Same as the X one but this is if Jeff touches the left or right of the frame
		
			RET
		
		xchange:
			
			NEG EAX

		JMP goback

		;Changes direction of X movement on goes back to check Y

		ychange:

			NEG EBX

		;Changes Y and returns back to the function

		RET
	jeffcmp ENDP