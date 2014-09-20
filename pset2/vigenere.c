/****************************************************************************
 * vigenere.c
 *
 * Ilya Rudyak
 * ilya.rudyak@gmail.com
 *
 * cs50 pset2
 *
 * Encrypts the string using vigenere cipher.
 ***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>


int main (int argc, string argv[])
{   
    if (argc!=2){
        printf ("Usage: ~/Dropboxpset2/vigenere <keyword>\n");
        return 1;
    }
    

    
    string w, k1;
    int w1[100];
    
    k1=argv[1];    
    int l=strlen(k1);
    int k[l];
    
    for (int i=0; i<l; i++){
        if (isalpha(k1[i])==0){
            printf ("Keyword must only contain letters A-Z and a-z\n");
            return 1;} 
    }       
 
    
    

    
    for (int i=0; i<l; i++){
        if (islower(k1[i])!=0)
            k[i]=k1[i]-97;
        else
            k[i]=k1[i]-65;
        
    }
    
    w=GetString();
    
    int j=0;
    for (int i=0; i<strlen(w); i++){
        
        if (islower(w[i])!=0 && w[i]+k[j]<=122)
            w1[i]=w[i]+k[j];   
        else if (islower(w[i])!=0 && w[i]+k[j]>122)
            w1[i]=w[i]+k[j]-26;
        else if (isupper(w[i])!=0 && w[i]+k[j]<=90)
            w1[i]=w[i]+k[j];
        else if (isupper(w[i])!=0 && w[i]+k[j]>90)
            w1[i]=w[i]+k[j]-26;
        else{
            w1[i]=w[i];
            j--;
        }
        if (j<l-1)
            j++;
        else
            j=0;
            
            
        
    }
    
    for (int i=0; i<strlen(w); i++)
        printf ("%c", w1[i]);
        
    printf ("\n");           
    
  
    return 0;
}
