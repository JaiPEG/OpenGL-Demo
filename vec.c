#include "vec.h"

#define _USE_MATH_DEFINES
#include <math.h>

const static float toRad = (float)(M_PI) / 180.0f;
const static float toDeg = 180.0f / (float)(M_PI);

static unsigned int i;

/* VEC2 */

void vec2_zero(float* vec2_dst)
{
    for (i = 0; i < 2; ++i)
    {
        vec2_dst[i] = 0.0f;
    }
}

void vec2_set(float* vec2_dst, float x, float y)
{
    vec2_dst[0] = x;
    vec2_dst[1] = y;
}

void vec2_setv(float* vec2_dst, const float* vec2_src)
{
    for (i = 0; i < 2; ++i)
    {
        vec2_dst[i] = vec2_src[i];
    }
}

void vec2_add(float* vec2_dst, float x, float y)
{
    vec2_dst[0] += x;
    vec2_dst[1] += y;
}

void vec2_add_dst(float* vec2_dst, const float* vec2_src, float x, float y)
{
    vec2_dst[0] = vec2_src[0] + x;
    vec2_dst[1] = vec2_src[1] + y;
}

void vec2_addv(float* vec2_dst, const float* vec2_src)
{
    for (i = 0; i < 2; ++i)
    {
        vec2_dst[i] += vec2_src[i];
    }
}

void vec2_addv_dst(float* vec2_dst, const float* vec2_srca, const float* vec2_srcb)
{
    for (i = 0; i < 2; ++i)
    {
        vec2_dst[i] = vec2_srca[i] + vec2_srcb[i];
    }
}

void vec2_sub(float* vec2_dst, float x, float y)
{
    vec2_dst[0] -= x;
    vec2_dst[1] -= y;
}

void vec2_sub_dst(float* vec2_dst, const float* vec2_src, float x, float y)
{
    vec2_dst[0] = vec2_src[0] - x;
    vec2_dst[1] = vec2_src[1] - y;
}

void vec2_subv(float* vec2_dst, const float* vec2_src)
{
    for (i = 0; i < 2; ++i)
    {
        vec2_dst[i] -= vec2_src[i];
    }
}

void vec2_subv_dst(float* vec2_dst, const float* vec2_srca, const float* vec2_srcb)
{
    for (i = 0; i < 2; ++i)
    {
        vec2_dst[i] = vec2_srca[i] - vec2_srcb[i];
    }
}

void vec2_mult(float* vec2_dst, float scalar)
{
    vec2_dst[0] *= scalar;
    vec2_dst[1] *= scalar;
}

void vec2_mult_dst(float* vec2_dst, const float* vec2_src, float scalar)
{
    vec2_dst[0] = vec2_src[0] * scalar;
    vec2_dst[1] = vec2_src[1] * scalar;
}

void vec2_multv(float* vec2_dst, const float* vec2_src)
{
    for (i = 0; i < 2; ++i)
    {
        vec2_dst[i] *= vec2_src[i];
    }
}

void vec2_multv_dst(float* vec2_dst, const float* vec2_srca, const float* vec2_srcb)
{
    for (i = 0; i < 2; ++i)
    {
        vec2_dst[i] = vec2_srca[i] * vec2_srcb[i];
    }
}

float vec2_magnitude(const float* vec2_src)
{
    return (float)sqrt(vec2_magnitude_sq(vec2_src));
}

float vec2_magnitude_inv(const float* vec2_src)
{
    return 1.0f / vec2_magnitude(vec2_src);
}

float vec2_magnitude_sq(const float* vec2_src)
{
    return vec2_src[0] * vec2_src[0] +
           vec2_src[1] * vec2_src[1];
}

void vec2_normalize(float* vec2_dst)
{
    float magnitude_inv = vec2_magnitude_inv(vec2_dst);

    vec2_mult(vec2_dst, magnitude_inv);
}

void vec2_normalize_dst(float* vec2_dst, const float* vec2_src)
{
    float magnitude_inv = vec2_magnitude_inv(vec2_dst);

    vec2_mult_dst(vec2_dst, vec2_src, magnitude_inv);
}

void vec2_rotate(float* vec2_dst, float angle)
{
    float tmp[2] = {vec2_dst[0], vec2_dst[1]};
    float theta = angle * toRad;
    float c = (float)cos(theta);
    float s = (float)sin(theta);
    
    vec2_dst[0] = tmp[0] * c - tmp[1] * s;
    vec2_dst[1] = tmp[0] * s + tmp[1] * c;
}

void vec2_rotate_dst(float* vec2_dst, const float* vec2_src, float angle)
{
    float theta = angle * toRad;
    float c = (float)cos(theta);
    float s = (float)sin(theta);
    
    vec2_dst[0] = vec2_src[0] * c - vec2_src[1] * s;
    vec2_dst[1] = vec2_src[0] * s + vec2_src[1] * c;
}

float vec2_dot(const float* vec2_srca, const float* vec2_srcb)
{
    return vec2_srca[0] * vec2_srcb[0] +
           vec2_srca[1] * vec2_srcb[1];
}

float vec2_angle(const float* vec2_srca, const float* vec2_srcb)
{
    return (float)acos(vec2_dot(vec2_srca, vec2_srcb)) * toDeg;
}

float vec2_angle_normalize(const float* vec2_srca, const float* vec2_srcb)
{
    return (float)acos(vec2_dot(vec2_srca, vec2_srcb) / (vec2_magnitude(vec2_srca) * vec2_magnitude(vec2_srcb))) * toDeg;
}

BOOL vec2_longer(const float* vec2_srca, const float* vec2_srcb)
{
    return vec2_magnitude_sq(vec2_srca) > vec2_magnitude_sq(vec2_srcb);
}

BOOL vec2_shorter(const float* vec2_srca, const float* vec2_srcb)
{
    return vec2_magnitude_sq(vec2_srca) < vec2_magnitude_sq(vec2_srcb);
}

/* VEC3 */

void vec3_zero(float* vec3_dst)
{
    for (i = 0; i < 3; ++i)
    {
        vec3_dst[i] = 0.0f;
    }
}

void vec3_set(float* vec3_dst, float x, float y, float z)
{
    vec3_dst[0] = x;
    vec3_dst[1] = y;
    vec3_dst[2] = z;
}

void vec3_setv(float* vec3_dst, const float* vec3_src)
{
    for (i = 0; i < 3; ++i)
    {
        vec3_dst[i] = vec3_src[i];
    }
}

void vec3_add(float* vec3_dst, float x, float y, float z)
{
    vec3_dst[0] += x;
    vec3_dst[1] += y;
    vec3_dst[2] += z;
}

void vec3_add_dst(float* vec3_dst, const float* vec3_src, float x, float y, float z)
{
    vec3_dst[0] = vec3_src[0] + x;
    vec3_dst[1] = vec3_src[1] + y;
    vec3_dst[2] = vec3_src[2] + z;
}

void vec3_addv(float* vec3_dst, const float* vec3_src)
{
    for (i = 0; i < 3; ++i)
    {
        vec3_dst[i] += vec3_src[i];
    }
}

void vec3_addv_dst(float* vec3_dst, const float* vec3_srca, const float* vec3_srcb)
{
    for (i = 0; i < 3; ++i)
    {
        vec3_dst[i] = vec3_srca[i] + vec3_srcb[i];
    }
}

void vec3_sub(float* vec3_dst, float x, float y, float z)
{
    vec3_dst[0] -= x;
    vec3_dst[1] -= y;
    vec3_dst[2] -= z;
}

void vec3_sub_dst(float* vec3_dst, const float* vec3_src, float x, float y, float z)
{
    vec3_dst[0] = vec3_src[0] - x;
    vec3_dst[1] = vec3_src[1] - y;
    vec3_dst[2] = vec3_src[2] - z;
}

void vec3_subv(float* vec3_dst, const float* vec3_src)
{
    for (i = 0; i < 3; ++i)
    {
        vec3_dst[i] -= vec3_src[i];
    }
}

void vec3_subv_dst(float* vec3_dst, const float* vec3_srca, const float* vec3_srcb)
{
    for (i = 0; i < 3; ++i)
    {
        vec3_dst[i] = vec3_srca[i] - vec3_srcb[i];
    }
}

void vec3_mult(float* vec3_dst, float scalar)
{
    vec3_dst[0] *= scalar;
    vec3_dst[1] *= scalar;
    vec3_dst[2] *= scalar;
}

void vec3_mult_dst(float* vec3_dst, const float* vec3_src, float scalar)
{
    vec3_dst[0] = vec3_src[0] * scalar;
    vec3_dst[1] = vec3_src[1] * scalar;
    vec3_dst[2] = vec3_src[2] * scalar;
}

void vec3_multv(float* vec3_dst, const float* vec3_src)
{
    for (i = 0; i < 3; ++i)
    {
        vec3_dst[i] *= vec3_src[i];
    }
}

void vec3_multv_dst(float* vec3_dst, const float* vec3_srca, const float* vec3_srcb)
{
    for (i = 0; i < 3; ++i)
    {
        vec3_dst[i] = vec3_srca[i] * vec3_srcb[i];
    }
}

float vec3_magnitude(const float* vec3_src)
{
    return (float)sqrt(vec3_magnitude_sq(vec3_src));
}

float vec3_magnitude_inv(const float* vec3_src)
{
    return 1.0f / vec3_magnitude(vec3_src);
}

float vec3_magnitude_sq(const float* vec3_src)
{
    return vec3_src[0] * vec3_src[0] +
           vec3_src[1] * vec3_src[1] +
           vec3_src[2] * vec3_src[2];
}

void vec3_normalize(float* vec3_dst)
{
    float magnitude_inv = vec3_magnitude_inv(vec3_dst);

    vec3_mult(vec3_dst, magnitude_inv);
}

void vec3_normalize_dst(float* vec3_dst, const float* vec3_src)
{
    float magnitude_inv = vec3_magnitude_inv(vec3_dst);

    vec3_mult_dst(vec3_dst, vec3_src, magnitude_inv);
}

float vec3_dot(const float* vec3_srca, const float* vec3_srcb)
{
    return vec3_srca[0] * vec3_srcb[0] +
           vec3_srca[1] * vec3_srcb[1] +
           vec3_srca[2] * vec3_srcb[2];
}

float vec3_angle(const float* vec3_srca, const float* vec3_srcb)
{
    return (float)acos(vec3_dot(vec3_srca, vec3_srcb)) * toDeg;
}

float vec3_angle_normalize(const float* vec3_srca, const float* vec3_srcb)
{
    return (float)acos(vec3_dot(vec3_srca, vec3_srcb) / (vec3_magnitude(vec3_srca) * vec3_magnitude(vec3_srcb))) * toDeg;
}

void vec3_cross_dst(float* vec3_dst, const float* vec3_srca, const float* vec3_srcb)
{
    vec3_dst[0] = vec3_srca[1] * vec3_srcb[2] - vec3_srca[2] * vec3_srcb[1];
    vec3_dst[1] = vec3_srca[2] * vec3_srcb[0] - vec3_srca[0] * vec3_srcb[2];
    vec3_dst[2] = vec3_srca[0] * vec3_srcb[1] - vec3_srca[1] * vec3_srcb[0];
}

BOOL vec3_longer(const float* vec3_srca, const float* vec3_srcb)
{
    return vec3_magnitude_sq(vec3_srca) > vec3_magnitude_sq(vec3_srcb);
}

BOOL vec3_shorter(const float* vec3_srca, const float* vec3_srcb)
{
    return vec3_magnitude_sq(vec3_srca) < vec3_magnitude_sq(vec3_srcb);
}

/* VEC4 */

void vec4_zero(float* vec4_dst)
{
    vec4_dst[0] = 0.0f;
    vec4_dst[1] = 0.0f;
    vec4_dst[2] = 0.0f;
    vec4_dst[3] = 0.0f;
}

void vec4_zerow(float* vec4_dst)
{
    vec4_dst[0] = 0.0f;
    vec4_dst[1] = 0.0f;
    vec4_dst[2] = 0.0f;
    vec4_dst[3] = 1.0f;
}

void vec4_set(float* vec4_dst, float x, float y, float z, float w)
{
    vec4_dst[0] = x;
    vec4_dst[1] = y;
    vec4_dst[2] = z;
    vec4_dst[3] = w;
}

void vec4_setv(float* vec4_dst, const float* vec4_src)
{
    for (i = 0; i < 4; ++i)
    {
        vec4_dst[i] = vec4_src[i];
    }
}

void vec4_add(float* vec4_dst, float x, float y, float z, float w)
{
    vec4_dst[0] += x;
    vec4_dst[1] += y;
    vec4_dst[2] += z;
    vec4_dst[3] += w;
}

void vec4_add_dst(float* vec4_dst, const float* vec4_src, float x, float y, float z, float w)
{
    vec4_dst[0] = vec4_src[0] + x;
    vec4_dst[1] = vec4_src[1] + y;
    vec4_dst[2] = vec4_src[2] + z;
    vec4_dst[3] = vec4_src[3] + w;
}

void vec4_addv(float* vec4_dst, const float* vec4_src)
{
    for (i = 0; i < 4; ++i)
    {
        vec4_dst[i] += vec4_src[i];
    }
}

void vec4_addv_dst(float* vec4_dst, const float* vec4_srca, const float* vec4_srcb)
{
    for (i = 0; i < 4; ++i)
    {
        vec4_dst[i] = vec4_srca[i] + vec4_srcb[i];
    }
}

void vec4_sub(float* vec4_dst, float x, float y, float z, float w)
{
    vec4_dst[0] -= x;
    vec4_dst[1] -= y;
    vec4_dst[2] -= z;
    vec4_dst[3] -= w;
}

void vec4_sub_dst(float* vec4_dst, const float* vec4_src, float x, float y, float z, float w)
{
    vec4_dst[0] = vec4_src[0] - x;
    vec4_dst[1] = vec4_src[1] - y;
    vec4_dst[2] = vec4_src[2] - z;
    vec4_dst[3] = vec4_src[3] - w;
}

void vec4_subv(float* vec4_dst, const float* vec4_src)
{
    for (i = 0; i < 4; ++i)
    {
        vec4_dst[i] -= vec4_src[i];
    }
}

void vec4_subv_dst(float* vec4_dst, const float* vec4_srca, const float* vec4_srcb)
{
    for (i = 0; i < 4; ++i)
    {
        vec4_dst[i] = vec4_srca[i] - vec4_srcb[i];
    }
}

void vec4_mult(float* vec4_dst, float scalar)
{
    vec4_dst[0] *= scalar;
    vec4_dst[1] *= scalar;
    vec4_dst[2] *= scalar;
    vec4_dst[3] *= scalar;
}

void vec4_mult_dst(float* vec4_dst, const float* vec4_src, float scalar)
{
    vec4_dst[0] = vec4_src[0] * scalar;
    vec4_dst[1] = vec4_src[1] * scalar;
    vec4_dst[2] = vec4_src[2] * scalar;
    vec4_dst[3] = vec4_src[3] * scalar;
}

void vec4_multv(float* vec4_dst, const float* vec4_src)
{
    for (i = 0; i < 4; ++i)
    {
        vec4_dst[i] *= vec4_src[i];
    }
}

void vec4_multv_dst(float* vec4_dst, const float* vec4_srca, const float* vec4_srcb)
{
    for (i = 0; i < 4; ++i)
    {
        vec4_dst[i] = vec4_srca[i] * vec4_srcb[i];
    }
}

float vec4_dot(const float* vec4_srca, const float* vec4_srcb)
{
    return vec4_srca[0] * vec4_srcb[0] +
           vec4_srca[1] * vec4_srcb[1] +
           vec4_srca[2] * vec4_srcb[2] +
           vec4_srca[3] * vec4_srcb[3];
}