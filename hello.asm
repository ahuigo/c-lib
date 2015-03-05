; for x86-64 on mac osx
SECTION .data

msg: db "hello xiaozi!", 0x0a
len: equ $-msg

SECTION .text
global _main

kernel:
    syscall
    ret

_main:
    mov rax,0x2000004
    mov rdi,1
    mov rsi,msg
    mov rdx,len
    call kernel

    mov rax,0x2000001
    mov rdi,0
    call kernel
;nasm -f macho64 -o asm1.o asm1.asm
;ld -o asm1 -e _main asm1.o
;./asm1
