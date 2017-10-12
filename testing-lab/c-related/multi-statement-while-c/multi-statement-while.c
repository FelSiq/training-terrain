#include <stdio.h>

int main(int argc, char const *argv[]){
	
	while (printf("This happens.\n"), printf("This too.\n"), 0 == 1);

	// while (int a = 5, a > 0) printf("%d\t", --a);
	// error: expected expression before ‘int’

	// int a;
	// while (a = 5, printf("How many prints?"), a > 0) printf("%d\t", a--);
	// Infinite loop: all the while statements are executed each iteration.

	// while (a = 3, for (char c = 0; c < 10; ++c), printf("a value = %d\n", a), a-- > 0);
	// while (for (char c = 0; c < 10; ++c), a = 3, printf("d value = %d\n", a), a-- > 0);
	// error: expected expression before ‘for’ (both)

	// while (struct {int n; float m; char s[5];} str = {.n = 1, .m = 5, .s = "haha\0"}, str.n < str.m) ++str.n;
	// error: expected expression before ‘struct’

	int a = 5;
	while (printf("%d\n", a--), a > 0);

	// while(while(1 == 0) printf("Double while!\n"), 1 == 0);
	// error: expected expression before ‘while’

	// while(if (1 == 1) while(1 == 0) printf("Double while!\n"), 1 == 0);
	// error: expected expression before ‘if’

	a = 5;
	while (1 == a % 2 ? printf("A") : printf("B"), --a > 0);
	while (-1 == ~0 ? printf("C") : printf("D"), 1 == 2);

	// while(-1 == -1 ? (printf("Infinite loop??\n"), 1 == 1) : (printf("Does not happens.\n"), 1 == 0));
	// It works, and creates a infinite loop.

	a = 20;
	while (printf("\na = %d\n", a), a % 2 ? (a -= 2, a > 0) : (a++, 1 == 1));

	return 0;
}

// Conclusions:
// - While loops can have more than two statements, separated by a comma.
// - All while statements are executed on each while iteration: setting up a value to a index is generally not a good idea.
// - Is not possible declare variables on a while statement.
// - Is not possible define and declare structs on a while statement.
// - Is not possible declare a for loop within a while statement.
// - Is not possible declare a while within a while
// - Is not possible declare a if within a while
// - It IS possible to use a ternary operator within a while statement.
// - It IS possible to manipulate the while main condition with a ternary operator.