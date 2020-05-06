#include "mglm.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "vec.h"
#include "mat.h"

const static float toRad = (float)(M_PI) / 180.0f;
const static float toDeg = 180.0f / (float)(M_PI);

static int i;
static int j;
static int k;

void mglmLoadIdentity(float* mat4)
{
    mat4_identity(mat4);
}

void mglmLoadFrustum(float* mat4, float left, float right, float bottom, float top, float zNear, float zFar)
{
    mat4[0] = 2.0f * zNear / (right - left);
    mat4[1] = 0.0f;
    mat4[2] = 0.0f;
    mat4[3] = 0.0f;

    mat4[4] = 0.0f;
    mat4[5] = 2.0f * zNear / (top - bottom);
    mat4[6] = 0.0f;
    mat4[7] = 0.0f;

    mat4[8] = (right + left) / (right - left);
    mat4[9] = (top + bottom) / (top - bottom);
    mat4[10] = -(zFar + zNear) / (zFar - zNear);
    mat4[11] = -1.0f;

    mat4[12] = 0.0f;
    mat4[13] = 0.0f;
    mat4[14] = -2.0f * zFar * zNear / (zFar - zNear);
    mat4[15] = 0.0f;
}

void mglmLoadOrtho(float* mat4, float left, float right, float bottom, float top, float zNear, float zFar)
{
    mat4[0] = 2.0f / (right - left);
    mat4[1] = 0.0f;
    mat4[2] = 0.0f;
    mat4[3] = 0.0f;

    mat4[4] = 0.0f;
    mat4[5] = 2.0f / (top - bottom);
    mat4[6] = 0.0f;
    mat4[7] = 0.0f;

    mat4[8] = 0.0f;
    mat4[9] = 0.0f;
    mat4[10] = -2.0f / (zFar - zNear);
    mat4[11] = 0.0f;

    mat4[12] = (right + left) / (right - left);
    mat4[13] = (top + bottom) / (top - bottom);
    mat4[14] = (zFar + zNear) / (zFar - zNear);
    mat4[15] = 1.0f;
}

void mglmLoadPerspective(float* mat4, float fov, float aspect, float zNear, float zFar)
{
    float halfHeight = zNear * (float)tan(fov / 2.0f * toRad);
    float halfWidth = halfHeight * aspect;

    mglmLoadFrustum(mat4, -halfWidth, halfWidth, -halfHeight, halfHeight, zNear, zFar);
}

void mglmFrustum(float* mat4, float left, float right, float bottom, float top, float zNear, float zFar)
{
    float tmp[16];
    
    mglmLoadFrustum(mat4, left, right, bottom, top, zNear, zFar);

    // mat4_mult_mat4_rgt(tmp, mat4);
    mat4_mult_mat4_lft(mat4, tmp);
}

void mglmOrtho(float* mat4, float left, float right, float bottom, float top, float zNear, float zFar)
{
    float tmp[16];
    
    mglmLoadOrtho(mat4, left, right, bottom, top, zNear, zFar);

    // mat4_mult_mat4_rgt(tmp, mat4);
    mat4_mult_mat4_lft(mat4, tmp);
}

void mglmPerspective(float* mat4, float fov, float aspect, float zNear, float zFar)
{
    float halfHeight = zNear * (float)tan(fov / 2.0f * toRad);
    float halfWidth = halfHeight * aspect;

    mglmFrustum(mat4, -halfWidth, halfWidth, -halfHeight, halfHeight, zNear, zFar);
}

void mglmRotate(float* mat4, float angle, float x, float y, float z)
{
    // consult http://en.wikipedia.org/wiki/Rotation_matrix

    float tmp[16];

    float theta = angle * toRad;
    float s = (float)sin(theta);
    float c = (float)cos(theta);
    float ci = 1.0f - c;

    tmp[0] = x * x * ci + c;
    tmp[1] = x * y * ci + z * s;
    tmp[2] = x * z * ci - y * s; // remove y * s for cool shear effect
    tmp[3] = 0.0f;

    tmp[4] = y * x * ci - z * s;
    tmp[5] = y * y * ci + c;
    tmp[6] = y * z * ci + x * s; // remove x * s for leaning character
    tmp[7] = 0.0f;

    tmp[8]  = z * x * ci + y * s; // remove y * s for cool shear effect
    tmp[9]  = z * y * ci - x * s; // remove x * s for cool shear effect
    tmp[10] = z * z * ci + c;
    tmp[11] = 0.0f;

    tmp[12] = 0.0f;
    tmp[13] = 0.0f;
    tmp[14] = 0.0f;
    tmp[15] = 1.0f;

    // mat4_mult_mat4_rgt(tmp, mat4);
    mat4_mult_mat4_lft(mat4, tmp);
}

void mglmRotateX(float* mat4, float angle)
{
    float tmp[16];

    float theta = angle * toRad;
    float s = (float)sin(theta);
    float c = (float)cos(theta);
    
    tmp[0] = 1.0f; tmp[4] = 0.0f; tmp[8]  = 0.0f; tmp[12] = 0.0f;
    tmp[1] = 0.0f; tmp[5] = c;    tmp[9]  = -s;   tmp[13] = 0.0f;
    tmp[2] = 0.0f; tmp[6] = s;    tmp[10] = c;    tmp[14] = 0.0f;
    tmp[3] = 0.0f; tmp[7] = 0.0f; tmp[11] = 0.0f; tmp[15] = 1.0f;

    // mat4_mult_mat4_rgt(tmp, mat4);
    mat4_mult_mat4_lft(mat4, tmp);
}

void mglmRotateY(float* mat4, float angle)
{
    float tmp[16];

    float theta = angle * toRad;
    float s = (float)sin(theta);
    float c = (float)cos(theta);
    
    tmp[0] = c;    tmp[4] = 0.0f; tmp[8]  = s;    tmp[12] = 0.0f;
    tmp[1] = 0.0f; tmp[5] = 1.0f; tmp[9]  = 0.0f; tmp[13] = 0.0f;
    tmp[2] = -s;   tmp[6] = 0.0f; tmp[10] = c;    tmp[14] = 0.0f;
    tmp[3] = 0.0f; tmp[7] = 0.0f; tmp[11] = 0.0f; tmp[15] = 1.0f;

    // mat4_mult_mat4_rgt(tmp, mat4);
    mat4_mult_mat4_lft(mat4, tmp);
}

void mglmRotateZ(float* mat4, float angle)
{
    float tmp[16];

    float theta = angle * toRad;
    float s = (float)sin(theta);
    float c = (float)cos(theta);
    
    tmp[0] = c;    tmp[4] = -s;   tmp[8]  = 0.0f; tmp[12] = 0.0f;
    tmp[1] = s;    tmp[5] = c;    tmp[9]  = 0.0f; tmp[13] = 0.0f;
    tmp[2] = 0.0f; tmp[6] = 0.0f; tmp[10] = 1.0f; tmp[14] = 0.0f;
    tmp[3] = 0.0f; tmp[7] = 0.0f; tmp[11] = 0.0f; tmp[15] = 1.0f;

    // mat4_mult_mat4_rgt(tmp, mat4);
    mat4_mult_mat4_lft(mat4, tmp);
}

void mglmScale(float* mat4, float x, float y, float z)
{
    float tmp[16];

    mglmZero(tmp);

    tmp[0]  = x;
    tmp[5]  = y;
    tmp[10] = z;
    tmp[15] = 1.0f;

    // mat4_mult_mat4_rgt(tmp, mat4);
    mat4_mult_mat4_lft(mat4, tmp);
}

void mglmTranslate(float* mat4, float x, float y, float z)
{
    float tmp[16];

    mglmLoadIdentity(tmp);

    tmp[12] = x;
    tmp[13] = y;
    tmp[14] = z;

    // mat4_mult_mat4_rgt(tmp, mat4);
    mat4_mult_mat4_lft(mat4, tmp);
}

void mglmZero(float* mat4)
{
    mat4_zero(mat4);
}

/*
    tmp[0] = ; tmp[4] = ; tmp[8]  = ; tmp[12] = ;
    tmp[1] = ; tmp[5] = ; tmp[9]  = ; tmp[13] = ;
    tmp[2] = ; tmp[6] = ; tmp[10] = ; tmp[14] = ;
    tmp[3] = ; tmp[7] = ; tmp[11] = ; tmp[15] = ;
*/

/*
    tmp[0] = ;
    tmp[1] = ;
    tmp[2] = ;
    tmp[3] = ;

    tmp[4] = ;
    tmp[5] = ;
    tmp[6] = ;
    tmp[7] = ;

    tmp[8] = ;
    tmp[9] = ;
    tmp[10] = ;
    tmp[11] = ;

    tmp[12] = ;
    tmp[13] = ;
    tmp[14] = ;
    tmp[15] = ;
*/