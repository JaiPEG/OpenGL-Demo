#ifndef MAT_H221
#define MAT_H221

#ifndef COLUMN_MAJOR
#define COLUMN_MAJOR
#endif // COLUMN_MAJOR

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void mat2_copy(float* mat2_dst, const float* mat2_src);
void mat2_add_mat2(float* mat2_dst, const float* mat2_src);
void mat2_add_mat2_dst(float* mat2_dst, const float* mat2_srca, const float* mat2_srcb);
void mat2_sub_mat2_lft(float* mat2_dst, const float* mat2_src);
void mat2_sub_mat2_rgt(const float* mat2_src, float* mat2_dst);
void mat2_sub_mat2_dst(float* mat2_dst, const float* mat2_srca, const float* mat2_srcb);
void mat2_mult_scalar(float* mat2_dst, float scalar);
void mat2_mult_scalar_dst(float* mat2_dst, const float* mat2_src, float scalar);
void mat2_mult_mat2_lft(float* mat2_dst, const float* mat2_src);
void mat2_mult_mat2_rgt(const float* mat2_src, float* mat2_dst);
void mat2_mult_mat2_dst(float* mat2_dst, const float* mat2_srca, const float* mat2_srcb);
void mat2_mult_vec2_row(float* vec2_dst, const float* mat2_src);
void mat2_mult_vec2_col(const float* mat2_src, float* vec2_dst);
void mat2_mult_vec2_row_dst(float* vec2_dst, const float* vec2_src, const float* mat2_src);
void mat2_mult_vec2_col_dst(float* vec2_dst, const float* mat2_src, const float* vec2_src);
void mat2_transpose(float* mat2_dst);
void mat2_transpose_dst(float* mat2_dst, const float* mat2_src);
float mat2_determinant(const float* mat2_src);
void mat2_inverse(float* mat2_dst);
void mat2_inverse_dst(float* mat2_dst, const float* mat2_src);
void mat2_extract_mat3_dst(float* mat2_dst, const float* mat3_src);
void mat2_extract_mat4_dst(float* mat2_dst, const float* mat4_src);

void mat3_copy(float* mat3_dst, const float* mat3_src);
void mat3_add_mat3(float* mat3_dst, const float* mat3_src);
void mat3_add_mat3_dst(float* mat3_dst, const float* mat3_srca, const float* mat3_srcb);
void mat3_sub_mat3_lft(float* mat3_dst, const float* mat3_src);
void mat3_sub_mat3_rgt(const float* mat3_src, float* mat3_dst);
void mat3_sub_mat3_dst(float* mat3_dst, const float* mat3_srca, const float* mat3_srcb);
void mat3_mult_scalar(float* mat3_dst, float scalar);
void mat3_mult_scalar_dst(float* mat3_dst, const float* mat3_src, float scalar);
void mat3_mult_mat3_lft(float* mat3_dst, const float* mat3_src);
void mat3_mult_mat3_rgt(const float* mat3_src, float* mat3_dst);
void mat3_mult_mat3_dst(float* mat3_dst, const float* mat3_srca, const float* mat3_srcb);
void mat3_mult_vec3_row(float* vec3_dst, const float* mat3_src);
void mat3_mult_vec3_col(const float* mat3_src, float* vec3_dst);
void mat3_mult_vec3_row_dst(float* vec3_dst, const float* vec3_src, const float* mat3_src);
void mat3_mult_vec3_col_dst(float* vec3_dst, const float* mat3_src, const float* vec3_src);
void mat3_transpose(float* mat3_dst);
void mat3_transpose_dst(float* mat3_dst, const float* mat3_src);
void mat3_inverse(float* mat3_dst);
void mat3_inverse_dst(float* mat3_dst, const float* mat3_src);
void mat3_extract_mat4_dst(float* mat3_dst, const float* mat4_src);

void mat4_copy(float* mat4_dst, const float* mat4_src);
void mat4_identity(float* mat4_dst);
void mat4_zero(float* mat4_dst);
void mat4_add_mat4(float* mat4_dst, const float* mat4_src);
void mat4_add_mat4_dst(float* mat4_dst, const float* mat4_srca, const float* mat4_srcb);
void mat4_sub_mat4_lft(float* mat4_dst, const float* mat4_src);
void mat4_sub_mat4_rgt(const float* mat4_src, float* mat4_dst);
void mat4_sub_mat4_dst(float* mat4_dst, const float* mat4_srca, const float* mat4_srcb);
void mat4_mult_scalar(float* mat4_dst, float scalar);
void mat4_mult_scalar_dst(float* mat4_dst, const float* mat4_src, float scalar);
void mat4_mult_mat4_lft(float* mat4_dst, const float* mat4_src);
void mat4_mult_mat4_rgt(const float* mat4_src, float* mat4_dst);
void mat4_mult_mat4_dst(float* mat4_dst, const float* mat4_srca, const float* mat4_srcb);
void mat4_mult_vec4_row(float* vec4_dst, const float* mat4_src);
void mat4_mult_vec4_col(const float* mat4_src, float* vec4_dst);
void mat4_mult_vec4_row_dst(float* vec4_dst, const float* vec4_src, const float* mat4_src);
void mat4_mult_vec4_col_dst(float* vec4_dst, const float* mat4_src, const float* vec4_src);
void mat4_transpose(float* mat4_dst);
void mat4_transpose_dst(float* mat4_dst, const float* mat4_src);
void mat4_inverse(float* mat4_dst);
void mat4_inverse_dst(float* mat4_dst, const float* mat4_src);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // MAT_H221