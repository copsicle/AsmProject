
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

	gameMenu PROC

	;Start of main menu function

		loopb:

			PUSHA

			INVOKE drd_processMessages
			INVOKE drd_imageDraw, OFFSET BG1.info, BG1.pos.x, BG1.pos.y
			INVOKE drd_imageDraw, OFFSET BG2.info, BG2.pos.x, BG2.pos.y
			INVOKE drd_imageDraw, OFFSET menu.info, menu.pos.x, menu.pos.y
			INVOKE drd_flip

			;Draw the main menu

			INVOKE GetAsyncKeyState, space
			CMP AX, 0
			JNE startGame

			;Check if space is entered
			
			POPA
			
			JMP loopb
			
			startGame:

			;Exits the function and starts the game
			
			POPA
		
		RET
	gameMenu ENDP

	bgcmp PROC adrObj:DWORD, ballObj:DWORD

	;Start of background comparing function

		PUSHA

		MOV EAX, adrObj
		MOV ECX, ballObj

		;Move addresses of the objects into registers

		MOV ECX, [ECX + 8]
		MOV [EAX + 8], ECX
		
		;Put the X direction of the ball in the background object
		
		MOV EBX, xlen

		;Put the length of the window in a register

		CMP [EAX], EBX
		JE bgmv

		NEG EBX
		
		CMP [EAX], EBX
		JE bgmv

		;Check if the background object fully went out of the windows in either sides

		POPA

		RET

		bgmv:

			NEG EBX
			MOV [EAX], EBX

			;Put the background object on the opposite side of the window for scrolling effect

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
		
		INVOKE Sleep, 200

		;Timeout for the user to release the key

		POPA

		;Making sure any registers don't get bamboozled in the process

		check:

		PUSHA
		
		INVOKE drd_processMessages

		;Make sure we get key inputs
		
		INVOKE GetAsyncKeyState, PKEY
		CMP AX, 0
		JNE unPauseGame

		;Unpause the game if p is pressed again
		
		POPA
		
		JMP check

		unPauseGame:
		
		INVOKE Sleep, 200

		;Unpressing timeout
		
		skipTimeout:

		;Skip the unpressing timeout if we didn't pause the game
		
		POPA

		;If it's quirky but it works clap your hands

		RET
	pauseGame ENDP

	moveObject PROC adrObj:DWORD
	
	;Start of moving objects function

		PUSHA

		MOV ECX, adrObj

		;Put the object address in a register

		MOV EDX, [ECX + 8]
		ADD [ECX], EDX

		MOV EDX, [ECX + 12]
		ADD [ECX + 4], EDX

		;Take X direction and Y direction of the object and add them to the according position

		POPA

		RET
	moveObject ENDP

	moveWithKeys PROC adrObj:DWORD

	;Start of moving an object with user input function

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

		;Put upward and downward moving keys of the object in a register and check if they are pressed

		jmp endIt

		goUp:

			MOV EAX, -1
			MOV ECX, adrObj
			MOV [ECX + 12], EAX

			;Put -1 in the Y direction of the object so it will go upwards

		JMP endIt

		goDown:

			MOV EAX, 1
			MOV ECX, adrObj    
			MOV [ECX + 12], EAX

			;Put -1 in the Y direction of the object so it will go upwards
		
		endIt:

		POPA

		RET
	moveWithKeys ENDP

	stopMovement PROC adrObj:DWORD

	;Start of stopping movement function
		
		PUSHA

		MOV ECX, adrObj

		MOV EDX, 0
		MOV [ECX + 12], EDX

		;Reset the Y direction of the object so that it won't keep moving after a movement key is unpressed

		POPA

		RET
	stopMovement ENDP

	playerBorder PROC adrObj:DWORD

	;Start of limiting the player within the window function

		PUSHA

		MOV ECX, adrObj

		MOV EDX, 0
		MOV EAX, yhitbox

		;Put the edges of the window into registers

		CMP [ECX + 4], EDX
		JE xdontMove

		CMP [ECX + 4], EAX
		JE ydontMove

		;Check if the player is hitting the border of the window

		JMP theEnd

		xdontMove:

			INVOKE GetAsyncKeyState, [ECX + 16]
			CMP AX, 0
			JE theEnd

			;Check if the player is still pressing the button to move in the direction of the same edge

		JMP change

		ydontMove:

			INVOKE GetAsyncKeyState, [ECX + 20]
			CMP AX, 0
			JE theEnd

			;Same as xdontMove but on the other edge

		change:
			
			MOV EDX, 0
			MOV ECX, adrObj
			MOV [ECX + 12], EDX

			;Change the players direction to 0 so he can't keep moving in the same direction
			
		theEnd:

		POPA

		RET
	playerBorder ENDP

	ballHitting PROC playerObj:DWORD, ballObj:DWORD

	;Start of ball collision with players function

		PUSHA

		MOV EAX, playerObj
		MOV EBX, ballObj

		MOV ECX, [EAX]
		ADD ECX, playerW

		;Take X position of the player and add the width of the player image
		
		CMP [EBX], ECX
		JE p1col

		;check if the X positions of the ball and player collide

		MOV EDX, [EBX]
		ADD EDX, ballBorder

		;Same as second to last comment but with the ball object

		CMP [EAX],EDX
		JE p2col

		;Same as the last compare but for the other player

		JMP endIt
		
		p1col:
			
			MOV ECX, [EAX + 4]
			SUB ECX, (ballBorder / 3)

			;Take Y position of the player and subtract a bit of the balls height for expanding the hitbox a bit 
			
			CMP [EBX + 4],ECX
			JGE y1isgood

			;Check if the balls Y is bigger than the player Y
			
			JMP endIt
			
			y1isgood:
				
				MOV EDX, [EAX + 4]
				ADD EDX, (playerH + (ballBorder / 3))

				;Take player Y and add to it the height of the player image plus the hitbox breathing room
				
				CMP [EBX + 4], EDX
				JLE p1finalSolution

				;Check if the balls Y is smaller than the image of the player (plus the breathing room for the hitbox)
				
				JMP endIt
		
		p2col:

		;All of this is pretty much the same as p1col but for the other side of the player
			
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

			;Check if the X direction of the ball is different than thee side of the player we want to collide with
			
			MOV ECX, [EBX + 8]
			NEG ECX
			MOV [EBX + 8], ECX

			;Negate the X direction of the ball
			
			JMP endIt
		
		p2finalSolution:

		;Same as p1finalSolution but for the other side
			
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

		;Start of ball collision with the celing and floor function

		PUSHA

		MOV EAX, adrObj
		
		MOV EDX, 0
		
		CMP [EAX + 4], EDX
		JE hitWall

		;Check if the ball hit the upper edge of the window
		
		MOV EBX, ylen
		SUB EBX, ballBorder

		;Take the length of the window and subtract the length of the ball image
		
		CMP [EAX + 4], EBX
		JE hitWall

		;Check if the ball hit the downward edge of the window
		
		JMP goAway
		
		hitWall:
			
			MOV ECX, [EAX + 12]
			NEG ECX
			MOV [EAX + 12], ECX

			;Negate the Y direction of the ball
		
		goAway:
		
		POPA

		RET
	ballToWall ENDP

	scoring PROC ballObj:DWORD, p1Obj:DWORD, p2Obj:DWORD, p1Obj2:DWORD, p2Obj2:DWORD

	;Start of score taking function

		PUSHA

		MOV EAX, ballObj
		
		MOV EDX, 0
		MOV EBX, 10
		MOV ECX, xlen
		SUB ECX, ballBorder
		
		CMP [EAX], ECX
		JE scoreP1
		
		CMP [EAX], EDX
		JE scoreP2

		;Check if the ball hit either the right or the left edge of the screen
		
		JMP plsGo
		
		scoreP1:

			INC p1Score
			INC pScored

			;Increase the score of player 1 and pScored for timeout
			
			INVOKE startPos

			;Reset game objects
			
			MOV ECX, p1Obj
			MOV EAX, p1Score
			
			DIV EBX

			;Divide the score by 10
			
			CMP EDX, 0
			JE addTenP1

			;Check if modulo 10 of the score is 0
			
			MOV EDX, scoreBorder
			ADD [ECX + 44], EDX

			;Move one number forward in the sprite sheet for the score
			
			JMP plsGo
		
		scoreP2:

		;Same as scoreP1 but for the score of the other player
			
			INC p2Score
			INC pScored
			
			INVOKE startPos
			
			MOV ECX, p2Obj
			MOV EAX, p2Score
			
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

			;Move forward in the sprite sheet for the second digit in the score and reset the first digit
			
			JMP plsGo
		
		addTenP2:

		;Same as addTenP1 but for the score of the other player
			
			MOV EAX, p2Obj2
			MOV EBX, scoreBorder
			MOV EDX, 0
			MOV [ECX + 44], EDX
			ADD [EAX + 44], EBX
		
		plsGo:
		
		POPA
		
		RET
	scoring ENDP

	restartGame PROC p1:DWORD, p2:DWORD, p12:DWORD, p22:DWORD
	
	;Start of restart game function

		PUSHA
		
		INVOKE GetAsyncKeyState, RKEY
		CMP AX, 0
		JNE ree

		;Check if the R key is pressed
		
		JMP goNow
		
		ree:

			INC pScored

			;Puts a timeout after the restart
			
			MOV p1Score, 0
			MOV p2Score, 0

			;Reset player scores
			
			MOV EAX, p1
			MOV EBX, p2
			
			MOV ECX, 0
			MOV [EAX + 44], ECX
			MOV [EBX + 44], ECX
			
			MOV EAX, p12
			MOV EBX, p22
			
			MOV [EAX + 44], ECX
			MOV [EBX + 44], ECX

			;Reset all score images to 0
			
			INVOKE startPos

			;Put all players back in their starting positions
			
			INC restarted

			;Increments restarted for letting the endGame function (below) know the game restarted
		
		goNow:
		
		POPA
		
		RET
	restartGame ENDP

	endGame PROC

	;Start of end game function

		PUSHA
		
		CMP p1Score, endScore
		JE p1wins
		
		CMP p2Score, endScore
		JE p2wins

		;Check if either player 1 or 2 achieved the winning score
		
		INVOKE GetAsyncKeyState, escape
		CMP AX, 0
		JNE endIt

		;Checks if the escape key is pressed
		
		POPA
		
		RET
		
		p1wins:
			
			MOV EAX, 0
			MOV EBX, p2Msg
			
			INVOKE drd_imageDraw, OFFSET BG1.info, BG1.pos.x, BG1.pos.y
			INVOKE drd_imageDraw, OFFSET BG2.info, BG2.pos.x, BG2.pos.y
			INVOKE drd_imageDraw, OFFSET winMsg.info, EAX, EAX
			INVOKE drd_imageDraw, OFFSET loseMsg.info, EBX, EAX
			INVOKE drd_imageDraw, OFFSET resMsg.info, resMsg.pos.x, resMsg.pos.y
			INVOKE drd_flip

			;Draws end screen for when player 1 wins
			
			JMP loopc
		
		p2wins:
			
			MOV EAX, 0
			MOV EBX, p2Msg
			
			INVOKE drd_imageDraw, OFFSET BG1.info, BG1.pos.x, BG1.pos.y
			INVOKE drd_imageDraw, OFFSET BG2.info, BG2.pos.x, BG2.pos.y
			INVOKE drd_imageDraw, OFFSET winMsg.info, EBX, EAX
			INVOKE drd_imageDraw, OFFSET loseMsg.info, EAX, EAX
			INVOKE drd_imageDraw, OFFSET resMsg.info, resMsg.pos.x, resMsg.pos.y
			INVOKE drd_flip
		
			;Draws end screen for when player 2 wins

		loopc:
			
			INVOKE drd_processMessages
			INVOKE restartGame, OFFSET scoreImgP1, OFFSET scoreImgP2, OFFSET scoreImgP12, OFFSET scoreImgP22
			
			CMP restarted, 1
			JE okNow

			;Checks if you pressed R to restart the game

		JMP loopc
		
		okNow:
			
			DEC restarted

			;Reset the byte for later use
			
			JMP lol
		
		endIt:
			
			INC endTheGame

			;Increments the byte for closing the window
		
		lol:
		
		POPA
		
		RET
	endGame ENDP