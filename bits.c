#include "bits.h"

#define BITS_BYTE   8
#define BITS_INT    (sizeof(int) * BITS_BYTE)

BOOL isNeg(int i)
{
    return (int)((unsigned int)i >> (BITS_INT - 1));
}

BOOL isPos(int i)
{
    return (int)((unsigned int)(~i) >> (BITS_INT - 1));
}

BOOL isOppSigns(int a, int b)
{
    return ((a ^ b) < 0);
}

int abs(int i)
{
    int mask = i >> (BITS_INT - 1);

    return (i + mask) ^ mask;
}

int min(int a, int b)
{
    return b ^ ((a ^ b) & -(a < b));
}

int max(int a, int b)
{
    return a ^ ((a ^ b) & -(a < b));
}

BOOL isPow2(unsigned int i)
{
    return (i & (i - 1)) == 0;
}

unsigned int log2(unsigned int i)
{
    unsigned int l = 0;

    while (i >>= 1)
    {
        ++l;
    }

    return l;
}