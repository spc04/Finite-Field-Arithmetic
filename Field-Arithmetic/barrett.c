#include<stdio.h>
#include<stdint.h>

#include "barrett.h"

void main () {

//	unsigned char a[32] = {242, 239, 233, 127, 91, 131, 76, 97, 58, 4, 234, 206, 200, 190, 85, 148, 101, 114, 19, 158, 196, 253, 42, 8, 138, 28, 40, 111, 173, 64, 46, 233}; 
	
//	uint32_t a2[9] = {1072884297, 234788477, 1071143369, 645135995, 308381912, 625658372, 681080647, 420847953, 8057};
	
	uint32_t b[9], d[18], red[9];
	
//	uint32_t a2[9] = {0,0,0,0,256,0,0,0,0};

	uint32_t a2[9] = {0,0,0,0,0,0,0,0,1024};
	
//	base_8_to_30(a,b);
	
//	mul(b,a2,d);
	mul(a2,a2,d);
	printf("\n\nThe Value of the Multiplication is :\n");
	printVal_32(d,18);

	bar_red(d,red);
	printf("\n\nThe REDUCED Value of the Multiplication is :\n");
	printVal_32(red,9);



}
