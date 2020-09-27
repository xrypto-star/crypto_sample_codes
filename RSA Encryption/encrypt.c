/*Program to implement encryption algorithm of RSA */

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
    big N,e,m,c;

    FILE *ifile;
    FILE *ofile;

    static char line[1000];
    static char buff[256];

    int i,mlen,klen;

    mip=mirsys(100,0);

    N=mirvar(0);
    e=mirvar(0);
    m=mirvar(0);
    c=mirvar(0);


    /*Read Public Parameters from file public.key*/
    ifile=fopen("public.key","rt");
    mip->IOBASE=16;
    cinnum(N,ifile);
    cinnum(e,ifile);
    fclose(ifile);

    
    /* find key length in characters (ASCII). Reset it as required and to prevent loss of plaintext! E,g., If N is of 23 bits, set klen = 3, N is 21 bits, set klen = 2, etc., Could be completely automated. */
    klen = logb2(N)/7;/* - 1;*/    
    printf("Key length = %d\n",klen);

    
    cotnum(N,stdout);
    cotnum(e,stdout);

    
    ofile = fopen("output.enc","wt");
    printf("Enter the text to be encrypted: \n");
    gets(line);
    mlen = strlen(line);
    while(TRUE)
    {
        if(mlen < klen)
        {
            break;
        }
        for(int i=0; i<klen; i++)
            buff[i] = line[i];            
        buff[klen] = '\0';

        for(int i=klen; i<=mlen; i++)
            line[i-klen] = line[i];
        mlen = strlen(line);

        mip->IOBASE=128;
        cinstr(m,buff);
        powmod(m,e,N,c);
        mip->IOBASE=16;
        /*cotnum(c,stdout);*/
        cotnum(c,ofile);
    }

    /*Unpadded*/
    if (mlen < klen && mlen != 0)
    {
        for (int i = 0; i < mlen; ++i)
            buff[i] = line[i];
        buff[mlen] = '\0';

        mip->IOBASE=128;
        cinstr(m,buff);
        powmod(m,e,N,c);
        mip->IOBASE=16;
        /*cotnum(c,stdout);*/
        cotnum(c,ofile);
    }
    fclose(ofile);

    return 0;
}   

