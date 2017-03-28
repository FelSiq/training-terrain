.data
.align 0

str_insertnum:	.asciiz "Please insert a number, from 1 to 999: "
str_invalid:	.asciiz "Invalid number! (must be a [1, 999] integer), try again: "
str_original:	.asciiz "Good choice! Your number was "
str_newnum:		.asciiz ", and its (digit-wise) inverse is "

.text
.align 2
.globl main

main:
	ori $v0, $zero, 4 #Print initial message
	la $a0, str_insertnum
	syscall

	jal get_number #Return value will be in $v0
	or $t0, $zero, $v0 #move v0 to t6, to hold it
	or $a0, $zero, $v0 #Copy the same number to a0, as it needs to be
	#passed as argument to reverse_number procedure (convention)

	ori $v0, $zero, 4 #Print "your original number is..." string
	la $a0, str_original
	syscall

	ori $v0, $zero, 1 #Print the previously got number
	or $a0, $zero, $t0
	syscall

	ori $v0, $zero, 4 #Print second aesthetics string
	la $a0, str_newnum
	syscall

	or $a0, $zero, $t0
	jal reverse_number

	ori $v0, $zero, 11
	ori $a0, $zero, 10
	syscall

	ori $v0, $zero, 10 #No mystery here
	syscall
	#End of program.

get_number:
	addi $sp, $sp, -4 #Stack return value
	sw $ra, 0($sp)
	#Next procedure are already below, no need for jump
my_scanf:
	ori $v0, $zero, 5 #Get the input integer
	syscall

	#The below instructions works only with "0" value as comparator
	#So, a "value shift" must be done, so all comparations will make sense
	addi $t0, $v0, -1
	bltz $t0, invalid_entry # $v0 - 1 < 0 ? <=> $v0 < 1 ?
	
	addi $t0, $v0, -1000
	bgez $t0, invalid_entry # $v0 - 1000 >= 0 ? <=> $v0 >= 1000 ?

	#At this point, entry is valid. Get the return value,
	#previously stacked, and return to main.
	j pop_stack

invalid_entry: #This is an auxiliary "procedure" of my_scanf
	ori $v0, $zero, 4 #Print a invalid warning string
	la $a0, str_invalid
	syscall
	j my_scanf #Return to my_scanf

reverse_number: #Argument is in $a0, return must be in $v0
	or $v0, $zero, $zero #Clean v0
	ori $s0, $zero, 10 #This is the base

	j reverse_number_rec

reverse_number_rec:
	addi $sp, $sp, -8
	sw $a0, 0($sp)	#Stack argument a0
	sw $ra, 4($sp) 	#Stack return address

	addi $t0, $a0, -1
	bgezal $t0, div_num_by_base #If a0 >= 1, div by 10, til its < 1 

	j pop_argument

div_num_by_base:
	divu $a0, $s0

	ori $v0, $zero, 1 #Print the number call's correspondent digit
	mfhi $a0
	syscall

	mflo $a0
	j reverse_number_rec 

pop_argument:
	lw $a0, 0($sp) #Get argument from stack
	addi $sp, $sp, 4 #Move stack pointer 4 bytes

	j pop_stack

pop_stack:
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra #return to or main (if input is valid) or (else) get_number