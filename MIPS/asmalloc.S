.data
.align 0

.text
.globl main
.align 2

main:
	ori $v0, $zero, 9 #Malloc
	addi $a0, $zero, 20 #How many (to malloc)
	syscall

	or $a1, $zero, $a0 #How many (to get string)
	or $a0, $zero, $v0 #First dynamic adress byte
	ori $v0, $zero, 8 #Get String
	syscall

	ori $v0, $zero, 4 #Print string
	syscall

	addi $v0, $zero, 10 #Exit
	syscall