/*Program to implement verification algorithm of RSA-based FDH signature */

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

static void hashing(FILE *fp,big c_hash)
{ /* compute hash function */
    char h[20];
    int i,ch;
    sha sh;

    shs_init(&sh);

    while ((ch=fgetc(fp))!=EOF)
        shs_process(&sh,ch);
    
    shs_hash(&sh,h);
    bytes_to_big(20,h,c_hash);
}

miracl *mip;

int main()
{  
    
    /*  encode using public key, e = 3, N = 'taken from file'  */
    big N,e,s,c_hash,s_hash,t;

    FILE *ifile;

    static char sig[1000];

    mip=mirsys(100,0);

    N=mirvar(0);
    e=mirvar(0);
    s=mirvar(0);
    c_hash=mirvar(0);
    s_hash=mirvar(0);
    t=mirvar(0);


    /*Read Public Parameters from file public.key*/
    ifile=fopen("public.key","rt");
    mip->IOBASE=16;
    cinnum(N,ifile);
    cinnum(e,ifile);
    fclose(ifile);

    
    ifile=fopen("genkey.c","rt");

    mip->IOBASE=128;

    hashing(ifile,c_hash);
    fclose(ifile);

    copy(N,t);
    divide(c_hash,t,t);
    
    mip->IOBASE=16;
    printf("Signature? ");
    scanf("%s",sig);
    cinstr(s,sig);
    powmod(s,e,N,s_hash);

    if (mr_compare(s_hash,c_hash) == 0)
    {
        printf("Verification is successful!!\n");
    }

    return 0;
}   

