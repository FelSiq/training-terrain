.align 0
.data

str_start: .asciiz "Welcome to the MIPS ASSEMBLY STRCMP!\n"
str_getin: .asciiz "Please, type your "
str_first: .asciiz "first"
str_scond: .asciiz "second"
str_strng: .asciiz " string (max 20 characters):\n"

#strcmp(a, b): return 0 if equals, 1 if a came first with ascii order, -1 otherwise.

.align 2
.text
.globl main

main:
	ori $v0, $zero, 4
	la $a0, str_start
	syscall

	la $a0, str_first #str correspondent to this position
	jal get_string #return val. will be on $v0
	or $s0, $zero, $v0

	la $a0, str_scond #str correspondent to this position
	jal get_string #return val. will be on $v0
	or $s1, $zero, $v0

	ori $v0, $zero, 4 #print results
	or $a0, $zero, $s0
	syscall #First string typed
	or $a0, $zero, $s1
	syscall #Then the second one

	or $a0, $zero, $s0 
	or $a1, $zero, $s1 #Redundant (already made above), but just to make more clear
	jal strcmp #return will be on $v0
	or $a0, $zero, $v0

	ori $v0, $zero, 1 #Print result
	syscall

	ori $v0, $zero, 10 #end of program
	syscall

get_string:
	addi $sp, $sp, -8
	sw $a0, 0($sp)
	sw $ra, 4($sp)

	ori $v0, $zero, 4 #Print interface
	la $a0, str_getin
	syscall

	lw $a0, 0($sp) #Get the current string  position
	syscall
	
	la $a0, str_strng
	syscall

	ori $v0, $zero, 9 #malloc
	ori $a0, $zero, 21 #how many bytes? (str_size + 1 to \0)
	syscall #first byte adress of the new mem. region will be on $v0
	
	or $a0, $zero, $v0 #copy the adress of the first byte of the new mem. region to $a0
	ori $v0, $zero, 8 #read string
	or $a1, $zero, $a0 #str_size + 1 
	addi $a1, $a1, -1 #str_size
	syscall #get string
	
	or $v0, $zero, $a0	#Copy the adress of first byte
						#of the string to the return register

	lw $a0, 0($sp)
	lw $ra, 4($sp)
	addi $sp, $sp, 8
	jr $ra

strcmp:
	addi $sp, $sp, -12
	sw $a1, 0($sp)
	sw $a0, 4($sp)
	sw $ra, 8($sp)
	j loop #do not need to be jal, because it is not recursive

loop:
	lb $t0, 0($a0) #Get a character of string 1 
	lb $t1, 0($a1) #Get a character of string 2 

	beq $t0, $zero, fst_ends_check_snd #If string 1 ends, check if second ends too 
	beq $t1, $zero, snd_first #s1 is already checked. if string 2 ends, then it come first

	sub $t0, $t0, $t1 #do $t0 - $t1.
	
	bgtz $t0, snd_first #if $t0 > 0, then second string come first
	bltz $t0, fst_first #if $t0 < 0, then first string come first

	addi $a0, $a0, 1
	addi $a1, $a1, 1

	j loop #At this point, both bytes are equals. Proceed with loop.

fst_ends_check_snd:
	beq $t1, $zero, equals #At this point, if both ends together, they're equals
	j fst_first #Else, string 1 goes first

equals:
	or $v0, $zero, $zero
	j ret_to_main

fst_first:
	ori $v0, $zero, 1
	j ret_to_main

snd_first:
	addi $v0, $zero, -1
	j ret_to_main

ret_to_main:
	lw $a1, 0($sp)
	lw $a0, 4($sp)
	lw $ra, 8($sp)
	addi $sp, $sp, 12
	jr $ra