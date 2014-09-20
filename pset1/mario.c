/**********************************
*   superMario half-pyramid
*
*   by irudyak
*   pset1 cs50 2012
*
***********************************/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    
    int i,j,k,h=-1;
    
    
    while (0>h || h>23){
        printf ("Height: ");
        h=GetInt();
    }
        
    for (i=1; i<=h; i++){
        for (j=0; j<=(h-i-1); j++)
            printf (" ");
        for (k=0; k<=i; k++)
            printf ("#");
        printf ("\n");   
    }       
    return 0;
}
