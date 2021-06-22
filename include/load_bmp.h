#ifndef LOAD_BMP_H
#define LOAD_BMP_H

typedef signed char int8_t;
typedef unsigned char byte;
typedef unsigned char uint8_t;

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

typedef signed short int16_t;
typedef signed int int32_t;

#define BI_RGB 0
#define BI_BITFIELDS 3

#define Amask 0XFF000000
#define Rmask 0X00FF0000
#define Gmask 0X0000FF00
#define Bmask 0X000000FF

enum //offset in hexadecimal
{
    BMP_SIGNATURE_OFFSET      = 0X00,
    BMP_PIXEL_DATA_OFFSET     = 0X0A,
    BMP_WIDTH_OFFSET          = 0X12,
    BMP_HEIGHT_OFFSET         = 0X16,
    BMP_BITS_PER_PIXEL_OFFSET = 0X1C,
    BMP_COMPRESSION_OFFSET    = 0X1E,
};

enum //sizes in BYTE
{
    BMP_SIGNATURE_SIZE              = 2,
    BMP_PIXEL_DATA_SIZE_OFFSET_SIZE = 4,
    BMP_WIDTH_SIZE                  = 4,
    BMP_HEIGHT_SIZE                 = 4,
    BMP_BITS_PER_PIXEL_SIZE         = 2,
    BMP_COMPRESSION_SIZE            = 4
};

typedef struct bmp_file_t
{
    char bmpSignature[BMP_SIGNATURE_SIZE];
    int32_t width;
    int32_t height;
    uint16_t bpp;
    uint32_t dataOffset;
    uint8_t compression;
    byte* pixelDataPointer;
} bmp_file_t;

void ReadBMP(bmp_file_t* bmp, char const* pathToFile);

#endif
