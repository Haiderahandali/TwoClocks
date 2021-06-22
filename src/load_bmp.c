#include "load_bmp.h"
#include <stdio.h>

void* malloc(size_t size);

void ReadBMP(bmp_file_t* bmp, char const* pathToFile)
{
    FILE* BMPFILE;
    if (!(BMPFILE = fopen(pathToFile, "rb")))
    {
        printf("couldn't open file ... error terminating \n");
        return;
    }

    //reading data from FILE into our structure;
    fseek(BMPFILE, BMP_SIGNATURE_OFFSET, SEEK_SET);
    fread(&bmp->bmpSignature, BMP_SIGNATURE_SIZE, 1, BMPFILE);

    fseek(BMPFILE, BMP_PIXEL_DATA_OFFSET, SEEK_SET);
    fread(&bmp->dataOffset, BMP_PIXEL_DATA_SIZE_OFFSET_SIZE, 1, BMPFILE);

    fseek(BMPFILE, BMP_WIDTH_OFFSET, SEEK_SET);
    fread(&bmp->width, BMP_WIDTH_SIZE, 1, BMPFILE);

    fseek(BMPFILE, BMP_HEIGHT_OFFSET, SEEK_SET);
    fread(&bmp->height, BMP_HEIGHT_SIZE, 1, BMPFILE);

    fseek(BMPFILE, BMP_BITS_PER_PIXEL_OFFSET, SEEK_SET);
    fread(&bmp->bpp, BMP_BITS_PER_PIXEL_SIZE, 1, BMPFILE);

    fseek(BMPFILE, BMP_COMPRESSION_OFFSET, SEEK_SET);
    fread(&bmp->compression, BMP_COMPRESSION_SIZE, 1, BMPFILE);

    size_t imageSize = (size_t)(bmp->width * bmp->height * (bmp->bpp / 8)); // in bytes

    bmp->pixelDataPointer = (byte*)malloc(imageSize);

    fseek(BMPFILE, bmp->dataOffset, SEEK_SET);
    fread(bmp->pixelDataPointer, imageSize, 1, BMPFILE);

    //--------- Error Checking, probably late and should be done earlier but ---------//
    //--------- it is easier to read if I put it in the end --------------------------//

    if (!(bmp->compression == BI_RGB || bmp->compression == BI_BITFIELDS))
    {
        printf("not a supported compression");
    }

    if (!((bmp->bmpSignature[0] == 'B') && (bmp->bmpSignature[1] == 'M')))
    {
        printf("Error file is not a BMP format file \n");
    }

    if (bmp->height > 0) // if it is positive then flip it becuase that means the bmp is stored bottom up
    {
        typedef unsigned char BYTE;

        int pitch = bmp->width * bmp->bpp / 8;
        for (int row = 0; row < bmp->height >> 1; ++row)
        {
            BYTE* row1 = bmp->pixelDataPointer + (row * pitch);
            BYTE* row2 = bmp->pixelDataPointer + ((bmp->height - 1 - row) * pitch);
            for (int col = 0; col < bmp->width * bmp->bpp / 8; ++col)
            {
                BYTE tmp  = row1[col];
                row1[col] = row2[col];
                row2[col] = tmp;
            }
        }
    }

    fclose(BMPFILE);
}
