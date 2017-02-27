all: secret.o static.o 
	gcc secret.o static.o -o static -Wall
secret.o:
	gcc -c secret.c -Wall
static.o:
	gcc -c static.c -Wall