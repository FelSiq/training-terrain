#include <stdio.h>

#ifdef DEBUG
	printf("This code will be removed.\n");
#endif

int main(int argc, char const *argv[]){
	char string[] = "Hell on world!";
	printf("%s\n", string);

	return 0;
}