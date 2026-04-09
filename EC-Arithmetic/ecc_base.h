#ifndef ECC_BASE
#define ECC_BASE


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "barrett.h"
#include "expo_mult.h"


uint8_t p2[32] = {243, 239, 233, 127, 91, 131, 76, 97, 58, 4, 234, 206, 200, 190, 85, 148, 101, 114, 19, 158, 196, 253, 42, 8, 138, 28, 40, 111, 173, 64, 46, 233}; // p-2 in base 2^8.

// Equation of the Elliptic Curve : Y^2 = X^3 + aX + b.

uint32_t a[9] = {527517625, 435768055, 26387281, 931838147, 736945218, 1018624339, 78820652, 553975810, 21047}; 
uint32_t b[9] = {635395678, 683913607, 265142332, 774446674, 410951765, 431497373, 928609134, 641487413, 8796}; // by fixing "a" and "b", we fix the Elliptic Curve.

typedef struct {
	uint32_t x[9];
	uint32_t y[9];
	} point; // Creating a structure "point" with x & y coordinates, each being an element of our field (F_p).


void printPoint (point P) {
	
	printf("\n");
	for (int i=8;i>=0;i--) printf("%d ", P.x[i]);
	printf(": ");
	for (int i=8;i>=0;i--) printf("%d ", P.y[i]);
	printf("\n");
	}	


int isEqual (uint32_t *a, uint32_t *b) { // To check if 2 field elements are equal or not.
	int flag=0;
	for (int i=0;i<=8;i++) {	
		while (a[i]==b[i]) {
			flag++;
			break;
			}
		}
	flag = flag/9;
	return flag;
	} // output 1 => a=b ; output 0 => a!=b.
	
	
void inv (uint32_t *a, uint32_t *a1) { // To compute the Inverse of "a" in the field (F_p).
	
	antiSC_montgomeryLadder_mult(a,p2,a1);
	
	}


int inCurve (point P) { // To check if the point P is indeed in our curve or not.
	int flag;
	uint32_t y2[9], x3[9], ax[9], d[18], z[9], RHS[9];
	
	mul(P.y,P.y,d);
	bar_red(d,y2); // Y^2
	
	mul(P.x,P.x,d); 
	bar_red(d,x3); 
	mul(x3,P.x,d);
	bar_red(d,x3); // X^3
	
	mul(a,P.x,d);
	bar_red(d,ax); // aX
	
	add(x3,ax,z);
	shrink(z,p); // X^3 + aX
	
	add(z,b,RHS);
	shrink(RHS,p); // X^3 + aX + b
	
	flag = (isEqual(y2,RHS) == 1) ? 1 : 0;
	
	return flag;
	} // output 1 => P is in the curve ; output 0 => P is NOT in the curve.


point addition (point P, point Q) { // For P and Q being points on our curve.

/*	if (inCurve(P) == 0 || inCurve(Q) == 0) {
		printf("\n!!! Error : Point(s) not on the Curve. !!!\n");
        	exit(EXIT_FAILURE); // !!! To terminate the ECC program due to invalid inputs !!!
		
		} // Checking whether P and Q are points of the curve.
*/	
	point R;
	uint32_t x1[9], y1[9], x2[9], y2[9];
	
	for (int i=0; i<=8; i++) {
		x1[i] = P.x[i];
		y1[i] = P.y[i];
		x2[i] = Q.x[i];
		y2[i] = Q.y[i];
		}
	
/*	if (isEqual(P.x,Q.x) == 1) {
		printf("\n!!! Error : Asked to do undefined operations. !!!\n");
//        	exit(EXIT_FAILURE);
        	return; // To quit the "addition" function due to invalid inputs.
		
		} // If these are points on the Elliptic Curve, only checking equality for the x-coordinate suffices.
*/	
		
	uint32_t x2x1[9], y2y1[9], x2x1i[9], C[18], c[9], c2[9];
	
	sub4ecc(x2,x1,x2x1); // x2-x1
	sub4ecc(y2,y1,y2y1); // y2-y1
	inv(x2x1,x2x1i); // 1/(x2-x1)
	
	mul(y2y1,x2x1i,C); 
	bar_red(C,c); // ((y2-y1)/(x2-x1))
	
	mul(c,c,C);
	bar_red(C,c2); // ((y2-y1)/(x2-x1))^2
	
	add(P.x,Q.x,x2x1); // (x1+x2)
	shrink(x2x1,p); // shrinking (x1+x2) if necessary
	sub4ecc(c2,x2x1,R.x); // R.x = ((y2-y1)/(x2-x1))^2 - (x1+x2)
	
	
	
	sub4ecc(x1,R.x,x2x1); // x1-x3
	mul(c,x2x1,C);
	bar_red(C,c2); // ((y2-y1)/(x2-x1))(x1-x3)
	
	sub4ecc(c2,y1,R.y); // R.y = ((y2-y1)/(x2-x1))(x1-x3) - y1
	
	return R;
	
	}
	
	
point doubling (point P) { // For P being a point on the curve.
	
/*	if (inCurve(P) == 0) {
		printf("\n!!! Error : Point not on the Curve. !!!\n");
        	exit(EXIT_FAILURE); // !!! To terminate the ECC program due to invalid inputs !!!
		
		} // Checking whether P is a points of the curve.
*/	
	point R;
	uint32_t x1[9], y1[9];
	
	for (int i=0; i<=8; i++) {
		x1[i] = P.x[i];	
		y1[i] = P.y[i];
		}
	
/*	uint32_t zero[9] = {0,0,0,0,0,0,0,0,0};
	if (isEqual(P.y,zero) == 1) {
		printf("\n!!! Error : Asked to do undefined operations. !!!\n");
//        	exit(EXIT_FAILURE);
        	return; // To quit the "doubling" function due to invalid inputs.
		}
*/	
	
	
	uint32_t X[18], temp1[9], temp2[9], temp3[9], sum[9], s[9], s2[9];
	
	mul(x1,x1,X);
	bar_red(X,temp1); // x1^2
	add(temp1,temp1,temp2);
	shrink(temp2,p); // 2*(x1^2)
	add(temp2,temp1,temp3);
	shrink(temp3,p);// 3*(x1^2)
	add(temp3,a,sum);
	shrink(sum,p); // 3*(x1^2) + a
	
	add(y1,y1,temp1);
	shrink(temp1,p); // 2*y1
	
	inv(temp1,temp2); // (1/2y1)
	
	mul(sum,temp2,X);
	bar_red(X,s); // (3*(x1^2) + a)/2y1
	
	mul(s,s,X);
	bar_red(X,s2); // ((3*(x1^2) + a)/2y1)^2
	
	add(x1,x1,temp1);
	shrink(temp1,p); // 2*x1 

	sub4ecc(s2,temp1,R.x); // R.x = ((3*(x1^2) + a)/2y1)^2 - 2x1
	
	
	
	sub4ecc(x1,R.x,temp1); // x1-x4
	mul(s,temp1,X);
	bar_red(X,temp2); // ((3*(x1^2) + a)/2y1) * (x1-x4)
	
	sub4ecc(temp2,y1,R.y); // R.y = (((3*(x1^2) + a)/2y1)^2 * (x1-x4)) - y1
	
	return R;
	}	

#endif	
	
