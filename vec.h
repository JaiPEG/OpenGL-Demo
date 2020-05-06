#ifndef VEC_H221
#define VEC_H221

typedef int BOOL;

#ifndef TRUE
#define TRUE 1
#endif // TRUE

#ifndef FALSE
#define FALSE 0
#endif // FALSE

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void vec2_zero(float* vec2_dst);
void vec2_set(float* vec2_dst, float x, float y);
void vec2_setv(float* vec2_dst, const float* vec2_src);
void vec2_add(float* vec2_dst, float x, float y);
void vec2_add_dst(float* vec2_dst, const float* vec2_src, float x, float y);
void vec2_addv(float* vec2_dst, const float* vec2_src);
void vec2_addv_dst(float* vec2_dst, const float* vec2_srca, const float* vec2_srcb);
void vec2_sub(float* vec2_dst, float x, float y);
void vec2_sub_dst(float* vec2_dst, const float* vec2_src, float x, float y);
void vec2_subv(float* vec2_dst, const float* vec2_src);
void vec2_subv_dst(float* vec2_dst, const float* vec2_srca, const float* vec2_srcb);
void vec2_mult(float* vec2_dst, float scalar);
void vec2_mult_dst(float* vec2_dst, const float* vec2_src, float scalar);
void vec2_multv(float* vec2_dst, const float* vec2_src);
void vec2_multv_dst(float* vec2_dst, const float* vec2_srca, const float* vec2_srcb);
float vec2_magnitude(const float* vec2_src);
float vec2_magnitude_inv(const float* vec2_src);
float vec2_magnitude_sq(const float* vec2_src);
void vec2_normalize(float* vec2_dst);
void vec2_normalize_dst(float* vec2_dst, const float* vec2_src);
void vec2_rotate(float* vec2_dst, float angle);
void vec2_rotate_dst(float* vec2_dst, const float* vec2_src, float angle);
float vec2_dot(const float* vec2_srca, const float* vec2_srcb);
float vec2_angle(const float* vec2_srca, const float* vec2_srcb);
float vec2_angle_normalize(const float* vec2_srca, const float* vec2_srcb);
BOOL vec2_longer(const float* vec2_srca, const float* vec2_srcb);
BOOL vec2_shorter(const float* vec2_srca, const float* vec2_srcb);

void vec3_zero(float* vec3_dst);
void vec3_set(float* vec3_dst, float x, float y, float z);
void vec3_setv(float* vec3_dst, const float* vec3_src);
void vec3_add(float* vec3_dst, float x, float y, float z);
void vec3_add_dst(float* vec3_dst, const float* vec3_src, float x, float y, float z);
void vec3_addv(float* vec3_dst, const float* vec3_src);
void vec3_addv_dst(float* vec3_dst, const float* vec3_srca, const float* vec3_srcb);
void vec3_sub(float* vec3_dst, float x, float y, float z);
void vec3_sub_dst(float* vec3_dst, const float* vec3_src, float x, float y, float z);
void vec3_subv(float* vec3_dst, const float* vec3_src);
void vec3_subv_dst(float* vec3_dst, const float* vec3_srca, const float* vec3_srcb);
void vec3_mult(float* vec3_dst, float scalar);
void vec3_mult_dst(float* vec3_dst, const float* vec3_src, float scalar);
void vec3_multv(float* vec3_dst, const float* vec3_src);
void vec3_multv_dst(float* vec3_dst, const float* vec3_srca, const float* vec3_srcb);
float vec3_magnitude(const float* vec3_src);
float vec3_magnitude_inv(const float* vec3_src);
float vec3_magnitude_sq(const float* vec3_src);
void vec3_normalize(float* vec3_dst);
void vec3_normalize_dst(float* vec3_dst, const float* vec3_src);
float vec3_dot(const float* vec3_srca, const float* vec3_srcb);
float vec3_angle(const float* vec3_srca, const float* vec3_srcb);
float vec3_angle_normalize(const float* vec3_srca, const float* vec3_srcb);
void vec3_cross_dst(float* vec3_dst, const float* vec3_srca, const float* vec3_srcb);
BOOL vec3_longer(const float* vec3_srca, const float* vec3_srcb);
BOOL vec3_shorter(const float* vec3_srca, const float* vec3_srcb);

void vec4_zero(float* vec4_dst);
void vec4_zerow(float* vec4_dst);
void vec4_set(float* vec4_dst, float x, float y, float z, float w);
void vec4_setv(float* vec4_dst, const float* vec4_src);
void vec4_add(float* vec4_dst, float x, float y, float z, float w);
void vec4_add_dst(float* vec4_dst, const float* vec4_src, float x, float y, float z, float w);
void vec4_addv(float* vec4_dst, const float* vec4_src);
void vec4_addv_dst(float* vec4_dst, const float* vec4_srca, const float* vec4_srcb);
void vec4_sub(float* vec4_dst, float x, float y, float z, float w);
void vec4_sub_dst(float* vec4_dst, const float* vec4_src, float x, float y, float z, float w);
void vec4_subv(float* vec4_dst, const float* vec4_src);
void vec4_subv_dst(float* vec4_dst, const float* vec4_srca, const float* vec4_srcb);
void vec4_mult(float* vec4_dst, float scalar);
void vec4_mult_dst(float* vec4_dst, const float* vec4_src, float scalar);
void vec4_multv(float* vec4_dst, const float* vec4_src);
void vec4_multv_dst(float* vec4_dst, const float* vec4_srca, const float* vec4_srcb);
float vec4_dot(const float* vec4_srca, const float* vec4_srcb);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // VEC_H221