/*Program to implement signing algorithm of RSA-based FDH signature */

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

static void hashing(FILE *fp,big hash)
{ /* compute hash function */
    char h[20];
    int i,ch;
    sha sh;

    shs_init(&sh);

    while ((ch=fgetc(fp))!=EOF)
        shs_process(&sh,ch);
    
    shs_hash(&sh,h);
    bytes_to_big(20,h,hash);
}

miracl *mip;

int main()
{  
    
    /*  encode using public key, e = 3, N = 'taken from file'  */
    big N,e,d,p,q,n,hash,s;

    FILE *ifile;
    FILE *ofile;

    mip=mirsys(100,0);

    N=mirvar(0);
    e=mirvar(0);
    d=mirvar(0);
    p=mirvar(0);
    q=mirvar(0);
    n=mirvar(0);
    hash=mirvar(0);
    s=mirvar(0);

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


    ifile=fopen("genkey.c","rt");

    mip->IOBASE=128;

    hashing(ifile,hash);
    fclose(ifile);

    powmod(hash,d,N,s);
    mip->IOBASE=16;
    cotnum(hash,stdout);
    printf("Signature = ");
    cotnum(s,stdout);    

    return 0;
}
