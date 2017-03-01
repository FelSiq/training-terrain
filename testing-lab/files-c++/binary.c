#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]){

	//Step 1:
	if (argc > 1 && atoi(*(argv + 1)) == 1){
		FILE *fp = fopen("test.out", "wb+");

		int mystr[] = {154, 255, 254, 241, 105};
		for (int i = 0; i < 5; ++i){
			fwrite((int *) (mystr + i), sizeof(unsigned char), 1, fp);
		}
		fclose(fp);
		return 0;
	}

	//Step 2
	FILE *fp = fopen("test.out", "rb+");

	int myvec[5];

	for(int i = 0; i < 5; i++){
		unsigned char c;
		fread(&c, sizeof(unsigned char), 1, fp);
		*(myvec + i) = (int) c;
		printf("%d\n", *(i + myvec));
	}

	fclose(fp);

	
	return 0;
}
