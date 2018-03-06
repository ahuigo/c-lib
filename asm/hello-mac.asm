; for x86-64 on mac osx!
;	nasm -f macho64 -o hello.o hello-mac.asm
;	ld -o hello -e main hello.o
;	./hello
SECTION .data

msg: db "hello xiaozi!", 0x0a
len: equ $-msg

SECTION .text
global main

kernel:
    syscall
    ret

main:
	//test
    mov rax,0x2000004;
    mov rdi,1
    mov rsi,msg
    mov rdx,len
    call kernel

    mov rax,0x2000001
    mov rdi,0 ;//exit status
    call kernel
