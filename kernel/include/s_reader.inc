;=============================
;	      Sector Reader
;		Copyright Lunaixsky 
;=============================
%ifndef __SREADER_INC_67343546FDCC56AAB872_INCLUDED__
%define __SREADER_INC_67343546FDCC56AAB872_INCLUDED__

;=============Constant=========
%define DISK_SEC 18				;Sector per cylindar
%define DISK_CYL 79				;Cylindar per head
;==============================
	;********************
	;*	Read Sectors
	;*	para: si: How many sector you want to read
	;*		  ch: Cylinder (Track,0)
	;*		  cl: Start Sector (usually be one)
	;*		  dl: Disk number (Floppy,0)
	;*		  dh: Head
	;********************
	READSECS:
		mov di,0
		mov cl,2
		mov al,1
	reLoop:
		mov ah,2
		int 0x13
		jc R_F
		add bx,0x0200	;offset 512B
		add di,1		;Read sector counter
		add cl,1		;Start sector move backword
		cmp di,si		;Is di>=si?
		jae SUCC		;yes went to success
		cmp cl,DISK_SEC	;Is there already 18 sectors?
		jbe reLoop		;no , continous read
		mov cl,1		;yes , reset sector to frist, we need to read from 1
		add ch,1		;Cause'o the sectors of cuurent cylindar are all read , we need to read another sectors on next cylindar
		cmp ch,DISK_CYL	;All cylindar are complete?
		jbe reLoop		;no, continous
		mov ch,1		;yes , reset to 1
		add dh,1		;head++
		cmp dh,2		;all head finished(We're read'o disk!)
		jae SUCC
		jb reLoop		;not yet, continous
	R_F:				;Failure!
		mov ah,0x0
		mov dl,0x0
		int 0x13
		mov ax,0xf
		ret
	SUCC:			;Success!
		mov ah,0x0
		mov dl,0x0
		int 0x13
		mov ax,0x123
		ret
%endif