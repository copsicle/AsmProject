
INCLUDE drd.inc

INCLUDELIB drd.lib

INCLUDE data.inc

.CODE

	init PROC

		INVOKE drd_init, xlen, ylen, winMode

		INVOKE drd_imageLoadFile, OFFSET hddJeff, OFFSET jeff.info

		INVOKE drd_imageLoadFile, OFFSET hddBG, OFFSET BG1.info

		INVOKE drd_imageLoadFile, OFFSET hddBG, OFFSET BG2.info

		INVOKE drd_imageSetTransparent, OFFSET jeff.info, white

		MOV BG2.pos.x, -xlen

		MOV EAX, speed

		MOV EBX, speed

		RET
	init ENDP

	update PROC
	
		PUSHA

		INVOKE drd_processMessages

		INVOKE drd_flip

		INVOKE drd_pixelsClear, black

		POPA

		ADD jeff.pos.x, EAX

		ADD jeff.pos.y, EBX

		INC BG1.pos.x

		INC BG2.pos.x

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

		CMP BG1.pos.x, xlen
		JE bg1mv

		CMP BG2.pos.x, xlen
		JE bg2mv

		RET

		bg1mv:
			MOV BG1.pos.x, -xlen
		RET

		bg2mv:
			MOV BG2.pos.x, -xlen
		RET

	jeffcmp PROC

		CMP jeff.pos.x, xhitbox
		JGE xchange

		CMP jeff.pos.x, 0
		JLE xchange

		goback:

			CMP jeff.pos.y, yhitbox
			JGE ychange

			CMP jeff.pos.y, 0
			JLE ychange
		
			RET
		
		xchange:
			
			NEG EAX

		JMP goback

		ychange:

			NEG EBX

		RET
	jeffcmp ENDP

	bgcmp ENDP