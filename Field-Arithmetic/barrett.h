#ifndef BARRETT
#define BARRETT



#include<stdio.h>
#include<stdint.h>

#include "convert.h"
#include "add_mul.h"


uint8_t p0[32] = {245, 239, 233, 127, 91, 131, 76, 97, 58, 4, 234, 206, 200, 190, 85, 148, 101, 114, 19, 158, 196, 253, 42, 8, 138, 28, 40, 111, 173, 64, 46, 233}; // The 256-bit prime.

//uint32_t p[9] = {1072295925, 87166317, 782255014, 359641651, 326264212, 737612408, 29925506, 271277002, 59694}; // The 2^30 base representation of prime p.

uint32_t T[10] = {6447950, 43232768, 929819084, 468049013, 398110757, 293638490, 723593512, 999002533, 383160366, 17987}; // The precomputed value of floor(((2^30)^18)/p).


void ext_mul (uint32_t a[10], uint32_t b[10], uint32_t d[20]) { // The Extended Multiplication Function.
	
	uint64_t m[19];
	
	m[0] = (uint64_t)a[0]*(uint64_t)b[0];

	for (int i=1; i<=9; i++) {
		m[i] = 0;
		for (int j=0;j<=i;j++) m[i] += ((uint64_t)a[j] * (uint64_t)b[i-j]);
		}
	for (int i=10; i<=17; i++) {
		m[i] = 0;
		for (int j=9;j>=(i-9);j--) m[i] += ((uint64_t)a[j] * (uint64_t)b[i-j]);
		}
	m[18] = (uint64_t)a[9]*(uint64_t)b[9];
	
	
	uint64_t temp64=0;
	uint32_t temp32=0;
		
	d[0] = (((uint32_t)m[0]) << 2) >> 2;
	
	temp64 = m[0] >> 30;
	temp32 = (((uint32_t)temp64) << 2) >> 2;
	d[1] = (((uint32_t)m[1]) << 2) >> 2;
	d[1] = d[1] + temp32;
	d[2] = d[1] >> 30; // Carry of d[1]
	d[1] = (d[1] << 2) >> 2; // Click to erase the Carry.
	
	for (int i=2; i<19; i++) {
		temp64 = m[i-1] >> 30;
		temp32 = (((uint32_t)temp64) << 2) >> 2;
		temp32 += (((uint32_t)m[i]) << 2) >> 2;
		
		d[i] += ((uint32_t)(m[i-2] >> 60));
		
		d[i] += temp32;
		
		d[i+1] = d[i] >> 30;
		
		d[i] = (d[i] << 2) >> 2;
		}
	d[19] += ((uint32_t)(m[18] >> 30) + (uint32_t)(m[17] >> 60));
	
	}	
	

void shrink (uint32_t x[9], uint32_t p[9]) { // Function for subtracting prime p from the result x if x>=p.
	
	uint32_t y[9];
	int flag=0;
	int t=8;
	while (x[8]>=p[8] && flag!=100) { 
		flag=9;
		t=8;
		while (x[t]==p[t] && t>=0) {
			flag=t;
			t--;
			}
		while (x[flag-1]>p[flag-1] || flag==0) {
			sub(x,p,y);
			for (int i=0; i<=8; i++) x[i]=y[i];
			flag=0;
			break;
			}
		while (x[flag-1]<p[flag-1] && flag!=0) {
			flag=100;
			break;
			}
		}
	
	}


void bar_red (uint32_t d[18], uint32_t x[9]) { // The Barrett Reduction Function.
	
	uint32_t Q[10];
	
	for (int i=0; i<=9; i++) Q[i] = d[8+i]; // Forming Q by right-shifting d by 240 bits.
	
	
	uint32_t QT[20];
	
	ext_mul(Q,T,QT);
	
	uint32_t Q1[9], p1[9], Qp[18], Qp1[9], d1[9], y[9];
	
	for (int i=0; i<=8; i++) Q1[i] = QT[10+i]; // Dividing QT by (2^30)^10, i.e. Right Shifting QT by 300 bits and storing it in Q1.
	
	mul(Q1,p,Qp);
	
	for (int i=0;i<=8;i++) Qp1[i] = Qp[i]; // Taking the LSB 270 bits of Qp and storing it in Qp1, i.e. Qp1 = Qp (mod 2^270).

	for (int i=0;i<=8;i++) d1[i] = d[i]; // Taking the LSB 270 bits of d and storing it in d1, i.e. d1 = d (mod 2^270).

	sub(d1,Qp1,x);
	
	shrink(x,p); // subtracting p from the result x if x>=p.
	
	
	}
	
#endif
