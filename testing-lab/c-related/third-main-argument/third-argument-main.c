#include <stdio.h>
int main(int argc, char *const argv[], char *envp[]) {

	/*
		"Secretly" the main function has three arguments.
	*/

	int counter = 0;
	while (envp[counter]) {
		printf("%s\n", envp[counter++]);
	}
}
