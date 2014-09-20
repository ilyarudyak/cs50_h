/****************************************************************************
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 ***************************************************************************/
       
#include <stdio.h>
#include <stdlib.h>

#include "/home/jharvard/Dropbox/pset4/bmp/bmp.h"

int main(int argc, char* argv[])
{
    

    // filename
    char* infile = "small2_6.bmp";
    

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // print filesize
    printf( "bfSize = %i\n", bf.bfSize); 
    
    // print width, height and image size
    printf( "biWidth = %i\n", bi.biWidth);  
    printf( "biHeight = %i\n", bi.biHeight); 
    printf( "biSizeImage = %i\n", bi.biSizeImage); 
    
    
    
    
    // determine padding for new scanlines
    int padding =  ( 4 - ( bi.biWidth * sizeof(RGBTRIPLE) ) % 4 ) % 4;

    printf("padding = %i\n", padding);
 
    
}    
    
    
