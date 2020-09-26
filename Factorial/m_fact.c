/*
* Program to calculate factorials in MIRACL. Demonstrate power of big numbers
*/
#include <stdio.h>
#include "miracl.h"   /* include MIRACL system */

void main(){

	big nf; /* declare "big" variable nf */
	int n;
	
	/* base 10, 5000 digits per big */
	miracl *mip=mirsys(5000,10);

	
	nf=mirvar(1); /* initialise big variable nf=1 */
	
	printf("factorial program\n");
	
	printf("input number n= \n");
	scanf("%d",&n);
	getchar();
	
	while (n>1)
		premult(nf,n--,nf); /* nf=n!=n*(n-1)*...2*1 */
	
	printf("n!= \n");
	otnum(nf,stdout); /* output result */
}
