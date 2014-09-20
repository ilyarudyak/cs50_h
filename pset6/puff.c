/****************************************************************************
 * puff.c
 *
 * Ilya Rudyak
 * Computer Science 50ht
 * Problem Set 6
 *
 * Decompress a huff-compressed file.
 ***************************************************************************/

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "forest.h"
#include "huffile.h"
#include "tree.h"

// first and last symbols to dump
#define FIRST '!'
#define LAST '~'

// number of columns to use
#define COLS 8

// global variable
Forest *f;
int count;

// prototypes
bool isHuffile(char *path);
bool createForest(char *path);
bool decompress(char *path1, char *path2);
bool isLeaf(Tree *t);

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        printf("Usage: %s file.bin file.txt\n", argv[0]);
        return 1;
    }
    
    // check if it's Huffile
    if ( isHuffile(argv[1]) == 0 )
    {
        printf("it's not a Huffile");
        return 1;
    }
    
    // create forest based on header.frequencies[]
    createForest(argv[1]);
    
    //decompress
    if ( decompress(argv[1], argv[2]) == false )
        return 1;
    
  
    
    //free forest
    rmforest(f);
    
    return 0;
}

/**
 * decompress Huffile and print to file.
 */
bool decompress(char *path1, char *path2) {

    // open input
    Huffile* input = hfopen(path1, "r");
    if (input == NULL)
    {
        printf("Could not open %s for reading.\n", path1);
        return false;
    }

    // read in header
    Huffeader header;
    if (hread(&header, input) == false)
    {
        hfclose(input);
        printf("Could not read header.\n");
        return false;
    }
    
    // open file for writing
    FILE *out = fopen(path2, "w");
    if (out == NULL)
    {
        printf("Could not open %s for writing.\n", path2);
        return false;
    }
    
    // read bits, crawl the tree and write to out
    int bit;
    char ch;
    Tree *p = f->first->tree;
    
    // check single-character file
    if ( count == 1 ) 
    {
        ch = p->symbol;
        if ( fputc(ch, out) == EOF ) 
        {
            printf("can't write\n");
            return false;
        }
        
        return true;
    }
    
    while ((bit = bread(input)) != EOF)
    {   
        
        
        if ( bit == 0 ) 
        {
            p = p->left;
            if ( isLeaf(p) ) 
            {
                ch = p->symbol;
                if ( fputc(ch, out) == EOF ) 
                {
                printf("can't write\n");
                return false;
                }
                p = f->first->tree;
            }    
        }
            
        else if ( bit == 1 )
        {
            p = p->right;
            if ( isLeaf(p) ) 
            {
                ch = p->symbol;
                if ( fputc(ch, out) == EOF )
                {
                printf("can't write\n");
                return false;
                } 
                p = f->first->tree;
            }    
        }
        
        
    }    
    
    return true;
}

/**
 * Check if tree is leaf.
 */
bool isLeaf(Tree *t) {
    
    if ( t->left == 0 && t->right ==0 )
        return true;
        
    else return false;    
}

bool createForest(char *path) {
    
    // create empty forest
    f = mkforest();
    
    // open input
    Huffile* input = hfopen(path, "r");
    if (input == NULL)
    {
        printf("Could not open %s for reading.\n", path);
        return 0;
    }
    
    // read in header
    Huffeader header;
    if (hread(&header, input) == false)
    {
        hfclose(input);
        printf("Could not read header.\n");
        return 0;
    }
    
    // read symbols and freq from header, create and plant trees in forest
    
    for (int i = 0; i < SYMBOLS; i++)
    {
        if ( header.frequencies[i] != 0 )
        {   
            Tree *t = mktree();
            t->symbol = i;
            t->frequency = header.frequencies[i];
            plant(f, t);
            count++;
             
        }
             
    }
    
       
    // join trees as siblings
    
    for (int i = 0; i < count - 1; i++) 
    {
        Tree *t = mktree();
        t->left = pick(f);
        t->right = pick(f);
        t->frequency = t->left->frequency + t->right->frequency;
        plant(f, t);
     }   
        
        
        
             
    
    
    
    
    // close input
    hfclose(input);
    
    return true;
    
} 


/**
 * Open file  and check if it is Huffile. 
 * Return NULL if not Huffile or other mistake, else return Huffile *.
 */
bool isHuffile(char *path) {
    
    // open input
    Huffile* input = hfopen(path, "r");
    if (input == NULL)
    {
        printf("Could not open %s for reading.\n", path);
        return 0;
    }
    
    // read in header
    Huffeader header;
    if (hread(&header, input) == false)
    {
        hfclose(input);
        printf("Could not read header.\n");
        return 0;
    }

    // check for magic number
    if (header.magic != MAGIC)
    {
        hfclose(input);
        printf("File was not huffed.\n");
        return 0;
    }

    // check checksum
    int checksum = header.checksum;
    for (int i = 0; i < SYMBOLS; i++)
    {
        checksum -= header.frequencies[i];
    }
    if (checksum != 0)
    {
        hfclose(input);
        printf("File was not huffed.\n");
        return 0;
    }
    
    
    
    // close input
    hfclose(input);
    
    return true;   
}



