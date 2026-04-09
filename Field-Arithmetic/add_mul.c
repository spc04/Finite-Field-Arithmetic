#include <stdio.h>
#include <stdint.h>

#include "convert.h"
#include "add_mul.h"

	
void main () {

	unsigned char a[32] = {245, 239, 233, 127, 91, 131, 76, 97, 58, 4, 234, 206, 200, 190, 85, 148, 101, 114, 19, 158, 196, 253, 42, 8, 138, 28, 40, 111, 173, 64, 46, 233};
	
	uint32_t a2[9] = {1072884297, 234788477, 1071143369, 645135995, 308381912, 625658372, 681080647, 420847953, 8057};
//	unsigned char a0[32] = {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	uint32_t a3[9] = {221788647, 802085326, 989860352, 324773810, 853657793, 339168765, 75237856, 562218955, 1073711976};
	
	uint32_t p[9] = {1072295925, 87166317, 782255014, 359641651, 326264212, 737612408, 29925506, 271277002, 59694};
	
	uint32_t b[9], b0[9], c[9], s[9], s1[9], d[18];
	
	
	
	base_8_to_30(a,b);
//	base_8_to_30(a0,b0);
	printf("\n\nThe value of 'a' in base 2^30 is :\n");
	printVal_32(b,9);
	
	printf("\n\nThe value of 'a2' in base 2^30 is :\n");
	printVal_32(a2,9);
	
	add(b,b,c);
	printf("\n\nThe Value of the Addition is :\n");
	printVal_32(c,9);
	
	mul(b,b,d);
	printf("\n\nThe Value of the Multiplication is :\n");
	printVal_32(d,18);

	sub(p,a3,s1);
	printf("\n\nThe Value of the DH Subtraction is :\n");
	printVal_32(s1,9);
	
	sub4ecc(a2,b,s);
	printf("\n\nThe Value of the ECC Subtraction is :\n");
	printVal_32(s,9);

}	
	
