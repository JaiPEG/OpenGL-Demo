#ifndef BMP_H221
#define BMP_H221

#include "image.h"
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int loadBmp(const char* fileName, Image* image);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // BMP_H221