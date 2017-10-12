#include <stdio.h>

static void secretFunction(){
	printf("This function could've not be acessed from outside!\n");
}

void *exportSecretFunction(){
	void (*bridge)(void) = &secretFunction;
	return bridge;
};