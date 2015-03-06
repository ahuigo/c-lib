/*
    nasm -f elf -o c.o c.s
	ld -m elf_i386 -e _start -o c c.o
		You must specify elf_i386, other wise you could not read symbols: File in wrong format
*/
section .data

   prompt_str  db   'Enter your name: '

; $ is the location counter
   STR_SIZE  equ  $ - prompt_str

   greet_str  db  'Hello '


   GSTR_SIZE  equ  $ - greet_str


section .bss

; Reserve 32 bytes of memory
   buff  resb  32

; A macro with two parameters
; Implements the write system call
   %macro write 2 
      mov   eax, 4
      mov   ebx, 1
      mov   ecx, %1
      mov   edx, %2
      int   80h
   %endmacro


; Implements the read system call
   %macro read 2
      mov   eax, 3
      mov   ebx, 0
      mov   ecx, %1
      mov   edx, %2
      int   80h
   %endmacro


section .text

   global _start

   _start:
      write prompt_str, STR_SIZE
      read  buff, 32

; Read returns the length in eax
      push  eax

; Print the hello text
      write greet_str, GSTR_SIZE

      pop   edx

; edx  = length returned by read
      write buff, edx

   _exit:
      mov   eax, 1
      mov   ebx, 0
      int   80h
