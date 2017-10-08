#include <stdio.h>
int main(int argc, char const *argv[]){
	for (struct {
		int a;
		float b;
		char s[30];
	} a_lovely_struct = {
		.a = 30,
		.b = 0x1.5p+10,
		.s = "I can't record last time I...\0"
	}; a_lovely_struct.a--; printf("%.3f\t%c\n", a_lovely_struct.b = ~(signed) a_lovely_struct.b ^ 1, *(a_lovely_struct.s + a_lovely_struct.a)));

	return 0;
}

// Conclusions:
// You can declare structs inside for loops.
// Hexadecimal floating point structure:
// -	0xA.B[pP]C
// -	Where: 
// 		A.B is the "significant part", i.e, A is the integer part and B the fraction part
// 		C is the exponential of base 2 (2 because hexadecimal: if decimal, then the base is 10).
// 		The real value is hex(A.B) * 2^C
// (base ten [eE] does not seens to work with hexadecimals, reciprocally, the base two [pP] does not seens to work with decimals)
// Interesting: the octal modifier (0A) seens to be ignored on floating points (0A.B == A.B).