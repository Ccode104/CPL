	.file	"Assembly_Code_Analysis.c"
	.text
	.globl	fib
	.type	fib, @function
fib:
.LFB0:
	.cfi_startproc
	endbr64

	#Push current base pointer(caller) on stack(64 bit or 8 bytes)
	pushq	%rbp 
	
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	
	#Callee saved register(8 bytes)
	pushq	%rbx 
	
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	
	#Decrement the stack pointer for AR of callee(updation)
	subq	$8, %rsp 
	
	.cfi_def_cfa_offset 32
	
	#Get a copy of the parameter n of callee
	movl	%edi, %ebx  

	#Compare n and 1
	cmpl	$1, %edi

	#if n>1 goto L4 
	jg	.L4 
.L2:
#if n=0,1 where n is not necessarily the parameter of first call 

	#Store the sum(or original parameter passed) in return value register
	movl	%ebx, %eax 

	#Modify the stack pointer to pop out AR of callee
	addq	$8, %rsp 

	.cfi_remember_state
	.cfi_def_cfa_offset 24
	
	#Restore the Callee saved register with value on stack
	popq	%rbx 

	.cfi_def_cfa_offset 16
	
	#Get the old value of base pointer(caller)
	popq	%rbp 

	.cfi_def_cfa_offset 8
	
	#Return Instruction(load the return address from stack to %rip)
	ret 
.L4:
#if n>1
	
	.cfi_restore_state
	
	#Substract 1 from n to get n-1 and store it in parameter register
	leal	-1(%rdi), %edi 

	#Call fib with (n-1)
	call	fib 

	#Store a copy of return value of fib(n-1) (ebp is callee saved register,here being used as general purpose register)
	movl	%eax, %ebp 

	#Substract 2 from n to get n-2 and store it in parameter register
	leal	-2(%rbx), %edi 

	#Call fib with (n-2)
	call	fib 

	#Store the sum of fib(n-1) and fib(n-2) in a register
	leal	0(%rbp,%rax), %ebx 

	#unconditional jump to .L2
	jmp	.L2 

	.cfi_endproc
.LFE0:
	.size	fib, .-fib
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	endbr64

	#Decrement the stack pointer for some caller saved register
	subq	$8, %rsp  
	.cfi_def_cfa_offset 16

	#Store 5 in parameter register i.e n=5
	movl	$5, %edi 

	#Call fib(5) and push the address of this line(8 bytes return address for callee) to stack
	call	fib 

	#Pop out the AR of main
	addq	$8, %rsp 	

	.cfi_def_cfa_offset 8
	
	#Return Instruction
	ret 

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
