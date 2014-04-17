.model small

;-------------------------------------------------------------------------------
; STACK SEGMENT
.stack 160h

;-------------------------------------------------------------------------------
; DATA SEGMENT
.data
	file_name_size  db 0h
	file_name	db ?
	seed		db ?
	sequence	db ?

	cabecalho 	db '*------------------------------------------------------------------------------*'
	                db '|     GERADOR DE NUMEROS PSEUDOALEATORIOS DE 10 BITS (Leonardo Korndorfer)     |'
	                db '*----------------------------------*----------------------*--------------------*$'
	status_line_1	db '| Arquivo de entrada:              | Sequencia de      valores - semente:      |$'
	body		db '*----------------------------------*----------------------*--------------------*'
	                db '                    1         2         3         4         5         6         '
	                db '          0123456789012345678901234567890123456789012345678901234567890123      '
	                db '        0 ................................................................      '
	                db '       64 ................................................................      '
	                db '      128 ................................................................      '
	                db '      192 ................................................................      '
	                db '      256 ................................................................      '
	                db '      320 ................................................................      '
	                db '      384 ................................................................      '
	                db '      448 ................................................................      '
	                db '      512 ................................................................      '
	                db '      576 ................................................................      '
	                db '      640 ................................................................      '
	                db '      704 ................................................................      '
	                db '      768 ................................................................      '
	                db '      832 ................................................................      '
	                db '      896 ................................................................      '
	                db '      960 ................................................................      '
	                db '     1024 ................................................................      '
			db '*------------------------------------------------------------------------------$'



;-------------------------------------------------------------------------------
; CODE SEGMENT
.code
	write_screen proc near
		mov ah, 6h			; clear the screen
		mov al, 25h			; number of lines
		mov bh, 0fh			; fill attribute
		mov cx, 0h			; ch = superior line cl = left column
		mov dx, 184fh			; ch = inferior line cl = right column
		int 10h

		mov ah, 2h			; define cursor position
		mov dx, 0h
		mov bh, 0h
		int 10h

		lea dx, cabecalho     		; Write header
		mov ah, 9h
		int 21h

		lea dx, status_line_1 		; Write status line initial state
		mov ah, 9h
		int 21h

		lea dx, body			; Write body
		mov ah, 9h
		int 21h

		ret
	write_screen endp

	get_filename proc near
		mov ah, 2h			; define cursor position
		mov dx, 0316h			; dh = line dl = column
		mov bh, 0h
		int 10h

		; stay in this loop to get the filename from the user
		get_filename_get_char_loop:
		mov ah, 8h			; get char from input
		int 21h

		cmp al, 0dh			; compare with return key
		je get_filename_entered_name	; if it is consist the name

		cmp al, 8h			; maybe it's backspace
		je get_filename_bkspce
			
		; 
		; it is a real char. make the magic
		cmp file_name_size, 8h		; if name_size is alreay 8 and next is not a 
		je get_filename_dot_only	; dot

		cmp file_name_size, 0ch		; name size already 12 so wait for enter only
		je get_filename_get_char_loop

		jmp get_filename_continue


		get_filename_dot_only:
			cmp al, 2eh			; if this is not a dot then back to
			jne get_filename_get_char_loop	; loop root

		get_filename_continue:

		inc file_name_size

		mov ah, 2h			; echo char into the screen			
		mov dl, al			; put char (from al) to screen
		int 21h
		jmp get_filename_get_char_loop

		;
		; handle backspace from user while entering filename
		; if a backspace has been pressed we will do:
		;   - get cursor position
		;   - decrease its column value
		;   - print space in position
		;   - repositionate cursor again (as when printing it makes
		;     current position + 1)
		get_filename_bkspce:
			cmp file_name_size, 0h		; if name size if 0 thats because we're
			je get_filename_get_char_loop	; trying to erase something that is not the
							; filename

			dec file_name_size

			mov ah, 3h			; get cursor position
			mov bh, 0h
			int 10h

			; dl has column - dh has line
			dec dl
			push dx				; save dl to repositionate cursor

			mov ah, 2h			; position of cursor
			mov bh, 0h
			int 10h

			; write space to cursor position
			mov ah, 2h			; echo char into the screen			
			mov dl, 20h
			int 21h

			pop dx
			mov ah, 2h			; reposition of cursor
			mov bh, 0h
			int 10h

			jmp get_filename_get_char_loop
		

		get_filename_entered_name:


		; TODO: Verify if this is really necessary
		mov ah, 2h			; put cursor position to 25x80
		mov dx, 0194fh			; dh = line dl = column
		mov bh, 0h
		int 10h

		ret
	get_filename endp


start:
	mov ax, @data
	mov ds, ax			; Set DS to point the data segment


	call write_screen
	call get_filename

wait_for_key_pressed:
	mov ah, 8h
	int 21h

	mov ax, 4c00h			; exit to DOS
	int 21h

end start
