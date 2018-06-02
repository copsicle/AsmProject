
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