section .data
	array db 89, 10, 67, 1, 4, 27, 12, 34, 86, 3
	ARRAY_SIZE equ $ - array

	array_fmt db "  %d", 0
	usort_str db "unsorted array:", 0
	sort_str db "sorted array:", 0
	newline db 10, 0

section .text
	extern puts
	global _start

_start:
  push  usort_str
  call  puts
  add   esp, 4

  push  ARRAY_SIZE
  push  array
  push  array_fmt
  call  print_array10
  add   esp, 12

  push  ARRAY_SIZE 
  push  array
  call  sort_routine20

; Adjust the stack pointer
  add   esp, 8

  push  sort_str
  call  puts
  add   esp, 4

  push  ARRAY_SIZE 
  push  array
  push  array_fmt
  call  print_array10
  add   esp, 12
  jmp   _exit

  extern printf

print_array10:
  push  ebp
  mov   ebp, esp
  sub   esp, 4
  mov   edx, [ebp + 8]
  mov   ebx, [ebp + 12]
  mov   ecx, [ebp + 16]

  mov   esi, 0

push_loop:
  mov   [ebp - 4], ecx
  mov   edx, [ebp + 8]
  xor   eax, eax
  mov   al, byte [ebx + esi]
  push  eax
  push  edx

  call  printf
  add   esp, 8
  mov   ecx, [ebp - 4]
  inc   esi
  loop  push_loop

  push  newline
  call  printf
  add   esp, 4
  mov   esp, ebp
  pop   ebp
  ret

sort_routine20:
  push  ebp
  mov   ebp, esp

; Allocate a word of space in stack
  sub   esp, 4 

; Get the address of the array
  mov   ebx, [ebp + 8] 

; Store array size
  mov   ecx, [ebp + 12]
  dec   ecx

; Prepare for outer loop here
  xor   esi, esi

outer_loop:
; This stores the min index
  mov   [ebp - 4], esi 
  mov   edi, esi
  inc   edi

inner_loop:
  cmp   edi, ARRAY_SIZE
  jge   swap_vars
  xor   al, al
  mov   edx, [ebp - 4]
  mov   al, byte [ebx + edx]
  cmp   byte [ebx + edi], al
  jge   check_next
  mov   [ebp - 4], edi

check_next:
  inc   edi
  jmp   inner_loop

swap_vars:
  mov   edi, [ebp - 4]
  mov   dl, byte [ebx + edi]
  mov   al, byte [ebx + esi]
  mov   byte [ebx + esi], dl
  mov   byte [ebx + edi], al

  inc   esi
  loop  outer_loop

  mov   esp, ebp
  pop   ebp
  ret

_exit:
  mov   eax, 1
  mov   ebx, 0
  int   80h
