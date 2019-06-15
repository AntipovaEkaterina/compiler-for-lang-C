section .text	
global	main
main:
	push	rbp
	mov		rbp, rsp
	sub		rsp, 0
	mov		rdx, 1
	mov		rcx, 2
	add		rdx, rcx
	mov		[rbp-8], rdx
.L5:
	mov		rdx, [rbp-16]
	mov		rcx, 10
	cmp		rdx, rcx
	jge		.L105
	mov		rdx, 3
	mov		rcx, 3
	add		rdx, rcx
	mov		[rbp-24], rdx
	jmp		.L5
.L105:
	mov		rdx, 3
	mov		rcx, 3
	add		rdx, rcx
	mov		[rbp-24], rdx
	add		rsp, 0
	pop		rbp
	mov		rax, 1
	xor		rbx, rbx
	int		0x80

	extern	printf
	extern	scanf

section .data
	formString db "%%s", 10, 0
	formInt db "%%d", 10, 0
	formInInt db "%%d", 0
	bufInInt dq 0
