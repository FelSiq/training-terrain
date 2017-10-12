#include <stdio.h>

struct myBelovedStruct {
	char a[3];
	short int b;
	int c;
} __attribute__((packed));

typedef struct myBelovedStruct myBelovedStruct;

int main(int argc, char const *argv[]){
	myBelovedStruct mbs = {"ABC", 0x123, 0x456789AB};

	printf("size: %lu\n", sizeof(myBelovedStruct));

	for (unsigned char *beholder = (unsigned char *) &mbs; 
		beholder < (unsigned char *) &mbs + sizeof(myBelovedStruct); 
		printf("%x ", *beholder++))
		if (!(((unsigned long int) beholder) % 4)) printf("\n");

	return 0;
}