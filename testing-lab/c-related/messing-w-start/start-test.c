#include <stdlib.h>
#include <stdio.h>
// Compile: gcc start-test.c -nostartfiles

int fastcall() {
	return fwrite("Hello World!\n", sizeof(char), 13, stdout) <= 0;
}

void _start() {
	exit(fastcall());
}
