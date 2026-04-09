#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#include "ecc_base.h"



void main () {

//	uint32_t x1[9] = {803962312, 409413677, 256738554, 1020529939, 38059069, 186749830, 328324139, 213063295, 48620};
//	uint32_t y1[9] = {194309060, 790722087, 911865161, 380062496, 999754684, 570004311, 1061320730, 735814692, 42904};
	uint32_t x2[9] = {228102662, 448937746, 865582717, 742032413, 1054372417, 891721772, 597754570, 729750614, 57807};
	uint32_t y2[9] = {594183587, 26911241, 648096860, 78556742, 423959017, 536679052, 544891743, 397642524, 29321};
	
	uint32_t x1[9] = {117299018, 545396564, 749397616, 1055885694, 518541596, 444951148, 910863549, 918852316, 21673};
	uint32_t y1[9] = {846748191, 39260932, 865268888, 53265722, 483056936, 600885842, 734463786, 1013536853, 40764};

	point P, Q, R1, R2;
	for (int i=0; i<=8; i++) {
		P.x[i] = x1[i];
		P.y[i] = y1[i];
		Q.x[i] = x2[i];
		Q.y[i] = y2[i];
		}
	
//	printf("P.x = ");
//	printVal_32(P.x,9);
//	printf("P.y = ");
//	printVal_32(P.y,9);
//	printf("Q.x = ");
//	printVal_32(Q.x,9);
//	printf("Q.y = ");
//	printVal_32(Q.y,9);
	
	if (inCurve(P) == 0 || inCurve(Q) == 0) {
		printf("\n!!! Error : Point(s) not on the Curve. !!!\n");
        	exit(EXIT_FAILURE); // !!! To terminate the ECC program due to invalid inputs !!!
		
		} // Checking whether P and Q are points of the 
		
		
	if (isEqual(P.x,Q.x) == 1) {
		printf("\n!!! Error : Asked to do undefined operations. !!!\n");
	       	exit(EXIT_FAILURE); // To terminate the program due to invalid inputs.
		
		} // If these are points on the Elliptic Curve, only checking equality for the x-coordinate suffices.
	
	R1 = addition(P,Q);
	printf("\n\nThe Value of P+Q is :\n");
	printPoint(R1);
	
	
	
	uint32_t zero[9] = {0,0,0,0,0,0,0,0,0};
	if (isEqual(P.y,zero) == 1) {
		printf("\n!!! Error : Asked to do undefined operations. !!!\n");
        	exit(EXIT_FAILURE); // To terminate the program due to invalid input.
        	
        	} // P is a point on the curve whose y-coordinate is 0. That means P =-P.
	
	R2 = doubling(P);
	printf("\n\nThe Value of 2P is :\n");
	printPoint(R2);
	
	


}
