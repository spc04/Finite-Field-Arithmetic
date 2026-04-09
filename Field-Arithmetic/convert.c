#include <stdio.h>
#include <stdint.h>

#include "convert.h"


void main () {

	unsigned char a[32] = {245, 239, 233, 127, 91, 131, 76, 97, 58, 4, 234, 206, 200, 190, 85, 148, 101, 114, 19, 158, 196, 253, 42, 8, 138, 28, 40, 111, 173, 64, 46, 233};
	uint32_t b[9];
	uint8_t a1[32];
	
	base_8_to_30(a,b);
	printf("\n\nThe value in base 2^30 is :\n");
	printVal_32(b,9);
	
	base_30_to_8(b,a1);
	printf("\n\nThe value in base 2^8 is :\n");
	printVal_8(a1,32);
	

}



