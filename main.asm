
INCLUDE \masm32\include\masm32rt.inc

;Include essential masm stuff

INCLUDE mainFuncs.inc

;Include all of the functions

.386

;Limit CPU instructions that masm is allwed to use

.MODEL flat, STDCALL

;Define memory model to use, masm seems to ignore it though

.CODE
	
	main PROC

	;Start of main function

		INVOKE init

		;Call the initialize function

		loopa:

		;Start main loop 

		;Call all drawing and updating functions and repeat them infinitly

			INVOKE draw

			CMP pScored, 1
			JE startTime

			;pScored is increased when a player scores a point

			JMP after

			startTime:

				INVOKE Sleep, 1000
				DEC pScored

				;Add a timeout before starting the game again and reset pScored value

			after:

			INVOKE update

			INVOKE scoring, OFFSET ball, OFFSET scoreImgP1, OFFSET scoreImgP2, OFFSET scoreImgP12 , OFFSET scoreImgP22

			CMP endTheGame, 1
			JE endItAll

			;endTheGame is increased when a player presses escape
			
		JMP loopa

		endItAll:

		INVOKE ExitProcess, 0

		;End and exit the code

		RET
	main ENDP

END main