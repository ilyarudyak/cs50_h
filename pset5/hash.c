#include <stdio.h>
#include <string.h>

# include "dictionary.h" 

int hash(char *str);

int main(void) {
    
    char s[LENGTH + 1];
    
    FILE *in = fopen("/home/jharvard/Dropbox/pset5_1/small.txt", "r");
    
    for (int i = 0; i < 100; i++) {
        fscanf(in, "%s", s);
        printf( "%i\n", hash(s) );
    }
        
    fclose(in);    
}

/**
 * simple hash function
 */
int hash(char *s)
{
   int len = strlen(s);
   int hash = 0;
    
   for (int i = 0; i < len; i++, s++)
        hash += *s;

   return hash % PRIME;
}
