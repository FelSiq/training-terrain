.data
.align 0

str_first: 		.asciiz "Type a string to copy: "
str_result: 	.asciiz "Result: "

.text
.globl main
.align 2

main:
	ori $v0, $zero, 4 #Print first string
	la $a0, str_first
	syscall

	ori $v0, $zero, 9 #Malloc
	ori $a0, $zero, 20 #How much (to malloc)
	syscall

	or $a1, $zero, $a0 #How much (to get string)
	or $a0, $zero, $v0 #First dynamic adress byte
	ori $v0, $zero, 8 #Get String
	syscall

	or $a1, $zero, $a0 #save dynamic adress
	ori $v0, $zero, 4 #Print second string
	la $a0, str_result
	syscall

	or $a0, $zero, $a1 #Argument to strcpy
	ori $a1, $zero, 20 #Argument to strcpy
	jal strcpy #return will be on $v0

	or $a0, $zero, $v0 #to print result
	ori $v0, $zero, 4 #Print string
	syscall

	ori $v0, $zero, 10 #Exit
	syscall

strcpy:
	or $s0, $zero, $a0 #save the argument
	or $a0, $zero, $a1 #how much? (malloc)
	ori $v0, $zero, 9 #malloc
	syscall
	#start loops

loop:
	addi $sp, $sp, -12
	sw $v0, 8($sp) #Current byte of newstring ("index")
	sw $s0, 4($sp) #Original string
	sw $ra, 0($sp) #return adress

	lb $t0, 0($s0) #Fetch the current byte value to a temporary register
	sb $t0, 0($v0) #Copy this character to the $v0 memory region
	addi $s0, $s0, 1 #Move both pointers
	addi $v0, $v0, 1
	beq $t0, $zero, pop_stack #if we're on a null byte, begin returning
	jal loop; #Starts a new call

pop_stack:
	lw $ra, 0($sp)
	lw $s0, 4($sp) #Original string
	lw $v0, 8($sp) #Current byte of newstring ("index")
	addi $sp, $sp, 12 #Return stack pointer
	jr $ra #Return to where $ra points to