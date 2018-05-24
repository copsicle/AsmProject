
INCLUDE drd.inc

INCLUDELIB drd.lib

INCLUDE data.inc

.CODE

	init PROC

		INVOKE drd_init, 1280, 720, 0

		RET
	init ENDP

	update PROC

		PUSHA

		INVOKE drd_processMessages

		POPA

		RET
	update ENDP

	draw PROC



		RET
	draw ENDP