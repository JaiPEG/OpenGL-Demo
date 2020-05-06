#include "frustum.h"

#define _USE_MATH_DEFINES
#include <math.h.>

void frustum_calc(Frustum* frustum, const View* view)
{
    const float toRad = (float)(M_PI) / 180.0f;
    
    float halfHeight = view->zNear * (float)tan(view->fov / 2.0f * toRad);
    float halfWidth = halfHeight * view->aspect;

    frustum->left = -halfWidth;
    frustum->right = halfWidth;
    frustum->bottom = -halfHeight;
    frustum->top = halfHeight;
    frustum->zNear = view->zNear;
    frustum->zFar = view->zFar;
}

void frustum_offset(Frustum* frustum, float x, float y)
{
    frustum->left += x;
    frustum->right += x;
    frustum->bottom += y;
    frustum->top += y;
}

void frustum_offset_relative(Frustum* frustum, float x, float y)
{
    float width = frustum->right - frustum->left;
    float height = frustum->top - frustum->bottom;

    float dx = width * x;
    float dy = height * y;
    
    frustum->left += dx;
    frustum->right += dx;
    frustum->bottom += dy;
    frustum->top += dy;
}

float frustum_aspect(const Frustum* frustum)
{
    return (frustum->right - frustum->left) / 
           (frustum->top - frustum->bottom);
}