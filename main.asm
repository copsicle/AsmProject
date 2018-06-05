
INCLUDE \masm32\include\masm32rt.inc

;Include essential masm stuff

INCLUDE mainFuncs.inc

;Include all of the functions

.386

;Limit CPU instructions that masm is allwed to use

.MODEL flat, STDCALL

;Define memory model to use, doesn't seem to work rn

.CODE
	
	main PROC

	;Start of main function

		INVOKE init

		;Call the initialize function

		loopa:

		;Start loop 

			INVOKE draw

			CMP pScored, 1
			JE startTime
			JMP after
			startTime:
				INVOKE Sleep, 1000
				DEC pScored
			after:

			INVOKE update

			INVOKE scoring, OFFSET ball

			CMP endTheGame, 1
			JE endItAll

			;Call all drawing and updating functions and repeat them infinitly
			
		JMP loopa

		endItAll:

		RET
	main ENDP

END main