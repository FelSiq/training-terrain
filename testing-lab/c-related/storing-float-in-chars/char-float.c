#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

	char *buffer = malloc(sizeof(float) * 3);

	float *aux_pointer = (float *) buffer;

	aux_pointer[0] = 3.565;
	aux_pointer[1] = 0.098;
	aux_pointer[2] = 4.009;

	for (int i = 0; i < 3; i++)
		printf("%.4f\n", aux_pointer[i]);

	free(buffer);

	return 0;
}
