global long_mode_start
extern kernel_main
extern _init

section .text
bits 64
long_mode_start:
    ; load null into all data segment registers
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; early init (before kernel)
    call _init
    ; main entrypoint
	call kernel_main
    hlt
