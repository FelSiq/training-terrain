.data	#DATA SEGMENT
.align 0	#2^0 = 1 byte
str_first:	.asciiz "BubreSorti Assembly implementation!\n"
str_vsize:	.asciiz "\tsize of vector: "
str_endl:	.asciiz "\n"
str_empty:	.asciiz " "

.text
.align 2	#2^2 = 4 bytes
#Plot twist: on SPIM, text section starts at "00400000" logic adress
.globl main

bubble:		#Bbort function
	addi $sp, $sp, -4 		#move stack pointer
	sw	$ra, 0($sp)			#store return value

	#Read-from-stack sector
	lw $t7, 4($sp) 			#Read v size from stack

	#Bubble Sort sector
	move $s2,$t7			#size constant
	addi $s3, $s2, -1		#size - 1 constant
	li $s0, 0				#This will be the i index on BubbleSort

	jal loop_entry			#outter loop call

	lw $ra, 0($sp)			#Recover return value
	addi $sp, $sp, 4		#move stack pointer
	jr $ra					#jump with register value

loop_entry:					#Function to entry the main loop of bubble sort
	addi $sp, $sp, -4
	sw $ra, 0($sp)			#Store return value
	j loop_extern;

loop_extern: 				#bubble sort loop 1
	bge $s0, $s3, loop_end	#if i >= size - 1, end BubbleSort outer loop
	addi $s0, $s0, 1 		#++i
	li $s1, 0				#This will be the BubbleSort j

loop_intern: 					#bubble sort loop 2
	bge $s1, $s3, loop_extern	#if j >= size-1

	addi $t2, $zero, 4;		#Create a constant 4
	move $t0, $s1 			#Move the j index to a temp register
	addi $t0, $t0, 2		#Add 1 to the register
	mul $t0, $t0, $t2		#Mult the current index by 4 (sizeof(int))

	add $t0, $t0, $sp		#Add the temp calculated value to the stack pointer value
	move $t1, $t0			#Copy this adress to a another temp register
	addi $t1, $t1, 4		#This will be index + 1 on BubbleSort

	move $s4, $t0			#Save the adress value of j
	move $s5, $t1			#Save the adress value of j + 1
	lw $a2, 0($s4)			#Fetch the correct j value
	lw $a3, 0($s5)			#Fetch the corrent j + 1 value

	addi $s1, $s1, 1 		#++j
	bgt $a2, $a3, swap
	j loop_intern

swap:
	#Current setup: 
	#	adress of vec[j]: $s4 	/ adress of vec[j + 1]: $s5
	#	value of vec[j]: $a2	/ value of vec[j + 1]: $a3
	sw $a2, 0($s5)			#Set the value of vec[j + 1] = vec[j]
	sw $a3, 0($s4)			#Set the value of vec[j] = vec[j + 1]
	j loop_intern

loop_end:				#Ends loop
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra

print_res:				#To print a single integer, with post spacebar
	li $v0, 1
	syscall
	li $v0, 4
	la $a0, str_empty
	syscall
	jr $ra

main:					#Main function
	li $v0, 4			#To print introduction text
	la $a0, str_first
	syscall

	addi $sp, $sp, -28	#Move the stack pointer (stack allocation)
	
	li $t0, 7			#Store v[0]
	li $t1, 5			#Store v[1]
	li $t2, 2			#Store v[2]
	li $t3, 1			#Store v[3]
	li $t4, 1			#Store v[4]
	li $t5, 3			#Store v[5]
	li $t6, 4			#Store v[6]
	li $t7, 7			#Store v size

	sw	$t7, 28($sp)	#Stack in 7
	sw	$t6, 24($sp)	#Stack in 7
	sw	$t5, 20($sp)	#Stack in 5
	sw	$t4, 16($sp)	#Stack in 2
	sw	$t3, 12($sp)	#Stack in 1
	sw	$t2, 8($sp)		#Stack in 1
	sw	$t1, 4($sp)		#Stack in 3
	sw	$t0, 0($sp)		#Stack in 4

	jal bubble	#jump-and-link to bubble

	lw	$t0, 0($sp)		#Stack in 4
	lw	$t1, 4($sp)		#Stack in 3
	lw	$t2, 8($sp)		#Stack in 1
	lw	$t3, 12($sp)	#Stack in 1
	lw	$t4, 16($sp)	#Stack in 2
	lw	$t5, 20($sp)	#Stack in 5
	lw	$t6, 24($sp)	#Stack in 7
	lw	$t7, 28($sp)	#Stack in 7
	addi $sp, $sp, 28	#move stack pointer

	li $v0, 4
	la $a0, str_endl
	syscall

	move $a0, $t0
	jal print_res
	move $a0, $t1
	jal print_res
	move $a0, $t2
	jal print_res
	move $a0, $t3
	jal print_res
	move $a0, $t4
	jal print_res
	move $a0, $t5
	jal print_res
	move $a0, $t6
	jal print_res
	
	li $v0, 4			#To print vector size
	la $a0, str_vsize
	syscall
	li $v0, 1	
	move $a0, $t7
	syscall

	li $v0, 10			#exit
	syscall 			#end of program