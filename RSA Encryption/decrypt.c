/*Program to implement decryption algorithm of RSA */

#include <stdio.h>
#include "miracl.h"   /* include MIRACL system */
#include <stdlib.h>
#include <string.h>
#include <math.h>

void strip(char *name)
{ 
    /* strip off filename extension */
    int i;
    for (i=0; name[i]!='\0'; i++)
    {
        if (name[i]!='.') continue;
        name[i]='\0';
        break;
    }
}

miracl *mip;

int main()
{  
    
    /*  encode using public key, e = 3, N = 'taken from file'  */
    big N,e,m,c,d,p,q,n;

    FILE *ifile;
    FILE *ofile;

    mip=mirsys(100,0);

    N=mirvar(0);
    e=mirvar(0);
    m=mirvar(0);
    c=mirvar(0);
    d=mirvar(0);
    p=mirvar(0);
    q=mirvar(0);
    n=mirvar(0);

    /*Read Public and Private Parameters from files public.key and private.key*/
    ifile = fopen("public.key","rt");
    mip->IOBASE=16;
    cinnum(N,ifile);
    cinnum(e,ifile);
    fclose(ifile);
    ifile=fopen("private.key","rt");
    cinnum(p,ifile);
    cinnum(q,ifile);
    cinnum(d,ifile);
    cinnum(n,ifile);
    fclose(ifile);

    ifile=fopen("output.enc","rt");
    while(TRUE)
    {
        mip->IOBASE=16;
        cinnum(c,ifile);
        if (size(c) == 0)
        {
            break;
        }
        powmod(c,d,N,m);
        mip->IOBASE=128;
        cotnum(m,stdout);
    }
    printf("\n");
    fclose(ifile);

    return 0;
}
