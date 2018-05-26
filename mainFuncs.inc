
INCLUDE drd.inc

INCLUDELIB drd.lib

INCLUDE data.inc

.CODE

	init PROC

		INVOKE drd_init, 1280, 720, 0

		INVOKE drd_imageLoadFile, OFFSET hddJeff, OFFSET jeff.info

		INVOKE drd_imageLoadFile, OFFSET hddBG, OFFSET BG1.info

		INVOKE drd_imageLoadFile, OFFSET hddBG, OFFSET BG2.info

		INVOKE drd_imageSetTransparent, OFFSET jeff.info, 0

		MOV EBX, 1

		MOV EDX, 1

		MOV BG2.pos.x, -1280

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

		ADD BG1.pos.x, EBX

		ADD BG2.pos.x, EDX

		RET
	update ENDP

	draw PROC
		
		PUSHA

		INVOKE drd_imageDraw, OFFSET BG1.info, BG1.pos.x, BG1.pos.y

		INVOKE drd_imageDraw, OFFSET BG2.info, BG2.pos.x, BG2.pos.y

		INVOKE drd_imageDraw, OFFSET jeff.info, jeff.pos.x, jeff.pos.y
		
		POPA

		RET
	draw ENDP

	bgcmp PROC

		CMP BG1.pos.x, 1280
		JE bg1mv

		CMP BG2.pos.x, 1280
		JE bg2mv

		RET

		bg1mv:
			MOV BG1.pos.x, -1280
		RET

		bg2mv:
			MOV BG2.pos.x, -1280
		RET
	bgcmp ENDP