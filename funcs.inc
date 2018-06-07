
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

	bgcmp PROC adrObj:DWORD, ballObj:DWORD

	;Start of background comparing function

		PUSHA

		MOV EAX, adrObj

		MOV ECX, ballObj

		MOV ECX, [ECX + 8]

		MOV [EAX + 8], ECX

		MOV EBX, xlen

		CMP [EAX], EBX
		JE bgmv

		NEG EBX
		
		CMP [EAX], EBX
		JE bgmv

		POPA

		RET

		bgmv:
			NEG EBX
			MOV [EAX], EBX
			POPA
		RET
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
		
		INVOKE Sleep, 100

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

	stopMovement PROC adrObj:DWORD
		
		PUSHA

		MOV ECX, adrObj

		MOV EDX, 0

		MOV [ECX + 12], EDX

		POPA

		RET
	stopMovement ENDP

	playerBorder PROC adrObj:DWORD

		PUSHA

		MOV ECX, adrObj

		MOV EDX, 0

		MOV EAX, yhitbox

		CMP [ECX + 4], EDX
		JE xdontMove

		CMP [ECX + 4], EAX
		JE ydontMove

		JMP theEnd

		xdontMove:

			INVOKE GetAsyncKeyState, [ECX + 16]
			CMP AX, 0
			JE theEnd

		JMP change

		ydontMove:

			INVOKE GetAsyncKeyState, [ECX + 20]
			CMP AX, 0
			JE theEnd

		change:
			
			MOV EDX, 0

			MOV ECX, adrObj

			MOV [ECX + 12], EDX
			
		theEnd:

		POPA

		RET
	playerBorder ENDP

	ballHitting PROC playerObj:DWORD, ballObj:DWORD
		PUSHA
		MOV EAX, playerObj
		MOV EBX, ballObj
		MOV ECX, [EAX]
		ADD ECX, playerW
		CMP [EBX], ECX
		JE p1col
		MOV EDX, [EBX]
		ADD EDX, ballBorder
		CMP [EAX],EDX
		JE p2col
		JMP endIt
		p1col:
			MOV ECX, [EAX + 4]
			SUB ECX, (ballBorder / 3)
			CMP [EBX + 4],ECX
			JGE y1isgood
			JMP endIt
			y1isgood:
				MOV EDX, [EAX + 4]
				ADD EDX, (playerH + (ballBorder / 3))
				CMP [EBX + 4], EDX
				JLE p1finalSolution
				JMP endIt
		p2col:
			MOV ECX, [EAX + 4]
			SUB ECX, (ballBorder / 3)
			CMP [EBX + 4], ECX
			JGE y2isgood
			JMP endIt
			y2isgood:
				MOV EDX, [EAX + 4]
				ADD EDX, playerH
				ADD EDX, (ballBorder / 3)
				CMP [EBX + 4], EDX
				JLE p2finalSolution
				JMP endIt
		p1finalSolution:
			MOV EDX, 0
			CMP [EBX + 8], EDX
			JG endIt
			MOV ECX, [EBX + 8]
			NEG ECX
			MOV [EBX + 8], ECX
			JMP endIt
		p2finalSolution:
			MOV EDX, 0
			CMP [EBX + 8], EDX
			JL endIt
			MOV ECX, [EBX + 8]
			NEG ECX
			MOV [EBX + 8], ECX
		endIt:
		POPA
		RET
	ballHitting ENDP

	ballToWall PROC adrObj:DWORD

		PUSHA
		MOV EAX, adrObj
		MOV EDX, 0
		CMP [EAX + 4], EDX
		JE hitwall
		MOV EBX, ylen
		SUB EBX, ballBorder
		CMP [EAX + 4], EBX
		JE hitwall
		JMP goAway
		hitwall:
			MOV ECX, [EAX + 12]
			NEG ECX
			MOV [EAX + 12], ECX
		goAway:
		POPA

		RET
	ballToWall ENDP

	scoring PROC ballObj:DWORD, p1Obj:DWORD, p2Obj:DWORD, p1Obj2:DWORD, p2Obj2:DWORD

		PUSHA
		MOV EAX, ballObj
		MOV EBX, 0
		MOV ECX, xlen
		SUB ECX, ballBorder
		CMP [EAX], ECX
		JE scoreP1
		CMP [EAX], EBX
		JE scoreP2
		JMP plsGo
		scoreP1:
			INC p1Score
			INC pScored
			INVOKE startPos
			MOV ECX, p1Obj
			MOV EAX, p1Score
			MOV EBX, 10
			MOV EDX, 0
			DIV EBX
			CMP EDX, 0
			JE addTenP1
			MOV EDX, scoreBorder
			ADD [ECX + 44], EDX
			JMP plsGo
		scoreP2:
			INC p2Score
			INC pScored
			INVOKE startPos
			MOV ECX, p2Obj
			MOV EAX, p2Score
			MOV EBX, 10
			MOV EDX, 0
			DIV EBX
			CMP EDX, 0
			JE addTenP2
			MOV EDX, scoreBorder
			ADD [ECX + 44], EDX
			JMP plsGo
		addTenP1:
			MOV EAX, p1Obj2
			MOV EBX, scoreBorder
			MOV EDX, 0
			MOV [ECX + 44], EDX
			ADD [EAX + 44], EBX
			JMP plsGo
		addTenP2:
			MOV EAX, p2Obj2
			MOV EBX, scoreBorder
			MOV EDX, 0
			MOV [ECX + 44], EDX
			ADD [EAX + 44], EBX
		plsGo:
		POPA
		RET
	scoring ENDP

	endGame PROC
		PUSHA
		CMP p1Score, endScore
		JE endIt
		CMP p2Score, endScore
		JE endIt
		INVOKE GetAsyncKeyState, escape
		CMP AX, 0
		JNE endIt
		POPA
		RET
		endIt:
			INC endTheGame
			POPA
		RET
	endGame ENDP

	restartGame PROC p1:DWORD, p2:DWORD
		PUSHA
		INVOKE GetAsyncKeyState, RKEY
		CMP AX, 0
		JNE ree
		JMP goNow
		ree:
			INC pScored
			MOV p1Score, 0
			MOV p2Score, 0
			MOV EAX, p1
			MOV EBX, p2
			MOV ECX, 0
			MOV [EAX + 44], ECX
			MOV [EBX + 44], ECX
			INVOKE startPos
		goNow:
		POPA
		RET
	restartGame ENDP