#ifndef EXPO_MULT
#define EXPO_MULT


#include <stdio.h>
#include <stdint.h>

#include "barrett.h"


//uint32_t g[9] = {2, 0, 0, 0, 0, 0, 0, 0, 0}; // g = 2 is the smallest primitive element in our field.

int len(uint8_t *n) { // to get the binary length of n.

	uint32_t n1[8];
	base_8_to_30(n,n1);
	shrink(n1,p);

	base_30_to_8(n1,n); // For faster computation, we can omit upto this if the input "n" always lies between 0 and p-1.

	int i=31;
	while(n[i] == 0) {
		i--;
		}
	int a=n[i], k=8;
	while (a < 128) {
		a = a<<1;
		k--;
		}
	return ((i*8)+k);

	}



void L2R_mult (uint32_t *g, uint8_t *n, uint32_t *h) { // Left-to-Right Exponentiation.

	h[0] = 1;
	for (int i=1;i<=8;i++) h[i] = 0;

	uint32_t H[18];
	uint8_t b;
	int l=len(n);

	for (int i=l-1; i>=0; i--) {
		mul(h,h,H);
		bar_red(H,h);

		b = (n[(i/8)] >> (i%8)) & (uint8_t)1;
		while (b==1) {
			mul(h,g,H);
			bar_red(H,h);
			break;
			}
		}

	}


void R2L_mult (uint32_t *g, uint8_t *n, uint32_t *h) { // Right-to-Left Exponentiation.

	h[0] = 1;
	for (int i=1;i<=8;i++) h[i] = 0;

	uint32_t g1[9];
	for (int i=0;i<=8;i++) g1[i] = g[i];

	uint32_t H[18];
	uint8_t b;
	int l=len(n);

	for (int i=0; i<l; i++) {
		b = (n[(i/8)] >> (i%8)) & (uint8_t)1;
		while (b==1) {
			mul(h,g1,H);
			bar_red(H,h);
			break;
			}
		mul(g1,g1,H);
		bar_red(H,g1);
		}
	}


void montgomeryLadder_mult (uint32_t *g, uint8_t *n, uint32_t *S) { // Montgomery Ladder Exponentiation.

	uint32_t R[9], X[18];

	for (int i=0;i<=8;i++) S[i] = g[i];
	mul(g,g,X);
	bar_red(X,R);

	uint8_t b;
	int l=len(n);
	for (int i=l-2; i>=0; i--) {
		b = (n[(i/8)] >> (i%8)) & (uint8_t)1;
		if (b==0) {
			mul(S,R,X);
			bar_red(X,R);

			mul(S,S,X);
			bar_red(X,S);
			}
		else {
			mul(S,R,X);
			bar_red(X,S);

			mul(R,R,X);
			bar_red(X,R);
			}
		}

	}


void antiSC_montgomeryLadder_mult (uint32_t *g, uint8_t *n, uint32_t *S) { // Constant Time Montgomery Ladder Exponentiation.

	uint32_t R[2][9], X[18];

	for (int i=0;i<=8;i++) R[0][i] = g[i];
	mul(g,g,X);
	bar_red(X,R[1]);

	uint8_t b;
	int l=len(n);
	for (int i=l-2; i>=0; i--) {
		b = (n[(i/8)] >> (i%8)) & (uint8_t)1;

		mul(R[0],R[1],X);
		bar_red(X,R[1-b]);

		mul(R[b],R[b],X);
		bar_red(X,R[b]);
		}

	for (int i=0;i<=8;i++) S[i] = R[0][i];
	}



#endif

