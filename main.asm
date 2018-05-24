
INCLUDE \masm32\include\masm32rt.inc

INCLUDE mainFuncs.inc

.386

.MODEL flat, STDCALL

.CODE
	
	main PROC

		INVOKE init

		loopa:
			
			INVOKE draw

			INVOKE update

		JMP loopa

		RET
	main ENDP

END main