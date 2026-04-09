#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "ecc_scal_mult.h"

void main () {


//	uint32_t x1[9] = {803962312, 409413677, 256738554, 1020529939, 38059069, 186749830, 328324139, 213063295, 48620};
//	uint32_t y1[9] = {194309060, 790722087, 911865161, 380062496, 999754684, 570004311, 1061320730, 735814692, 42904};
//	uint32_t x2[9] = {228102662, 448937746, 865582717, 742032413, 1054372417, 891721772, 597754570, 729750614, 57807};
//	uint32_t y2[9] = {594183587, 26911241, 648096860, 78556742, 423959017, 536679052, 544891743, 397642524, 29321};
	uint32_t x3[9] = {117299018, 545396564, 749397616, 1055885694, 518541596, 444951148, 910863549, 918852316, 21673};
	uint32_t y3[9] = {846748191, 39260932, 865268888, 53265722, 483056936, 600885842, 734463786, 1013536853, 40764};
	
	
//	unsigned char n[32] = {244, 239, 233, 127, 91, 131, 76, 97, 58, 4, 234, 206, 200, 190, 85, 148, 101, 114, 19, 158, 196, 253, 42, 8, 138, 28, 40, 111, 173, 64, 46, 233}; // n = p-1 (245 is changed to 244 in n[0]).
	
	unsigned char n[32] = {243, 239, 233, 127, 91, 131, 76, 97, 58, 4, 234, 206, 200, 190, 85, 148, 101, 114, 19, 158, 196, 253, 42, 8, 138, 28, 40, 111, 173, 64, 46, 233}; // n = p-2 (245 is changed to 243 in n[0]). To make sure that both the LSB and the MSB are 1 for compatibility of R2L and L2R Multiplication respectively.

	point P;
	for (int i=0; i<=8; i++) {
		P.x[i] = x3[i];
		P.y[i] = y3[i];
		}

	if (inCurve(P) == 0) {
		printf("\n!!! Error : Point P is not on the Curve. !!!\n");
        	exit(EXIT_FAILURE); // !!! To terminate the ECC program due to invalid inputs !!!
		
		} // Checking whether P is a point of the curve.
		
	uint32_t zero[9] = {0,0,0,0,0,0,0,0,0};
	if (isEqual(P.y,zero) == 1) {
		printf("\n!!! Error : Asked to do undefined operations. !!!\n");
        	exit(EXIT_FAILURE); // To terminate the program due to invalid input.
        	}	
	
	point nP1, nP2, nP3, nP4;
	
	nP1 = ECC_L2R_mult(P,n);
	printf("\n\nThe Value of the L2R ECC Scalar Multiplication is :\n");
	printPoint(nP1);
	
	nP2 = ECC_R2L_mult(P,n);
	printf("\n\nThe Value of the R2L ECC Scalar Multiplication is :\n");
	printPoint(nP2);
	
	nP3 = ECC_montgomeryLadder_mult(P,n);
	printf("\n\nThe Value of the Montgomery Ladder ECC Scalar Multiplication is :\n");
	printPoint(nP3);
	
	nP4 = ECC_antiSC_montgomeryLadder_mult(P,n);
	printf("\n\nThe Value of the Constant Time Montgomery Ladder ECC Scalar Multiplication is :\n");
	printPoint(nP4);
		
	
}
