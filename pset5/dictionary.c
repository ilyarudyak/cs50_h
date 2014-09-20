/****************************************************************************
 * dictionary.c
 * 
 * Ilya Rudyak
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


#include "dictionary.h"

// hash-table - array of pointers to node
node *hash_tab[HASHTABLE_SIZE];

// to count ## of elements in dictionary
int count = 0;
 
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{   
    // convert to lower case
    char str[LENGTH + 1];
    int len = strlen(word);
    for (int i = 0; i <= len; i++)
        str[i] = tolower(word[i]);
    
    // calculate hash 
    int n = DJBHash(str);
    
    // search only in backet n
    node *p = hash_tab[n];
         
    while (p != NULL) {           
        
        if ( strcmp(p->word, str) == 0 ) 
            return true;
                
        p = p->next;
    }
    
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    char s[LENGTH + 1];
    FILE *in = fopen(dictionary, "r");
    
    if ( in == NULL)
        return false;
    
    else {
    // load up to end of file
        while ( fscanf(in, "%s", s) != EOF) {
            insert(s);
            count++;
        }
    }    
    fclose(in);
    
    return true;
}
/**
 * Insert a string into hash table, bucket n.
 */
void insert(char *s) {
    
    // calculate hash for string s
    int n = DJBHash(s);
    
    // create new node *
    node *new = malloc(sizeof(node));
    strcpy(new->word, s);
    new->next = NULL;
        
    //insert if list is empty
    if ( hash_tab[n] == NULL ) {
        hash_tab[n] = new;
    }
    //insert as head if list is not empty
    else {
        new->next = hash_tab[n];
        hash_tab[n] = new;
    }
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

/**
 * DJB2 hash function
 */
unsigned int DJBHash(char* str)
{
   long long hash = 5381;
   unsigned int i    = 0;
   int len = strlen(str);

   for(i = 0; i < len; str++, i++)
   {
      hash = ((hash << 5) + hash) + (*str);
   }

   return (unsigned int) hash % HASHTABLE_SIZE;
}
/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    
    return count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        
        node *p = hash_tab[i];
        
        while (p != NULL) {
            
            node *tmp = p;
            p = p->next;
            free(tmp);
        }
    }
    return true;
}
