
INCLUDE drd.inc

INCLUDELIB drd.lib

INCLUDE data.inc

.CODE

	init PROC

		INVOKE drd_init, 1280, 720, 0

		INVOKE drd_imageLoadFile, offset hddJeff, offset jeff.info

		MOV EBX, 1

		MOV EDX, 1

		RET
	init ENDP

	update PROC

		PUSHA

		INVOKE drd_processMessages

		INVOKE drd_flip

		INVOKE drd_pixelsClear, 0

		POPA

		ADD jeff.pos.x, EBX

		ADD jeff.pos.y, EDX

		RET
	update ENDP

	draw PROC
		
		PUSHA

		INVOKE drd_imageDraw, offset jeff.info, jeff.pos.x, jeff.pos.y
		
		POPA

		RET
	draw ENDP