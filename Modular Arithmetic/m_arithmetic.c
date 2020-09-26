/* Program to implement modular arithmetic operations in MIRACL.
*/
#include <stdio.h>
#include "miracl.h"   /* include MIRACL system */

void main(){

	big a, b, c;

	big n; /*Mod*/

	big t;
	
	/* base 10, 5000 digits per big */
	miracl *mip=mirsys(5000,10);

	/*Initialize variables*/
	a=mirvar(0);
	b=mirvar(0);
	c=mirvar(0);
	n=mirvar(0);
	t=mirvar(0);


	/*Initializes internal random number system. */
	long seed = 23422;
	irand(seed);

	getchar();

	bigdig(10,10,n);
	printf("n = ");
	otnum(n,stdout);

	getchar();
	
	/*Generate two big random numbers a and b < n and >= 0 in base 10, each consisting pf 150 digits */
	bigrand(n,a);
	bigrand(n,b);

	/*Output the Random Numbers to screen*/
	printf("a = ");
	otnum(a,stdout);
	printf("b = ");
	otnum(b,stdout);


	getchar();


	/*Modular Addition: c = (a + b)mod n*/
	add(a,b,c);
	copy(n,t);
	divide(c,t,t);
	printf("(a + b)mod n = ");
	otnum(c,stdout);

	
	getchar();

	
	/*Modular Subtraction: c = (a - b)mod n*/
	subtract(a,b,c);
	printf("(a - b)mod n = ");
	if (exsign(c) == 1)
	{
		otnum(c,stdout);
	}
	else		/*  4-6 mod 5 = -2 mod 5 = 3 mod 5 = -7 mod 5 = -12 mod 5  */
	{	
		while(exsign(c) != 1)
			add(c,n,c);
		otnum(c,stdout);
	}


	getchar();


	/*Modular Multiplication: c = (a * b)mod n*/
	multiply(a,b,c);
	copy(n,t);
	divide(c,t,t);
/*	t=mirvar(0);
	mad(a,b,t,n,c,t);
	copy(t,c);*/
	printf("(a * b)mod n = ");
	otnum(c,stdout);


	getchar();

	
	/*Modular Division or Inverse: c = (a / b)mod n = a*b^(-1) mod n*/
	egcd(b,n,c);	/*3^-1 mod 7 = */ /* a a^-1 = 1 mod n*/
	convert(1,t);
	if(!mr_compare(c,t))
	{

		multi_inverse(1,&b,n,&c);
		/*otnum(c,stdout);*/
		multiply(a,c,c);
		copy(n,t);
		divide(c,t,t);
		printf("(a / b)mod n = ");
		otnum(c,stdout);
	}
	else
		printf("Can't Divide./Inverse doesn't exist!!\n");

}
