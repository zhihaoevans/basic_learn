	.file	"a.c"
	.globl	global_init_a
	.data
	.align 4
	.type	global_init_a, @object
	.size	global_init_a, 4
global_init_a:
	.long	3
	.comm	global_noinit_b,4,4
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$4, -4(%rbp)
	leaq	-4(%rbp), %rax
	movq	%rax, %rsi
	movl	$static_a.1728, %edi
	call	swap
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.data
	.align 4
	.type	static_a.1728, @object
	.size	static_a.1728, 4
static_a.1728:
	.long	3
	.local	static_b.1729
	.comm	static_b.1729,4,4
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
