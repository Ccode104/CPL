	.file	"temp.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
#Illustration of function prologue and epilogue
	.cfi_startproc
	endbr64
	#Prologue
	#Push current base pointer on stack
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16

	#Make base pointer equal to stack pointer for AR of main
	movq	%rsp, %rbp

	.cfi_def_cfa_register 6
	#Function Body
	nop

	#Epilogue

	#Decrement the stack pointer(Here no data on AR of main)
	#Nothing in this case

	#Pop out callee saved registers and old base pointer 
	popq	%rbp 
	.cfi_def_cfa 7, 8
	
	#Return
	ret
	.cfi_endproc
.LFE0:
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
