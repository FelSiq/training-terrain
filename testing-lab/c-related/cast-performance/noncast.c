#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int *list;
	float key;
} item;

#define N 10000000

void func (item *p) {
	for (int i = 0; i < N; i++) {
		*p[i].list = i;
		p[i].key = 1.0 * i;
	}
}

int main(int argc, char *argv[]) {

	item *data = malloc(sizeof(item) * N);
	for (int i = 0; i < N; i++)
		data[i].list = malloc(sizeof(int));

	func(data);

	for (int i = 0; i < N; i++)
		free(data[i].list);

	free(data);

	return 0;
}

