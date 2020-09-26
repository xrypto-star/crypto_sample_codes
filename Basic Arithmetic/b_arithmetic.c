/* Program to implement basic arithmetic operations
*/
#include <stdio.h>
#include "miracl.h"   /* include MIRACL system */

void main(){

	big a, b, c;
	
	/* base 10, 5000 digits per big */
	miracl *mip=mirsys(5000,10);

	/*Initialize variables*/
	a=mirvar(0);
	b=mirvar(0);
	c=mirvar(0);

	/*Initializes internal random number system. */
	long seed = 23422;
	irand(seed);

	getchar();

	/*Generate two big random numbers a and b in base 10, each consisting pf 150 digits */
	bigdig(10,10,a);
	bigdig(10,10,b);

	/*Output the Random Numbers to screen*/
	printf("a = ");
	otnum(a,stdout);
	printf("b = ");
	otnum(b,stdout);

	getchar();

	/*Adding: c = a + b*/
	add(a,b,c);

	printf("a + b = ");
	otnum(c,stdout);

	getchar();

	/*Subtract: c = a - b*/
	subtract(a,b,c);

	printf("a - b = ");
	otnum(c,stdout);

	getchar();

	/*Multiply: c = a * b*/
	multiply(a,b,c);

	printf("a * b = ");
	otnum(c,stdout);

	getchar();

	/*Divide: c = a / b*/
	divide(b,a,c);

	printf("b / a = ");
	otnum(c,stdout);

	getchar();

	/*Reprint the Random Numbers to stdout*/
	printf("a = ");
	otnum(a,stdout);
	printf("b = ");
	otnum(b,stdout);
}
