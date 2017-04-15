.data
	.align 0
	s:	.asciiz "abccccdcc"
	c:	.ascii "c"

.text
	.align 2
	.globl main

main:
		la $a0, s 				#000
		la $t0, c				#004
		lb $a1, 0($t0)			#008
		jal func				#012
		move $t0, $a0			#016
		lb $a0, 0($v0)			#020
		li $v0, 1				#024
		syscall					#028
		li $v0, 10				#032
		syscall					#036
		
func: 	addi $sp, $sp, -8		#040
		sw $ra, 4($sp)			#044
		sw $s0, 0($sp)			#048
		add $v0, $a0, $zero		#052
jump56:	lb $s0, 0($v0)			#056
		beq $s0, $zero, brc76	#060
		beq $s0, $a1, brc80		#064
		addi $v0, $v0, 1		#068
		j jump56				#072
brc76:	addi $v0, $zero, 0		#076
brc80:	lw $ra, 4($sp)			#080
		lw $s0, 0($sp)			#084
		addi $sp, $sp, 8		#088
		jr $ra					#092

	