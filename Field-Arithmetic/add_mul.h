#ifndef ADD_MUL
#define ADD_MUL

#include <stdio.h>
#include <stdint.h>

#include "convert.h"


uint32_t p[9] = {1072295925, 87166317, 782255014, 359641651, 326264212, 737612408, 29925506, 271277002, 59694}; // The 2^30 base representation of prime p.


void printVal_64 (uint64_t *x, int n) {
	
	printf("\n");
	for (int i=n-1;i>=0;i--) printf("%lu ", x[i]);
	printf("\n");
	}	
	
	

void add (uint32_t a[9], uint32_t b[9], uint32_t c[9]) {
	
	c[0] = 0;
	
	for (int i=0; i<8; i++) {
		
		c[i] += (a[i] + b[i]);
		
		c[i+1] = c[i] >> 30; // To counter the overflow.
		
		c[i] = (c[i] << 2) >> 2;
		
		}
	
	c[8] += (a[8] + b[8]);
	
	}
	

void sub_com (uint32_t a[9], uint32_t b[9], uint32_t c[9]) { // Common part of subtraction used in both DH and ECC.
	c[0] = 0;
	for (int i=0; i<8; i++) {
		while (a[i]>=b[i]) {
			c[i] = a[i] - b[i];
			break;
			}
		while (a[i]<b[i]) {
			a[i+1] -= 1;
			int k=i;
			while (a[k+1]==-1 && (k+1)<8) {
				a[k+1] = (a[k+1] << 2) >> 2;
				a[k+2] -= 1;
				k++;
				}			
			c[i] = (((uint32_t)1 << 30) + a[i]) - b[i];
			
			break;
			}	
		}
	}

void sub (uint32_t a[9], uint32_t b[9], uint32_t c[9]) { // Designed to even adjust the result c[] w.r.t our field (F_p), if c[] becomes negative (for DH).

	sub_com(a,b,c);
	a[8] = (a[8] << 2) >> 2;
	c[8] = a[8] - b[8];
	c[8] = (c[8] << 2) >> 2; // To counter the case of c being negative.
	}

void sub4ecc (uint32_t a[9], uint32_t b[9], uint32_t c[9]) { // (For ECC.)
	sub_com(a,b,c);
	c[8] = a[8] - b[8];
	uint32_t a1[9];
	while (c[8]>=p[8]) {
		add(c,p,a1);
		for (int i=0; i<=8; i++) c[i] = a1[i];
		break;
		}
	
	}
	
void mul (uint32_t a[9], uint32_t b[9], uint32_t d[18]) {
	
	uint64_t m[17];

	m[0] = (uint64_t)a[0]*(uint64_t)b[0];
	for (int i=1; i<=8; i++) {
		m[i] = 0;
		for (int j=0;j<=i;j++) m[i] += ((uint64_t)a[j] * (uint64_t)b[i-j]);
		}
	for (int i=9; i<=15; i++) {
		m[i] = 0;
		for (int j=8;j>=(i-8);j--) m[i] += ((uint64_t)a[j] * (uint64_t)b[i-j]);
		}
	m[16] = (uint64_t)a[8]*(uint64_t)b[8];
	
	
	uint64_t temp64=0;
	uint32_t temp32=0;
	
	d[0] = (((uint32_t)m[0]) << 2) >> 2;
	
	temp64 = m[0] >> 30;
	temp32 = (((uint32_t)temp64) << 2) >> 2;
	d[1] = (((uint32_t)m[1]) << 2) >> 2;
	d[1] = d[1] + temp32;
	d[2] = d[1] >> 30;
	d[1] = (d[1] << 2) >> 2;
	
	for (int i=2; i<17; i++) {
		temp64 = m[i-1] >> 30;
		temp32 = (((uint32_t)temp64) << 2) >> 2;
		temp32 += (((uint32_t)m[i]) << 2) >> 2;
		
		d[i] += ((uint32_t)(m[i-2] >> 60));
		
		d[i] += temp32;
		
		d[i+1] = d[i] >> 30;
		
		d[i] = (d[i] << 2) >> 2;
		}
	d[17] += ((uint32_t)(m[16] >> 30) + (uint32_t)(m[15] >> 60));
	
	}	
	
#endif	
	
