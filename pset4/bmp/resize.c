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

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // remember resize n
    int n = atoi(argv[1]);
    //printf("n = %i\n", n);

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
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
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    
    // keep old values
    int width_old = bi.biWidth;
    int height_old = bi.biHeight; 
           
    // change width, height and image size
    bi.biWidth = bi.biWidth * n;
    bi.biHeight = bi.biHeight * n;
    
    // determine padding for old scanlines
    int padding_old =  ( 4 - ( width_old * sizeof(RGBTRIPLE) ) % 4 ) % 4;
    
    //printf("padding_old = %i\n", padding_old);
    
    // determine padding for new scanlines
    int padding_new =  ( 4 - ( bi.biWidth * sizeof(RGBTRIPLE) ) % 4 ) % 4;

    //printf("padding_new = %i\n", padding_new);
    
    
    
    // change image size and filesize
    bi.biSizeImage = bi.biWidth * abs(bi.biHeight) * 3 + padding_new * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + 54;
    
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    
    
    // iterate over infile's scanlines
    for (int i = 0; i < abs(height_old); i++)
    {   
        for (int h = 0; h < n; h++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < width_old; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile n times
                for (int w = 0; w < n; w++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
     
            // add new padding
            for (int k = 0; k < padding_new; k++)
                fputc(0x00, outptr);
                
            //go back to start of line in inptr
            fseek(inptr, -width_old*sizeof(RGBTRIPLE), SEEK_CUR);   
         }   
            
            // skip over old padding in inptr
            fseek(inptr, width_old*sizeof(RGBTRIPLE) + 
                          padding_old, SEEK_CUR);
                   
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
