.text
	.align 2
	.globl main

	main: #This code shows how a atomic exchange works

		ori $v0, $zero, 9
		ori $a0, $zero, 4
		syscall

		ori $t2, $zero, 77
		sw $t2, 0($v0)

		loop_until_works:
			ori $t0, $zero, 1
			ll $t1, 0($v0)	#Load linked
			sc $t0, 0($v0)	#Store conditional
			#$t0 will be 0 if and only if memory region 0($v0) is modified exactly between ll and sc instructions
			#else, $t0 will be 1
			beq $t0, $zero, loop_until_works #Branch, if store do not worked

		ori $v0, $zero, 1
		or $a0, $zero, $t1
		syscall

		ori $v0, $zero, 17
		ori $a0, $zero, 0
		syscall
