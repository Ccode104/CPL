	.file	"Assembly_Code_Analysis.c"
	.text
	.p2align 4
	.globl	fib
	.type	fib, @function
fib:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$72, %rsp
	.cfi_def_cfa_offset 128
	movl	%edi, 12(%rsp)
	movl	%edi, 4(%rsp)
	movl	$0, 16(%rsp)
	cmpl	$1, %edi
	jle	.L46
.L2:
	movl	4(%rsp), %eax
	movl	$0, 20(%rsp)
	subl	$1, %eax
	movl	%eax, 8(%rsp)
	cmpl	$1, %eax
	je	.L6
.L3:
	movl	8(%rsp), %eax
	movl	$0, 24(%rsp)
	subl	$1, %eax
	movl	%eax, %r11d
	cmpl	$1, %eax
	je	.L55
.L5:
	leal	-1(%r11), %eax
	movl	$0, 28(%rsp)
	cmpl	$1, %eax
	je	.L10
	movl	%r11d, 32(%rsp)
	movl	%eax, %r11d
.L7:
	xorl	%ecx, %ecx
	leal	-1(%r11), %r12d
	movl	%ecx, %r15d
	cmpl	$1, %r12d
	je	.L56
.L9:
	leal	-1(%r12), %ebx
	xorl	%edx, %edx
	cmpl	$1, %ebx
	je	.L57
.L11:
	cmpl	$2, %ebx
	je	.L58
	leal	-3(%rbx), %r13d
	leal	-6(%rbx), %esi
	xorl	%r8d, %r8d
	movl	%r13d, %eax
	leal	-4(%rbx), %r9d
	andl	$-2, %eax
	subl	%eax, %esi
.L16:
	leal	2(%r9), %ebp
	xorl	%ecx, %ecx
	cmpl	$-1, %r9d
	je	.L19
.L15:
	leal	-1(%rbp), %r14d
	xorl	%r10d, %r10d
	cmpl	$1, %r14d
	je	.L59
.L18:
	leal	-1(%r14), %edi
	movl	%r9d, 60(%rsp)
	subl	$2, %r14d
	movl	%esi, 56(%rsp)
	movl	%r10d, 52(%rsp)
	movl	%ecx, 48(%rsp)
	movl	%r8d, 44(%rsp)
	movl	%edx, 40(%rsp)
	movl	%r11d, 36(%rsp)
	call	fib
	movl	52(%rsp), %r10d
	movl	36(%rsp), %r11d
	movl	40(%rsp), %edx
	movl	44(%rsp), %r8d
	addl	%eax, %r10d
	cmpl	$1, %r14d
	movl	48(%rsp), %ecx
	movl	56(%rsp), %esi
	movl	60(%rsp), %r9d
	jg	.L18
	leal	-3(%rbp), %eax
	andl	$1, %eax
	addl	%r10d, %eax
.L20:
	subl	$2, %ebp
	addl	%eax, %ecx
	cmpl	$1, %ebp
	jg	.L15
	movl	%r9d, %ebp
	andl	$1, %ebp
	addl	%ecx, %ebp
.L19:
	subl	$2, %r9d
	addl	%ebp, %r8d
	cmpl	%r9d, %esi
	jne	.L16
	andl	$1, %r13d
	leal	0(%r13,%r8), %eax
.L17:
	subl	$2, %ebx
	addl	%eax, %edx
	cmpl	$1, %ebx
	jg	.L11
	leal	-3(%r12), %eax
	andl	$1, %eax
	addl	%edx, %eax
.L14:
	subl	$2, %r12d
	addl	%eax, %r15d
	cmpl	$1, %r12d
	jg	.L9
	leal	-3(%r11), %eax
	andl	$1, %eax
	addl	%r15d, %eax
.L12:
	subl	$2, %r11d
	addl	%eax, 28(%rsp)
	cmpl	$1, %r11d
	jg	.L7
	movl	32(%rsp), %r11d
	leal	-3(%r11), %eax
	andl	$1, %eax
	addl	28(%rsp), %eax
.L10:
	subl	$2, %r11d
	addl	%eax, 24(%rsp)
	cmpl	$1, %r11d
	jg	.L5
	movl	8(%rsp), %eax
	subl	$3, %eax
	andl	$1, %eax
	addl	24(%rsp), %eax
.L8:
	subl	$2, 8(%rsp)
	movl	8(%rsp), %edi
	addl	%eax, 20(%rsp)
	cmpl	$1, %edi
	jg	.L3
	movl	4(%rsp), %eax
	subl	$3, %eax
	andl	$1, %eax
	addl	20(%rsp), %eax
.L6:
	subl	$2, 4(%rsp)
	movl	4(%rsp), %edi
	addl	%eax, 16(%rsp)
	cmpl	$1, %edi
	jg	.L2
	movl	12(%rsp), %eax
	andl	$1, %eax
	addl	16(%rsp), %eax
	movl	%eax, 12(%rsp)
.L46:
	movl	12(%rsp), %eax
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L58:
	.cfi_restore_state
	movl	$1, %eax
	jmp	.L17
	.p2align 4,,10
	.p2align 3
.L59:
	movl	$1, %eax
	jmp	.L20
.L57:
	movl	$1, %eax
	jmp	.L14
.L56:
	movl	$1, %eax
	jmp	.L12
.L55:
	movl	$1, %eax
	jmp	.L8
	.cfi_endproc
.LFE0:
	.size	fib, .-fib
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$3, %edi
	call	fib
	movl	$1, %edi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	jmp	fib
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
