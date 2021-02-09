// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include  "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }
     

    int num=atoi(argv[1]);

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    if(!(num<100&&num>0))
    {
        fprintf(stderr,"Resize only 1-100. Try again\n");
        return 2;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
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
        return 5;
    }
    
    int oldwidth=bi.biWidth;
    int oldheight=bi.biHeight;
    int newwidth=bi.biWidth*num;
    int newheight=bi.biHeight*num;
    
    int inPadding = (4 - (oldwidth * sizeof(RGBTRIPLE)) % 4) % 4; 
    int outPadding = (4 - (newwidth * sizeof(RGBTRIPLE)) % 4) % 4;

    
    bi.biHeight=newheight;
    bi.biWidth=newwidth;
  
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * newwidth) + outPadding) * abs(newheight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    RGBTRIPLE sline[newwidth * sizeof(RGBTRIPLE)];
    
    for(int i = 0, biHeight = abs(oldheight); i < biHeight; i++)
    {
         for (int j = 0; j < oldWidth; j++)
        {
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for (int k = 0; k < n; k++)
            {
                sline[(j * n) + k] = triple;
            }
        }

        fseek(inptr, inPadding, SEEK_CUR);

        for (int j = 0; j < n; j++)
        {
            
            fwrite(sline, sizeof(RGBTRIPLE), newwidth, outptr);

            for (int k = 0; k < outPadding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }
  
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
