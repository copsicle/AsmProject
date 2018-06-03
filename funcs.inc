
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

	pauseGame PROC

	;Start of game pausing function

		PUSHA

		INVOKE GetAsyncKeyState, PKEY
		CMP AX, 0
		JNE doIt
		
		;Jump to doIt if the P key is pressed

		JMP skipTimeout

		;Jump to skipTimeout if we don't want to pause the game

		doIt:
		
		INVOKE Sleep, 500

		;Timeout for the user to release the key

		POPA

		;Making sure any registers don't get bamboozled in the process

		check:

		PUSHA
		
		INVOKE drd_processMessages

		;Mkae sure we get key inputs
		
		INVOKE GetAsyncKeyState, PKEY
		CMP AX, 0
		JNE unPauseGame

		;Unpause the game if p is pressed again
		
		POPA
		
		JMP check

		unPauseGame:
		
		INVOKE Sleep,500

		;Unpressing timeout
		
		skipTimeout:

		;Skip the unpressing timeout if we didn't pause the game
		
		POPA

		;If it's quirky but it works clap your hands

		RET
	pauseGame ENDP

	moveObject PROC adrObj:DWORD

		PUSHA

		MOV ECX, adrObj

		;Put the object address in a register

		MOV EDX, [ECX + 8]

		;Character object layout 1. pos -> 2 DWORDS for x and y(8 bytes)
		;2. drc -> same as pos (starting in byte 8 after initial object address)
		;3. Keys -> 2 DWORDS for the keys for moving up and down (starting in byte 16 after initial object address)
		;4. info -> the image of the character (starting in byte 24 after initial object address)

		ADD [ECX], EDX

		MOV EDX, [ECX + 12]

		ADD [ECX + 4], EDX

		POPA

		RET
	moveObject ENDP

	moveWithKeys PROC adrObj:DWORD

		PUSHA

		MOV ECX, adrObj

		MOV EDX, [ECX + 16]

		INVOKE GetAsyncKeyState, EDX
		CMP AX, 0
		JNE goUp

		MOV ECX, adrObj

		MOV EDX, [ECX + 20]

		INVOKE GetAsyncKeyState, EDX
		CMP AX, 0
		JNE goDown

		jmp endIt

		goUp:

			MOV EAX, -1
			
			MOV ECX, adrObj

			MOV [ECX + 12], EAX

		JMP endIt

		goDown:

			MOV EAX, 1

			MOV ECX, adrObj    

			MOV [ECX + 12], EAX
		
		endIt:

		POPA

		RET
	moveWithKeys ENDP