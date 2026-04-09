#ifndef ECC_SCAL_MULT
#define ECC_SCAL_MULT


#include <stdio.h>
#include <stdint.h>

#include "ecc_base.h"

point ECC_L2R_mult (point P, uint8_t *n) { // Left-to-Right Scalar Multiplication.
	
	point Q = P;

	uint8_t b;
	int l=len(n);
	
	for (int i=l-2; i>=0; i--) { // Considering the fact that the MSB of "n" is 1.
		Q = doubling(Q);
		b = (n[(i/8)] >> (i%8)) & (uint8_t)1;
		while (b==1) {
			Q = addition(P,Q);
			break;
			}
		}
	return Q;
	}
	
	
point ECC_R2L_mult (point P, uint8_t *n) { // Right-to-Left Scalar Multiplication.
	
	point Q = P;
		
	point P1 = doubling(P);
		
	uint8_t b;
	int l=len(n);

	for (int i=1; i<l; i++) { // Considering the fact that the LSB of "n" is 1.
		b = (n[(i/8)] >> (i%8)) & (uint8_t)1;
		while (b==1) {
			Q = addition(P1,Q);
			break;
			}
		P1 = doubling(P1);
		}
	return Q;
	}


point ECC_montgomeryLadder_mult (point P, uint8_t *n) { // Montgomery Ladder Scalar Multiplication.
	
	point S, R;
	
	S = P;
	R = doubling(P);

	uint8_t b;
	int l=len(n);
	for (int i=l-2; i>=0; i--) {
		b = (n[(i/8)] >> (i%8)) & (uint8_t)1;
		if (b==0) {
			R = addition(S,R);
			S = doubling(S);
			}
		else {
			S = addition(S,R);
			R = doubling(R);
			}
		}
	return S;
	}	


point ECC_antiSC_montgomeryLadder_mult (point P, uint8_t *n) { // Constant Time Montgomery Ladder Scalar Multiplication.
	
	point R[2];
	
	R[0] = P;
	R[1] = doubling(P);
	
	uint8_t b;
	int l=len(n);
	for (int i=l-2; i>=0; i--) {
		b = (n[(i/8)] >> (i%8)) & (uint8_t)1;
		
		R[1-b] = addition(R[0],R[1]);
		
		R[b] = doubling(R[b]);
		}
	
	return R[0];
	}

#endif

