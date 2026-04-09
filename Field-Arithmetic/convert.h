#ifndef CONVERT
#define CONVERT



#include <stdio.h>
#include <stdint.h>


void printVal_8 (uint8_t *x, int n) {
	
	printf("\n");
	for (int i=n-1;i>=0;i--) printf("%d ", x[i]);
	printf("\n");
	}	

void printVal_32 (uint32_t *x, int n) {
	
	printf("\n");
	for (int i=n-1;i>=0;i--) printf("%u ", x[i]);
	printf("\n");
	}	


uint32_t leftShift_32 (uint32_t x, int n) {
	
	uint32_t y=0;
	while (n<32) {
		y = x << n;
		break;
		}
	return y;
	}	

uint32_t rightShift_32 (uint32_t x, int n) {
	
	uint32_t y=0;
	while (n<32) {
		y = x >> n;
		break;
		}
	return y;
	}	


void base_8_to_30 (uint8_t a[32], uint32_t a1[9]) {
	
	int c=0;
	uint32_t b=0;
	uint32_t b4=0;
	for (int i=0; i<8; i++) {
		
		a1[i] = b4;
		for (int j=0; j<4; j++) {
			b = leftShift_32((uint32_t) a[c+j], (8*j)+(i*2));
			a1[i] ^= b;
			}

		a1[i] = (a1[i] << 2) >> 2;

		
		while ((6-(i*2)) >= 0) {
			b4 = ((uint32_t) a[c+3]) >> (6-(i*2));
			break;
			}
		while ((6-(i*2)) < 0) {
			b4 = ((uint32_t) a[c+3]) << -(6-(i*2));
			b = ((uint32_t) a[c+2]) >> (8 + (6-(i*2)));
			b4 ^= b;
			break;
			}
		
		c = c+4;
		}
	
	a1[8] = b4;
	
	}
	
	
void base_30_to_8 (uint32_t a[9], uint8_t a1[32]) {
	
	uint32_t b=0, k;
	
	b = a[0];
	for (int i=0; i<8; i++) {
		
		for (int j=0; j<4; j++) {
			k = rightShift_32(b, (8*j)+(2*i));
			a1[(4*i)+j] = (uint8_t) k;
			}
		
		b = a[i+1];
		
		while ((8-(2*(i+1))) >= 0) {
			a1[(4*i)+3] = a1[(4*i)+3] ^ (uint8_t) ((b << (8-(2*(i+1)))));
			break;
			}
		
		while ((8-(2*(i+1))) < 0) {
			a1[(4*i)+2] = a1[(4*i)+2] ^ (uint8_t) ((b << (8+(8-(2*(i+1))))));
			a1[(4*i)+3] = (uint8_t) ((b >> -(8-(2*(i+1)))));
			break;
			}
		
		}
	
	}	
	
#endif	

