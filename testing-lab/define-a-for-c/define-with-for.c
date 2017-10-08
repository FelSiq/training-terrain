#include <stdio.h>
#define loop(A, B) for(unsigned a = B; a--; A);
int main(int argc, char const *argv[]) {
	// You can set the content of a for whenever you want with the help of a define
	loop((printf("Sure!"), printf("A!"), printf("B!")), 4);
	loop((printf("Haha!"), printf("D!")), 2);
	loop(printf("\nFunny!"), 3);
	return 0;
}
