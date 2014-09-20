/****************************************************************************
 * recover.c
 *
 * Ilya Rudyak
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 ***************************************************************************/
 
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t  BYTE;

// size of block to read
#define BLOCK 512

// JPG header size
#define HEADER_SIZE 4

//global array
BYTE card_reader[BLOCK];

//prototypes
bool isJPG(BYTE *jpg_header);
 
int main(void)
{   
    // open file
    FILE *in = fopen("card.raw", "r");
    
    if ( in == 0 )
    {
        printf("can't open file");
        return 1;
    }
    
    // count jpgs in file
    int count = 0;
    
    // array to keep file title
    char title[8];
    
    // flag to write to jpg file
    bool isJPG_open = false;
    
    // create file pointer
    FILE *file;
    
    // start reading from file
    while (true)
    {    
        if ( feof(in) != 0 ) 
        {   
            // close last jpg file
            fclose(file);
            
            break;
        }
        
        fread(card_reader, BLOCK, 1, in);
        
        if ( isJPG(card_reader) )
        {   
            
           
            // when found new jpg - close old one
            if ( isJPG_open ) 
                fclose(file);
                
            // create new jpg file
            sprintf(title, "%03i.jpg", count);
            file = fopen( title, "w" );
            
            if ( file == 0 )
            {
                printf("can't create jpg file");
                return 1;
            }
            
            // we open new jpg file
            isJPG_open = true;
            
            // increase counter
            count++;
        }
        
        if ( isJPG_open && feof(in) == 0 )
        {
            // write to jpg file
            fwrite(card_reader, BLOCK, 1, file);
        }
        
            
        
    }
    
    //printf("jpgs ## %i\n", count);
    // close card file
    fclose(in);
    
    return 0; 
}


bool isJPG(BYTE *card_reader)
{
    if ( card_reader[0] != 0xff ) return false;
    if ( card_reader[1] != 0xd8 ) return false;
    if ( card_reader[2] != 0xff ) return false;
    if ( card_reader[3] != 0xe0 &&
          card_reader[3] != 0xe1 ) return false;
          
    return true;
}









