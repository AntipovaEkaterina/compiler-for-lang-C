section .text
	global	main
main:
	push	rbp
	mov		rbp, rsp
	sub		rsp, 80
	mov		rdx, 4
	mov		rcx, 2
	imul	rdx, rcx
	mov		[rbp-24], rdx

	push	rdi
	push	rax
	push	rsi

	mov		rdi, formInt
	mov		rax, [rbp-24]
	mov		rsi, rax
	xor		rax, rax
	call	printf
	pop		rsi
	pop		rax
	pop		rdi

	mov		rdx, 1
	mov		[rbp-32], rdx
.L5:
	mov		rdx, [rbp-32]
	mov		rcx, 3
	cmp		rdx, rcx
	jge		.L105

	push	rdi
	push	rax
	push	rsi

	mov		rdi, formInt
	mov		rax, [rbp-32]
	mov		rsi, rax
	xor		rax, rax
	call	printf
	pop		rsi
	pop		rax
	pop		rdi

	mov		rdx, [rbp-32]
	mov		rcx, 1
	add		rdx, rcx
	mov		[rbp-32], rdx
	jmp		.L5
.L105:

	push	rdi
	push	rax
	push	rsi

	mov		rdi, formInt
	mov		rax, [rbp-32]
	mov		rsi, rax
	xor		rax, rax
	call	printf
	pop		rsi
	pop		rax
	pop		rdi

	mov		rdx, [rbp-32]
	mov		rcx, 1
	add		rdx, rcx
	mov		[rbp-32], rdx
.L7:
	mov		rdx, [rbp-32]
	mov		rcx, 8
	cmp		rdx, rcx
	jge		.L107

	push	rdi
	push	rax
	push	rsi

	mov		rdi, formInt
	mov		rax, [rbp-32]
	mov		rsi, rax
	xor		rax, rax
	call	printf
	pop		rsi
	pop		rax
	pop		rdi

.L107:
.L9:
	mov		rdx, [rbp-32]
	mov		rcx, 10
	cmp		rdx, rcx
	jle		.L109

	push	rdi
	push	rax
	push	rsi

	mov		rdi, formInt
	mov		rax, [rbp-32]
	mov		rsi, rax
	xor		rax, rax
	call	printf
	pop		rsi
	pop		rax
	pop		rdi

.L109:
	add		rsp, 80
	pop		rbp
	mov		rax, 1
	xor		rbx, rbx
	int		0x80

	extern	printf
	extern	scanf

section .data
	formString db "%s", 10, 0
	formInt db "%d", 10, 0
	formInInt db "%d", 0
	bufInInt dq 0
