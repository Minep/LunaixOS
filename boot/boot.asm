;#
;#		Lunaix bootstrap
;#-------CPR Lunaixsky-------
;#
org 7c00h
jmp load
%include "boot/include/s_reader.inc"
   ;############define
   lding:db "Reading System...",0
   err:	 db "Boot failure!",0
   dot: db ".",0
   ;end define#################

   println:
        lodsb
        or al,al
        jz .pd
        mov ah,0eh
        int 0x10
        jmp println
   .pd:
   		mov ah,3h	;read current cursor
   		int 0x10	;read via 10th interrupt
   		mov bh,0	;reset page to frist
   		inc dh		;increase row by 1
   		mov dl,0	;reset column to frist
   		mov ah,2h	;set cursor 
   		int 0x10	;set via 10th interrupt
        ret 		;return

    print:
        lodsb
        or al,al
        jz .pd_
        mov ah,0eh
        int 0x10
        jmp print
   .pd_:
   		ret



	read_d:
		mov si,4    ;How many sector should be read
		mov ch,0    ;Cylinder 0 (Track 0)
		mov cl,2    ;Sector 2
		mov dl,0    ;Floppy A
		mov dh,0    ;Head 0
		mov ah,2    ;Function 2 (Read Sector)
		call READSECS
		cmp ax,0x123
		je sec
		jne failure
		;call dp_rety

	failure:
		mov si,err
		call println
		cli
		hlt
	dp_rety:
		mov si,dot
		call print
		ret

	sec:
		popa
		mov ax,0
		mov bx,ax
		mov cx,ax
		mov ah,0
		mov dl,0
		int 0x13
		jmp 0:0x2000

   load:
        xor ax,ax
        mov es,ax
        mov ds,ax
        mov si,lding
		call println

		mov ax,0
		mov es,ax       ;ES = 0
		mov bx,0x2000    ;bx = 2000
	                ;Therefore sector will read into 0:2000
		mov ax,0
		pusha
		jmp read_d
times 510-($-$$) db 0
dw 0xAA55