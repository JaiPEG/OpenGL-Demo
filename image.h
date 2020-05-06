#ifndef IMAGE_H221
#define IMAGE_H221

// origin: top-left
// order: R, G, B, A
// NO compression
// NO row padding
// ~ there may be internal padding within the pixel

typedef struct
{
    unsigned int width;         // pixels
    unsigned int height;        // pixels
    unsigned int redBits;       // bits
    unsigned int greenBits;     // bits
    unsigned int blueBits;      // bits
    unsigned int alphaBits;     // bits
    unsigned int pixelBits;     // bits: redBits + greenBits + blueBits + alphaBits
    unsigned int pixelBytes;    // bytes: (pixel_bits / 8) rounded up to nearest byte
    void* data;
} Image;

// size = pixel_bytes * width * height

#endif // IMAGE_H221