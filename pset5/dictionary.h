/****************************************************************************
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// hash table size
#define HASHTABLE_SIZE 10007

// prime number used in hash function
#define PRIME 10007

// struct definition for hash table
typedef struct node 
{
    char word[LENGTH + 1];
    struct node *next;
} 
node;



/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/**
 * Insert a string into hash table, bucket n.
 */
void insert(char *s);

/**
 * simple hash function
 */
int hash(char *s);

/**
 * DJB2 hash function
 */
unsigned int DJBHash(char* str);

#endif // DICTIONARY_H
