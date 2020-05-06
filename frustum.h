#ifndef FRUSTUM_H221
#define FRSUTUM_H221

#include "view.h"

typedef struct
{
    float left;
    float right;
    float bottom;
    float top;
    float zNear; // windows sucks...
    float zFar;
} Frustum;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void frustum_calc(Frustum* frustum, const View* view);
void frustum_offset(Frustum* frustum, float x, float y);
void frustum_offset_relative(Frustum* frustum, float x, float y);

float frustum_aspect(const Frustum* frustum);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // FRUSTUM_H221