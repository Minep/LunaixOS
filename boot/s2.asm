[bits 16]
org 0x2000
jmp load_
%include "boot/include/gdt.inc"
%include "boot/include/graphics.inc"
%include "boot/include/A20.inc"
%include "boot/include/_DEF__.inc"
%include "boot/include/s_reader.inc"
%include "boot/include/bootinfo.inc"
%include "boot/include/memory.inc"

  ;############define

  lding       db "LOADING LUNAIX...",0
  lding2      db "[LUNA'S INFO] Initialize x86 Environment...",0
  lding3      db "[LUNA'S INFO] Opening SYS Bus A20",0
  lding4      db "[LUNA'S INFO] Loading Kernel ...",0
  lding5      db "[LUNA'S INFO] Done! ...",0
  msgFailure  db "[FATAL ERROR] LUNA could not load kernel correctly! Press any key to reboot",0
  splt        db "==========================",0
  bts:        db "     Lunaix OS v1.0       ",0
  arth        db "      -=Lunaixsky=-       ",0
  s           db 0

  ;end define#################

  ;Boot info
  LUNAIX_boot_info:
    istruc multiboot_info
      at multiboot_info.flags,      dd 0
      at multiboot_info.memoryLo,     dd 0
      at multiboot_info.memoryHi,     dd 0
      at multiboot_info.bootDevice,   dd 0
      at multiboot_info.cmdLine,      dd 0
      at multiboot_info.mods_count,   dd 0
      at multiboot_info.mods_addr,    dd 0
      at multiboot_info.syms0,      dd 0
      at multiboot_info.syms1,      dd 0
      at multiboot_info.syms2,      dd 0
      at multiboot_info.mmap_length,    dd 0
      at multiboot_info.mmap_addr,    dd 0
      at multiboot_info.drives_length,  dd 0
      at multiboot_info.drives_addr,    dd 0
      at multiboot_info.config_table,   dd 0
      at multiboot_info.bootloader_name,  dd 0
      at multiboot_info.apm_table,    dd 0
      at multiboot_info.vbe_control_info, dd 0
      at multiboot_info.vbe_mode_info,  dw 0
      at multiboot_info.vbe_interface_seg,dw 0
      at multiboot_info.vbe_interface_off,dw 0
      at multiboot_info.vbe_interface_len,dw 0
    iend

  load_:
    cli
    xor   ax, ax             ; null segments
    mov   ds, ax
    mov   es, ax
    mov   ax, 0x0000         ; stack begins at 0x9000-0xffff
    mov   ss, ax
    mov   sp, 0xFFFF
    sti
    mov [LUNAIX_boot_info+multiboot_info.bootDevice], dl
    sti
    mov al,0x03
    mov ah,0
    int 0x10
    mov si,splt
    call println16
    mov si,bts
    call println16
    mov si,arth
    call println16
    mov si,splt
    call println16
    mov si,s
    call println16
    mov si,s
    call println16
    mov si,lding
    call println16
    mov si,lding2
    call println16
    call insGDT
    mov si,lding3


    call println16
    call EnableA20_KKbrd_Out    ;Open A20


    mov al,0xAE     ;Enabling keyboard
    out 0x64,al


    ;=====READ KERNEL=====
    mov si,lding4
    call println16
    call RESETFLP

    pusha
    xor eax, eax
    xor ebx, ebx
    call BiosGetMemorySize64MB

    mov word [LUNAIX_boot_info+multiboot_info.memoryHi], bx
    mov word [LUNAIX_boot_info+multiboot_info.memoryLo], ax

    mov eax, 0x0
    mov ds, ax
    mov di, 0x1000
    call BiosGetMemoryMap
    popa
    pusha
    xor cx,cx
    mov ax,0
    mov es,ax
    mov bx,KEL_R_MODE_ADD
    mov si,READ_KER_SIZE    ;How many sector should be read
    xor ch,ch    ;Cylinder 0 (Track 0)
    mov cl,8    ;Sector 7
    mov dl,0    ;Floppy A
    mov dh,0    ;Head 0
    mov ah,2    ;Function 2 (Read Sector)
    call READSECS
    cmp ax,0x123
    jne rb
    popa

    mov si,lding4
    call println16
    cli             ; clear interrupts
    mov eax, cr0    ; set bit 0 in cr0--enter pmode
    or  eax, 1
    mov cr0, eax
    jmp CODE_DESC:S3

rb:
  mov si, msgFailure    ; Nope--print error
  call  println16
  mov ah, 0
  int     0x16                    ; await keypress
  int     0x19                    ; warm boot computer

[bits 32]
  S3:
    ;Setting up register
    mov   ax, DATA_DESC    ; set data segments to data selector (0x10)
    mov   ds, ax
    mov   ss, ax
    mov   es, ax
    mov   esp, 90000h   ; stack begins from 90000h
                        ;You can custom it by yourself or just use the default
    call ClrScr32
    mov ebx,tp32
    call Puts32

    cld
    mov esi,KEL_R_MODE_ADD
    mov edi,KEL_P_MODE_ADD
    mov ecx,20000
    rep movsb
    mov ebx,dn
    call Puts32

    ;Check Image
    mov ebx, [KEL_P_MODE_ADD+60]
    add ebx, KEL_P_MODE_ADD
    ;=====EXECUTE KERNEL
    add ebx, 24
    mov eax, [ebx]      
    add ebx, 16     ; address of entry point of SYSCORE0.LUASYS
    mov ebp, dword [ebx]    ; get entry point offset in code section  
    add ebx, 12
    mov eax, dword [ebx]
    add ebp, eax
    cli

    mov   eax, 0x2badb002     ; multiboot specs say eax should be this
    mov   ebx, 0
    mov   edx, 20000                ;Image size
    push dword LUNAIX_boot_info     ;Passing down the arg
    jmp ebp  ;Say good bye to bootloader :)
    add esp,4

    cli
    hlt

tp32  db 0x0A,         "                 ___==LUNAIX PERLOAD PROGREAME==___               ",0x0A,0x0A
      db 0x0A,0x0A,0x0A,0x0A
      db 0x0a,         "=================================================================="
      db 0x0A,         "             #      #   #  #####   ###   ###   #   #      ####    ####"
      db 0x0A,         "             #      #   #  #   #  #   #   #     # #      #    #  #    "
      db 0x0A,         "             #      #   #  #   #  #   #   #     ##       #    #   ### "
      db 0x0A,         "             #      #   #  #   #  #####   #    #  #      #    #      #"
      db 0x0A,         "             #####  #####  #   #  #   #  ###  #    #      ####   #### "
      db 0x0A,         "               ================================================================="
      db 0x0A,         "                                                               Build   20161220"
      db 0x0A,         "                                 Copying Kernel...                              ",0
dn    db 0x0A,         "                              Execution Preparing ...                           ",0