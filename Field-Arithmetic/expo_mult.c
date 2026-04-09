#include <stdio.h>
#include <stdint.h>

#include "barrett.h"
#include "expo_mult.h"

void main () {

	uint32_t g[9] = {2, 0, 0, 0, 0, 0, 0, 0, 0}; // g = 2 is the smallest primitive element in our field.

//	unsigned char n[32] = {244, 239, 233, 127, 91, 131, 76, 97, 58, 4, 234, 206, 200, 190, 85, 148, 101, 114, 19, 158, 196, 253, 42, 8, 138, 28, 40, 111, 173, 64, 46, 233}; // n = p-1 (245 is changed to 244 in n[0]).

//	unsigned char n[32] = {244,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	unsigned char n[32] = {244,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // = 500
	
	uint32_t h1[9], h2[9], S1[9], S2[9];
	
	L2R_mult(g,n,h1);
	printf("\n\nThe Value of the L2R Exponent Multiplication is :\n");
	printVal_32(h1,9);
	
	R2L_mult(g,n,h2);
	printf("\n\nThe Value of the R2L Exponent Multiplication is :\n");
	printVal_32(h2,9);

	montgomeryLadder_mult(g,n,S1);
	printf("\n\nThe Value of the Montgomery Ladder Exponent Multiplication is :\n");
	printVal_32(S1,9);
	
	antiSC_montgomeryLadder_mult(g,n,S2);
	printf("\n\nThe Value of the Constant Time Montgomery Ladder Exponent Multiplication is :\n");
	printVal_32(S2,9);

	
}
