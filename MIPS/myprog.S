.data	#GLOBAL DECLARATION DIRECTIVE
.align	0	#2^0 = 1 byte
str_hello:	.asciiz	"Hell on world!"

.text	#SOURCE CODE DECLARATION DIRECTIVE
.align 2 #2^2 = 4 bytes
.globl main	#main now is extern

main:	#The next function will be the first one to be executed on SPIM
	li $v0, 4	#To Print string syscall (Syscall ID must be in v0)
	la $a0, str_hello	#To print str_hello (non-float arguments must be in a*)
	syscall

	li $v0, 10	#exit
	syscall #end of program