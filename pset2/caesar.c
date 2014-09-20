/****************************************************************************
 * caesar.c
 *
 * Ilya Rudyak
 * ilya.rudyak@gmail.com
 *
 * Hail, Caesar! cs50 pset2
 *
 * Encrypts the string using caesar cipher.
 ***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>


int main (int argc, string argv[])
{   
    if (argv[1]==NULL){
        printf ("Usage: ~/Dropbox/pset2/caesar <key>\n");
        return 1;
    }
    string w;
    int w1[100], k;
    
    int k1 = atoi(argv[1]);
    if (k1>26)
        k=k1-26*(k1/26);
     else
        k=k1;
    
    
    w=GetString();
    
    
    for (int i=0; i<strlen(w); i++){
        if (islower(w[i])!=0 && w[i]+k<=122)
            w1[i]=w[i]+k;
        else if (islower(w[i])!=0 && w[i]+k>122)
            w1[i]=w[i]+k-26;
        else if (isupper(w[i])!=0 && w[i]+k<=90)
            w1[i]=w[i]+k;
        else if (isupper(w[i])!=0 && w[i]+k>90)
            w1[i]=w[i]+k-26;
        else if (islower(w[i])==0 && isupper(w[i])==0)
            w1[i]=w[i];
    }

        
    for (int i=0; i<strlen(w); i++)
        printf ("%c", w1[i]);
        
    printf ("\n");           
    
  
    return 0;
}
