/*Program to implement Key generation algorithm of RSA-based FDH signature */

#include <stdio.h>
#include "miracl.h"   /* include MIRACL system */
#define NP 2            /* use two primes - could be more */
#define PRIME_BITS 10  /* >=256 bits */

static miracl *mip;

static big pd,pl,ph;

/* generate strong prime number =11 mod 12 suitable for RSA encryption */
void strongp(big p,int n)
{ 
    long seed1, seed2;
    printf("Seed 1? ");
    scanf("%ld",&seed1);
    getchar();
    printf("Seed 2? ");
    scanf("%ld",&seed2);
    getchar();

    int r,r1,r2;
    
    irand(seed1);
    bigbits(2*n/3,pd);
    nxprime(pd,pd);
    expb2(n-1,ph);
    divide(ph,pd,ph);
    expb2(n-2,pl);
    divide(pl,pd,pl);
    subtract(ph,pl,ph);

    irand(seed2);
    bigrand(ph,ph);
    add(ph,pl,ph);
    r1=subdiv(pd,12,pl);
    r2=subdiv(ph,12,pl);

    r=0;
    while ((r1*(r2+r))%12!=5) 
        r++;

    incr(ph,r,ph);
    do 
    { 
        /* find p=2*r*pd+1 = 11 mod 12 */
        multiply(ph,pd,p);
        premult(p,2,p);
        incr(p,1,p);
        incr(ph,12,ph);
    }while (!isprime(p));
}

int main()
{  

    /*  calculate public (N,e) and private keys (p,q)  *
    *  for rsa encryption                 */
    int i;
    long seed[2*NP];

    big p[NP],N,a,b,n,e,d;

    big z,o,t;

    FILE *outfile;
    
    mip=mirsys(100,0);

    gprime(15000);  /* speeds up large prime generation */

    for (i=0;i<NP;i++) 
        p[i]=mirvar(0);

    N=mirvar(0);
    pd=mirvar(0);
    pl=mirvar(0);
    ph=mirvar(0);
    a=mirvar(0);
    b=mirvar(0);
    n=mirvar(0);
    e=mirvar(0);
    z=mirvar(0);
    o=mirvar(0);
    t=mirvar(0);
    d=mirvar(0);

    printf("Generating RSA parameters...\n");
    printf("Please wait....\n");
    convert(1,N);  /* Converts 1 to big number and stores it inside ke*/
    for (i=0;i<NP;i++) 
    {   
        printf("Generating prime number %d...\n",i+1);
        strongp(p[i],PRIME_BITS);
        multiply(N,p[i],N);
    }
    
    /*n = (p-1)(q-1)*/
    decr(p[0],1,a);
    decr(p[1],1,b);
    multiply(a,b,n);


    /*Choose e s.t. 1 < e < n and e & n are co-prime*/
    convert(0,z);
    convert(1,o);
    do
    {
        bigrand(n,e);
        egcd(e,n,t);
    }while(mr_compare(e,z) == 0 || mr_compare(e,o) == 0 || mr_compare(t,o) != 0);
    

    /*Computing d s.t. ed = 1 mod n*/
    multi_inverse(1,&e,n,&d);


    mip->IOBASE=16;

    printf("\nKey Length = %d bits\n",logb2(N));  

    outfile=fopen("public.key","wt");
    printf("Public Parameters:\n");

    printf("N = ");
    cotnum(N,stdout);
    cotnum(N,outfile);

    printf("e = ");
    cotnum(e,stdout);
    cotnum(e,outfile);

    fclose(outfile);


    outfile=fopen("private.key","wt");
    printf("Private Parameters:\n");

    printf("p = ");
    cotnum(p[0],stdout);
    cotnum(p[0],outfile);
    
    printf("q = ");
    cotnum(p[1],stdout);
    cotnum(p[1],outfile);

    printf("d = ");
    cotnum(d,stdout);
    cotnum(d,outfile);

    printf("n = ");
    cotnum(n,stdout);
    cotnum(n,outfile);

    fclose(outfile);

    return 0;
}
