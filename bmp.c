#include "bmp.h"

#include <Windows.h>
#include <stdio.h>
#include <memory.h>

int loadBmp(const char* fileName, Image* image)
{
    int ret = 0;

    FILE* file = NULL;
    
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    unsigned char* p = NULL;

    unsigned int i;
    unsigned int j;

    if (image)
    {
        memset(&fileHeader, 0, sizeof(BITMAPFILEHEADER));
        memset(&infoHeader, 0, sizeof(BITMAPINFOHEADER));

        // incoorporate later
#if 0
        BITMAPV4HEADER      bmpV4Header;   // BITMAPINFOHEADER + 5 DWORDS + CIEXYZTRIPLE + 3 DWORDS.
        BITMAPV5HEADER      bmpV5Header;   // BITMAPV4HEADER + 4 DWORDS.
        BITMAPCOREHEADER    bmpDIB_1;      // for OS/2?

        RGBQUAD* colorTableValues = nullptr;

        bool OS2;
#endif
    
        if (fopen_s(&file, fileName, "rb") == 0)
        {
            // BITMAPFILEHEADER

            fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, file);

            // The file type must be BM, BA, CI, CP, IC or PT
            // http://en.wikipedia.org/wiki/BMP_file_format

            if ((fileHeader.bfType == (WORD)0x4D42) ||  // BM – Windows 3.1x, 95, NT, ... etc.
                (fileHeader.bfType == (WORD)0x4D42) ||  // BA – OS/2 struct Bitmap Array
                (fileHeader.bfType == (WORD)0x4D42) ||  // CI – OS/2 struct Color Icon
                (fileHeader.bfType == (WORD)0x4D42) ||  // CP – OS/2 const Color Pointer
                (fileHeader.bfType == (WORD)0x4D42) ||  // IC – OS/2 struct Icon
                (fileHeader.bfType == (WORD)0x4D42))    // PT – OS/2 Pointer
            {
                // check for OS2?
                // must have typedef: BITMAPCOREHEADER, OS21XBITMAPHEADER, BITMAPCOREHEADER2, OS22XBITMAPHEADER

                // BITMAPINFOHEADER

                fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, file);

                // only supports uncompressed for now
                if (infoHeader.biCompression == 0 && infoHeader.biClrUsed == 0)
                {
                    // skip and goto start of pixel array
                    fseek(file, fileHeader.bfOffBits, SEEK_SET);

                    // no endian swap:
                    //image->width = infoHeader.biWidth;
                    //image->height = abs(infoHeader.biHeight);
                    //image->pixel_bits = infoHeader.biBitCount;

                    // only supports 24 and 32 bpp for now...
                    if (infoHeader.biBitCount == 24 ||
                        infoHeader.biBitCount == 32)
                    {
                        image->width = infoHeader.biWidth;
                        image->height = infoHeader.biHeight;
                        image->redBits = 8;
                        image->greenBits = 8;
                        image->blueBits = 8;
                        image->alphaBits = 8;
                        // include alpha channel even if RGB
                        image->pixelBits = 32;
                        image->pixelBytes = 4;

                        image->data = malloc(image->width * image->height * image->pixelBytes);

                        if (image->data)
                        {
                            // start writing at pixels
                            p = (unsigned char*)image->data;

                            switch (infoHeader.biBitCount)
                            {
                                case 24:    

                                    for (i = image->height; i > 0; --i)
                                    {
                                        for (j = image->width; j > 0; --j)
                                        {
                                            // stored as BGR
                                            // assume B8G8R8
                    
                                            // throw in alpha to make pixel 4 byte-aligned
                                            p[3] = 255;
                                            p[2] = fgetc(file);
                                            p[1] = fgetc(file);
                                            p[0] = fgetc(file);

                                            // move to next pixel (4 bytes)
                                            p += 4;
                                        }

                                        // for 24-bit images, rows are padded to multiples of 4
                                        fseek(file, infoHeader.biWidth % 4, SEEK_CUR);
                                    }
                            
                                    break;

                                case 32:

                                    for (i = image->width * image->height; i > 0; --i)
                                    {
                                        // stored as BGRA
                                        // assume B8G8R8A8

                                        p[2] = fgetc(file);
                                        p[1] = fgetc(file);
                                        p[0] = fgetc(file);
                                        p[3] = fgetc(file);

                                        // move to next pixel (4 bytes)
                                        p += 4;
                                    }
                            }

                            ret = 1;
                        }
                    }
                }
            }

            fclose(file);
        }
    }
    
    return ret;
}

#if 0

//--------------------------------------------------
    // WORK ON:
    //--------------------------------------------------

    //--------------------------------------------------
    // BITMAPINFOHEADER, BITMAPV4HEADER, or BITMAPV5HEADER.
    //--------------------------------------------------

    bool bottomUp = true; // normal way of doing this

    // VER. 1 OF DOING THIS...
    //-----------------------------------------------------------------------------
    #if 0
    // if format is uncompressed RGB
    if ( bmpInfoHeader.biCompression == BI_RGB )
    {
        // if height is positive
        if ( bmpInfoHeader.biHeight > 0 )
        {
            // it's a bottom-up DIB with the origin at the lower left corner
            bottomUp = true;
        }
        // if height is negative
        else if ( bmpInfoHeader.biHeight < 0 )
        {
            // it's a top-down DIB with the origin at the upper left corner
            bottomUp = false;
        }
    }
    /*
    // http://en.wikipedia.org/wiki/YUV
    else if ( bmpInfoHeader.biCompression == YUV ) // TODO
    {
        // For YUV bitmaps, the bitmap is always top-down, regardless of the sign of biHeight.
        // Decoders should offer YUV formats with postive biHeight, but for backward compatibility
        // they should accept YUV formats with either positive or negative biHeight.
        bottomUp = false;
    }
    //*/
    // if compressed **WHAT DOES IT MEAN TO BE COMPRESSED?**
    else // TODO
    {
        // For compressed formats, biHeight must be positive, regardless of image orientation
        if ( bmpInfoHeader.biHeight < 0 )
        {
            return IMAGE_ERROR_CODE_BMP_INVALID_HEIGHT;
        }
        else if ( bmpInfoHeader.biHeight > 0 )
        {
            // bottomUp = false; // TODO
        }
    }
    #endif
    //------------------------------------------------------------------------------------------------

    // VER. 2 OF DOING THIS...
    //------------------------------------------------------------------------------------------------
    #if 1
    if ( bmpInfoHeader.biHeight > 0 )
    {
        /*
        // For YUV bitmaps, the bitmap is always top-down, regardless of the sign of biHeight.
        // Decoders should offer YUV formats with postive biHeight, but for backward compatibility
        // they should accept YUV formats with either positive or negative biHeight.
        if ( bmpInfoHeader.* == YUV )
        {
            bottomUp = false;
        }
        //*/
    }
    else if ( bmpInfoHeader.biHeight < 0 )
    {
        /*
        // For compressed formats, biHeight must be positive, regardless of image orientation.
        if ( bmpInfoHeader.biCompression == #compressed# )
        {
            return false;
        }
        //*/
        
        // bottomUp = false;
    }
    #endif
    //------------------------------------------------------------------------------------------------

    // biPlanes specifies the number of planes for the target device. This value must be set to 1.
    if ( bmpInfoHeader.biPlanes != 1 )
    {
        return IMAGE_ERROR_CODE_BMP_INALID_BITPLANES;
    }

    // Specifies the number of bits per pixel (bpp).
    // For uncompressed formats, this value is the average number of bits per pixel.
    // For compressed formats, this value is the implied bit depth
    // of the uncompressed image, after the image has been decoded.
    mPixelDepth = bmpInfoHeader.biBitCount; // local var. NOT USED
    BYTE bitCountRGB[ 3 ] = { 0, 0, 0 };

    // The BITMAPINFOHEADER structure may be followed
    // by an array of palette entries or color masks.
    // The rules depend on the value of biCompression.
    bool colorTable = false;
    RGBQUAD* pColorTable = nullptr;
    unsigned int sizeColorTable = 0;
    unsigned int bitMasksSize = 0;

    // Uncompressed RGB.
    if ( bmpInfoHeader.biCompression == BI_RGB )
    {
        // If biCompression equals BI_RGB and the bitmap uses 8 bpp or less,
        // the bmpInfoHeader has a color table immediatelly following the BITMAPINFOHEADER structure.
        if ( bmpInfoHeader.biBitCount <= 8 )
        {
            // for bpp <= 8, colorTable is mandatory
            colorTable = true;
        }
        // For 16-bpp bitmaps, if biCompression equals BI_RGB, the format is always RGB 555
        else if ( bmpInfoHeader.biBitCount == 16 )
        {
            bitCountRGB[ 0 ] = 5;
            bitCountRGB[ 1 ] = 5;
            bitCountRGB[ 2 ] = 5;
        }
    }
    // Uncompressed RGB with color masks. Valid for 16-bpp and 32-bpp bitmaps.
    else if ( bmpInfoHeader.biCompression == BI_BITFIELDS )
    {
        colorTable = true;

        // If biCompression equals BI_BITFIELDS, (refer to case BI_RGB above)
        // the format is either RGB 555 or RGB 565.
        // Use the subtype GUID in the AM_MEDIA_TYPE structure to determine the specific RGB type.
        if ( bmpInfoHeader.biBitCount == 16 )
        {
            // TODO:
            /*
            bitCountRGB[ 0 ] = 5;
            bitCountRGB[ 1 ] = 5;
            bitCountRGB[ 2 ] = 5;
            // OR
            bitCountRGB[ 0 ] = 5;
            bitCountRGB[ 1 ] = 6;
            bitCountRGB[ 2 ] = 5;
            */
        }
        /*
        // for 32-bpp ?
        // not yet supported
        else
        {

        }
        */
    }
    // Other compression types not yet supported.
    else
    {
        return IMAGE_ERROR_CODE_BMP_UNSUPPORTED_COMPRESSION_TYPE;
    }
    
    // if the BITMAPINFOHEADER structure is followed by
    // an array of palette entries or color masks.
    // The rules depend on the value of biCompression.
    if ( colorTable )
    {
        // If uncompressed RGB
        if ( bmpInfoHeader.biCompression == BI_RGB )
        {
            // The size of the array is given by the biClrUsed member.
            // If biClrUsed is zero, the array contains the maximum number
            // of colors for the given bitdepth; that is, 2 ^ biBitCount colors.
            if ( bmpInfoHeader.biClrUsed == 0 )
            {
                // 1 << bpp = 2 ^ bpp
                sizeColorTable = 1 << bmpInfoHeader.biBitCount;
                pColorTable = new RGBQUAD[ sizeColorTable ];
            }
            else
            {
                // The size of the array is given by the biClrUsed member.
                sizeColorTable = bmpInfoHeader.biClrUsed;                
                pColorTable = new RGBQUAD[ sizeColorTable ];
            }

            // If biCompression equals BI_RGB and the bitmap uses 8 bpp or less,
            // the bitmap has a color table immediatelly following the BITMAPINFOHEADER structure.
            if ( bmpInfoHeader.biBitCount <= 8 )
            {
                // TODO: read in values to mColorTableValues
            }
            // TODO:
            /*
            else
            {
                
            }
            */
        }
        // If biCompression equals BI_BITFIELDS,
        // the bitmap uses three DWORD color masks (red, green, and blue, respectively),
        // which specify the byte layout of the pixels.
        // The 1 bits in each mask indicate the bits for that color within the pixel. 
        else if ( bmpInfoHeader.biCompression == BI_BITFIELDS )
        {
            // TODO: read 3 DWORD after BITMAPINFOHEADER, then proceed to the color table
            // start at sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER ) + 12
            bitMasksSize = 12;
        }
        /*
        // maybe don't even need this
        else if ( bmpInfoHeader.biCompression == BI_ALPHABITFIELDS )
        {
            // almost same as above
            // start at sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER ) + 16 (for extra alpha mask)
            bitMasksSize = 16;
        }
        */
        /*
        TODO:
        // If biCompression is a video FOURCC,
        // the presence of a color table is implied by the video format.
        // You should not assume that a color table exists when
        // the bit depth is 8 bpp or less.
        // However, some legacy components might assume that a color table is present.
        // Therefore, if you are allocating a BITMAPINFOHEADER structure,
        // it is recommended to allocate space for a color table when
        // the bit depth is 8 bpp or less, even if the color table is not used.
        else if ( mBitmapInfoHeader.biCompression == FOURCC ) // TODO
        {
                
        }
        */
        /*
        // Not yet supported
        else
        {

        }
        */
    }

    //--------------------------------------------------
    // Pixel array.
    //--------------------------------------------------

    // http://en.wikipedia.org/wiki/BMP_file_format

    unsigned int pixelRowSize_notPadded = bmpInfoHeader.biBitCount * bmpInfoHeader.biWidth / 8; // REVIEW!
    unsigned int pixelRowSize = ( ( bmpInfoHeader.biBitCount * bmpInfoHeader.biWidth + 31  ) / 32 ) * 4;
    unsigned int pixelArraySize = pixelRowSize * std::abs( bmpInfoHeader.biHeight ); // bitHeight can be negative

    // NOTE (from wiki link):
    // for bpp <= 8, FileSize ~= 54 + 4 * 2^bpp + pixelArraySize
    // for bpp <= 8, FileSize ~= 54 + pizelArraySize

    // 54 = sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER )
    // 4 * 2^n  is the size of the color palette in bytes

    // ~= b/c:
    // size of the color palette will be 3 * 2^n bytes for the OS/2 DIB header version BITMAPCOREHEADER,
    // some files may define only the number of colors needed by the image, potentially fewer than 2^n
    // optional presence of the 12 or 16 bytes needed for the extra bit masks stored immediately after the BITMAPINFOHEADER DIB header
    // the variable-size GAP depicted in Diag.1 (see wiki link)

    unsigned int pixelArrayOffset = sizeof( BITMAPFILEHEADER ) +
                                    sizeof( BITMAPINFOHEADER ); // sum should be 54 so far?;

    if ( bmpInfoHeader.biBitCount <= 8 )
    {
        if ( OS2 )
        {
            pixelArrayOffset += 3 * ( sizeColorTable ); // size of color palette
        }
        else
        {
            pixelArrayOffset += 4 * ( sizeColorTable ); // size of color palette
        }

        pixelArrayOffset += bitMasksSize;
    }
    // > 8
    else
    {
        // NOTE: color table can be used if > 8 bpp, just not mandatory
    }

    unsigned int fileSize = pixelArrayOffset + pixelArraySize;

    // NEED TO DO EXTRA FOR FILE SIZE

    // USE THIS TO CHECK FOR BUGS
    if ( fileSize != bmpFileHeader.bfSize )
    {
        return IMAGE_ERROR_CODE_BMP_FILE_SIZE_MISSMATCH;
    }

    // USE THIS TO CHECK FOR BUGS
    if ( pixelArrayOffset != bmpFileHeader.bfOffBits )
    {
        return IMAGE_ERROR_CODE_BMP_PIXEL_ARRAY_OFFSET_MISSMATCH;
    }

    // copy pixels
    for ( unsigned int rowIndex = 0; rowIndex < pixelArraySize; rowIndex += pixelRowSize )
    {
        memcpy( mPixels, /*file( pixelArrayOffset + rowIndex )*/ NULL, pixelRowSize_notPadded );
    }

    //---------------------------

    // http://msdn.microsoft.com/en-us/library/aa452885.aspx

    switch( bmpInfoHeader.biBitCount )
    {
    case 1: // monochrome

        unsigned char* pixels_mc = new unsigned char[ 10 ];

        for ( unsigned int i = 0; i < pixelArraySize; ++i )
        {
            //mPixels
        }

        break;
    }

    //---------------------------

#endif