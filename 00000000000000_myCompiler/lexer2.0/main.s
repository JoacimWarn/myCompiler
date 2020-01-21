	.file	"main.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC1:
	.ascii "%d\12\0"
LC2:
	.ascii "r\0"
LC3:
	.ascii "test.txt\0"
LC4:
	.ascii "error while opening file\0"
LC5:
	.ascii "w\0"
LC6:
	.ascii "outputLexer.txt\0"
LC7:
	.ascii "\12Error opening file...\0"
LC8:
	.ascii "%c\11\11operator\12\0"
LC9:
	.ascii "%s\11\11keyword\12\0"
LC10:
	.ascii "%s\11\11int\12\0"
LC11:
	.ascii "%s\11\11identifier\12\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB10:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$64, %esp
	call	___main
	movl	$123, (%esp)
	call	_isalnum
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	_printf
	movl	$791293227, 25(%esp)
	movw	$15653, 29(%esp)
	movb	$0, 31(%esp)
	movl	$0, 56(%esp)
	movl	56(%esp), %eax
	movl	%eax, 60(%esp)
	movl	$LC2, 4(%esp)
	movl	$LC3, (%esp)
	call	_fopen
	movl	%eax, 52(%esp)
	cmpl	$0, 52(%esp)
	jne	L2
	movl	$LC4, (%esp)
	call	_puts
	movl	$1, %eax
	jmp	L14
L2:
	movl	$LC5, 4(%esp)
	movl	$LC6, (%esp)
	call	_fopen
	movl	%eax, 48(%esp)
	cmpl	$0, 48(%esp)
	jne	L4
	movl	__imp___iob, %eax
	addl	$64, %eax
	movl	%eax, 12(%esp)
	movl	$22, 8(%esp)
	movl	$1, 4(%esp)
	movl	$LC7, (%esp)
	call	_fwrite
	movl	52(%esp), %eax
	movl	%eax, (%esp)
	call	_fclose
	movl	$1, %eax
	jmp	L14
L4:
	jmp	L5
L13:
	movl	$0, 60(%esp)
	jmp	L6
L8:
	leal	25(%esp), %edx
	movl	60(%esp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	cmpb	47(%esp), %al
	jne	L7
	leal	25(%esp), %edx
	movl	60(%esp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	movl	%eax, 8(%esp)
	movl	$LC8, 4(%esp)
	movl	48(%esp), %eax
	movl	%eax, (%esp)
	call	_fprintf
L7:
	addl	$1, 60(%esp)
L6:
	cmpl	$5, 60(%esp)
	jle	L8
	movsbl	47(%esp), %eax
	movl	%eax, (%esp)
	call	_isalnum
	testl	%eax, %eax
	je	L9
	movl	56(%esp), %eax
	leal	1(%eax), %edx
	movl	%edx, 56(%esp)
	movzbl	47(%esp), %edx
	movb	%dl, 32(%esp,%eax)
	jmp	L5
L9:
	cmpb	$32, 47(%esp)
	je	L10
	cmpb	$10, 47(%esp)
	je	L10
	cmpb	$44, 47(%esp)
	jne	L5
L10:
	cmpl	$0, 56(%esp)
	je	L5
	leal	32(%esp), %edx
	movl	56(%esp), %eax
	addl	%edx, %eax
	movb	$0, (%eax)
	movl	$0, 56(%esp)
	leal	32(%esp), %eax
	movl	%eax, (%esp)
	call	_isKeyWord
	cmpl	$1, %eax
	jne	L11
	leal	32(%esp), %eax
	movl	%eax, 8(%esp)
	movl	$LC9, 4(%esp)
	movl	48(%esp), %eax
	movl	%eax, (%esp)
	call	_fprintf
	jmp	L5
L11:
	leal	32(%esp), %eax
	movl	%eax, (%esp)
	call	_isKeyWord
	testl	%eax, %eax
	jne	L12
	leal	32(%esp), %eax
	movl	%eax, (%esp)
	call	_isDigit
	testl	%eax, %eax
	je	L12
	leal	32(%esp), %eax
	movl	%eax, 8(%esp)
	movl	$LC10, 4(%esp)
	movl	48(%esp), %eax
	movl	%eax, (%esp)
	call	_fprintf
	jmp	L5
L12:
	leal	32(%esp), %eax
	movl	%eax, 8(%esp)
	movl	$LC11, 4(%esp)
	movl	48(%esp), %eax
	movl	%eax, (%esp)
	call	_fprintf
L5:
	movl	52(%esp), %eax
	movl	%eax, (%esp)
	call	_fgetc
	movb	%al, 47(%esp)
	cmpb	$-1, 47(%esp)
	jne	L13
	movl	52(%esp), %eax
	movl	%eax, (%esp)
	call	_fclose
	movl	48(%esp), %eax
	movl	%eax, (%esp)
	call	_fclose
	movl	$0, %eax
L14:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE10:
	.data
	.align 32
LC0:
	.ascii "auto\0"
	.space 5
	.ascii "break\0"
	.space 4
	.ascii "case\0"
	.space 5
	.ascii "char\0"
	.space 5
	.ascii "const\0"
	.space 4
	.ascii "continue\0"
	.space 1
	.ascii "default\0"
	.space 2
	.ascii "do\0"
	.space 7
	.ascii "double\0"
	.space 3
	.ascii "else\0"
	.space 5
	.ascii "enum\0"
	.space 5
	.ascii "extern\0"
	.space 3
	.ascii "float\0"
	.space 4
	.ascii "for\0"
	.space 6
	.ascii "goto\0"
	.space 5
	.ascii "if\0"
	.space 7
	.ascii "int\0"
	.space 6
	.ascii "long\0"
	.space 5
	.ascii "register\0"
	.space 1
	.ascii "return\0"
	.space 3
	.ascii "short\0"
	.space 4
	.ascii "signed\0"
	.space 3
	.ascii "sizeof\0"
	.space 3
	.ascii "static\0"
	.space 3
	.ascii "struct\0"
	.space 3
	.ascii "switch\0"
	.space 3
	.ascii "typedef\0"
	.space 2
	.ascii "union\0"
	.space 4
	.ascii "unsigned\0"
	.space 1
	.ascii "void\0"
	.space 5
	.ascii "volatile\0"
	.space 1
	.ascii "while\0"
	.space 4
	.text
	.globl	_isKeyWord
	.def	_isKeyWord;	.scl	2;	.type	32;	.endef
_isKeyWord:
LFB11:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$364, %esp
	.cfi_offset 7, -12
	.cfi_offset 6, -16
	.cfi_offset 3, -20
	leal	-352(%ebp), %edx
	movl	$LC0, %ebx
	movl	$80, %eax
	movl	%edx, %edi
	movl	%ebx, %esi
	movl	%eax, %ecx
	rep movsl
	movl	$0, -32(%ebp)
	movl	$0, -28(%ebp)
	jmp	L16
L19:
	leal	-352(%ebp), %ecx
	movl	-28(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	leal	(%ecx,%eax), %edx
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	_str_cmp
	testl	%eax, %eax
	jne	L17
	movl	$1, -32(%ebp)
	jmp	L18
L17:
	addl	$1, -28(%ebp)
L16:
	cmpl	$31, -28(%ebp)
	jle	L19
L18:
	movl	-32(%ebp), %eax
	addl	$364, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%edi
	.cfi_restore 7
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE11:
	.globl	_str_cmp
	.def	_str_cmp;	.scl	2;	.type	32;	.endef
_str_cmp:
LFB12:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	jmp	L22
L25:
	movl	8(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	L23
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	L23
	movl	$0, %eax
	jmp	L24
L23:
	movl	8(%ebp), %eax
	addl	$1, %eax
	movl	%eax, 8(%ebp)
	movl	12(%ebp), %eax
	addl	$1, %eax
	movl	%eax, 12(%ebp)
L22:
	movl	8(%ebp), %eax
	movzbl	(%eax), %edx
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	%al, %dl
	je	L25
	movl	$1, %eax
L24:
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE12:
	.globl	_isDigit
	.def	_isDigit;	.scl	2;	.type	32;	.endef
_isDigit:
LFB13:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
	jmp	L27
L30:
	movl	-4(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$47, %al
	jle	L28
	movl	-4(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$57, %al
	jg	L28
	movl	$1, %eax
	jmp	L29
L28:
	movl	-4(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -4(%ebp)
L27:
	movl	-4(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	L30
	movl	$0, %eax
L29:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE13:
	.ident	"GCC: (GNU) 4.8.1"
	.def	_isalnum;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_fopen;	.scl	2;	.type	32;	.endef
	.def	_puts;	.scl	2;	.type	32;	.endef
	.def	_fwrite;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
	.def	_fprintf;	.scl	2;	.type	32;	.endef
	.def	_fgetc;	.scl	2;	.type	32;	.endef
