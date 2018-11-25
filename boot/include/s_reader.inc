;=============================
;	      Sector Reader
;		Copyright Lunaixsky 
;=============================
%ifndef __SREADER_INC_67343546FDCC56AAB872_INCLUDED__
%define __SREADER_INC_67343546FDCC56AAB872_INCLUDED__

;=============Constant=========
%define DISK_SEC 18				;Sector per cylindar
%define DISK_CYL 79				;Cylindar per head
%define HEAD_HHD_TOTAL 7
;==============================

	RESETFLP:
		mov ah,0x0
		mov dl,0x0
		int 0x13
		ret
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
		jbe reLoop		;no , continus read
		xor cl,cl
		mov cl,1		;yes , reset sector to frist, we need to read from 1 .We have finish C0-H0-S18
		add dh,1		;When to next sector C0-H1-S1 , Move to next Header
		cmp dh,1		;All Header are complete?
		jbe reLoop		;no, continus jump to 'reLoop' if below or equal
		xor dh,dh		;Set to 0	And we have finish C0-H1-S18
		add ch,1		;Move to next Cylinder
		xor cl,cl 		;set to 0
		mov cl,1		;Set to first Sector 	C1-H0-S1
		cmp ch,DISK_CYL	;all Cylinder finished(We're read'o disk!)
		jae SUCC
		jb reLoop		;not yet, continus
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
		
		
	DISK_WRITE:
		mov al,1
		mov di,0
	l0:
		int 0x13
		jc R_F
		inc di
		inc cl
		add bx,0x200
		cmp di,si
		jae done
		cmp cl,DISK_SEC
		jb l0
		mov cl,1
		inc dh
		cmp dh,HEAD_HHD_TOTAL
		jb l0
		xor dh,dh
		inc ch
		xor cl,cl
		cmp ch,DISK_CYL
		jb l0
		xor cx,cx
		xor ax,ax
		xor bx,bx
		xor dx,dx
		jmp done
	done:
		mov ah,0x0
		mov dl,0x0
		int 0x13
		mov ax,0x321
		ret
		
;int _sn=0;
;//secn as arg
;__asm mov ah,3
;for(int cyl=0;(cyl<80 && _sn>=secn);cyl++)
;{
;	for(int hd=0;(hd<8 && _sn>=secn);hd++)
;	{
;		for(int sec=0;(sec<=18 && _sn>=secn);sec++)
;		{
;			__asm
;			{
;				mov cl,sec
;				mov dh,hd
;				mov ch,cyl
;				int 0x13
;			}
;			_sn++;
;		}
;	}
;}

%endif