#include "mat.h"

#include <memory.h>

static int i;
static int j;
static int k;

/* MAT2 */

// CTRL+V

void mat2_copy(float* mat2_dst, const float* mat2_src)
{
    for (i = 0; i < 4; ++i)
    {
        mat2_dst[i] = mat2_src[i];
    }
}

float mat2_determinant(const float* mat2_src)
{
    return mat2_src[0] * mat2_src[3] -
           mat2_src[2] * mat2_src[1];
}

void mat2_inverse(float* mat2_dst)
{
    float tmp[4];

    mat2_inverse_dst(tmp, mat2_dst);

    mat2_copy(mat2_dst, tmp);
}

void mat2_inverse_dst(float* mat2_dst, const float* mat2_src)
{
    float determinant = mat2_determinant(mat2_src);

    mat2_dst[0] = mat2_src[3];
    mat2_dst[1] = -mat2_src[1];
    mat2_dst[2] = -mat2_src[2];
    mat2_dst[3] = mat2_src[0];
    
    //mat2_mult_scalar(mat2_dst, 1.0f / determinant);
}

//

void mat2_extract_mat3_dst(float* mat2_dst, const float* mat3_src)
{
    mat2_dst[0] = mat3_src[0];
    mat2_dst[1] = mat3_src[1];

    mat2_dst[2] = mat3_src[3];
    mat2_dst[3] = mat3_src[4];
}

void mat2_extract_mat4_dst(float* mat2_dst, const float* mat4_src)
{
    mat2_dst[0] = mat4_src[0];
    mat2_dst[1] = mat4_src[1];

    mat2_dst[2] = mat4_src[4];
    mat2_dst[3] = mat4_src[5];
}

/* MAT3 */

// TODO:

void mat3_extract_mat4_dst(float* mat3_dst, const float* mat4_src)
{
    mat3_dst[0] = mat4_src[0];
    mat3_dst[1] = mat4_src[1];
    mat3_dst[2] = mat4_src[2];

    mat3_dst[3] = mat4_src[4];
    mat3_dst[4] = mat4_src[5];
    mat3_dst[5] = mat4_src[6];

    mat3_dst[6] = mat4_src[8];
    mat3_dst[7] = mat4_src[9];
    mat3_dst[8] = mat4_src[10];
}

/* MAT4 */

void mat4_copy(float* mat4_dst, const float* mat4_src)
{
    for (i = 0; i < 16; ++i)
    {
        mat4_dst[i] = mat4_src[i];
    }
}

void mat4_identity(float* mat4_dst)
{
    for (i = 0; i < 16; ++i)
    {
        mat4_dst[i] = 0.0f;
    }

    for (i = 0; i < 4; ++i)
    {
        mat4_dst[(i << 2) + i] = 1.0f;
    }
}

void mat4_zero(float* mat4_dst)
{
    for (i = 0; i < 16; ++i)
    {
        mat4_dst[i] = 0.0f;
    }
}

void mat4_add_mat4(float* mat4_dst, const float* mat4_src)
{
    for (i = 0; i < 16; ++i)
    {
        mat4_dst[i] = mat4_dst[i] + mat4_src[i];
    }
}

void mat4_add_mat4_dst(float* mat4_dst, const float* mat4_srca, const float* mat4_srcb)
{
    for (i = 0; i < 16; ++i)
    {
        mat4_dst[i] = mat4_srca[i] + mat4_srcb[i];
    }
}

void mat4_sub_mat4_lft(float* mat4_dst, const float* mat4_src)
{
    for (i = 0; i < 16; ++i)
    {
        mat4_dst[i] = mat4_dst[i] - mat4_src[i];
    }
}

void mat4_sub_mat4_rgt(const float* mat4_src, float* mat4_dst)
{
    for (i = 0; i < 16; ++i)
    {
        mat4_dst[i] = mat4_src[i] - mat4_dst[i];
    }
}

void mat4_sub_mat4_dst(float* mat4_dst, const float* mat4_srca, const float* mat4_srcb)
{
    for (i = 0; i < 16; ++i)
    {
        mat4_dst[i] = mat4_srca[i] - mat4_srcb[i];
    }
}

void mat4_mult_scalar(float* mat4_dst, float scalar)
{
    for (i = 0; i < 16; ++i)
    {
        mat4_dst[i] = mat4_dst[i] * scalar;
    }
}

void mat4_mult_scalar_dst(float* mat4_dst, const float* mat4_src, float scalar)
{
    for (i = 0; i < 16; ++i)
    {
        mat4_dst[i] = mat4_src[i] * scalar;
    }
}

void mat4_mult_mat4_lft(float* mat4_dst, const float* mat4_src)
{
    float tmp[16];
    
    // init
    for (i = 0; i < 16; ++i)
    {
        tmp[i] = 0.0f;
    }

    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j)
        {
            for (k = 0; k < 4; ++k)
            {
                tmp[(i << 2) + j] += mat4_dst[(k << 2) + j] * mat4_src[(i << 2) + k];
            }
        }
    }

    // copy
    for (i = 0; i < 16; ++i)
    {
        mat4_dst[i] = tmp[i];
    }
}

void mat4_mult_mat4_rgt(const float* mat4_src, float* mat4_dst)
{
    float tmp[16];
    
    // init
    for (i = 0; i < 16; ++i)
    {
        tmp[i] = 0.0f;
    }

    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j)
        {
            for (k = 0; k < 4; ++k)
            {
                tmp[(i << 2) + j] += mat4_src[(k << 2) + j] * mat4_dst[(i << 2) + k];
            }
        }
    }

    // copy
    for (i = 0; i < 16; ++i)
    {
        mat4_dst[i] = tmp[i];
    }
}

void mat4_mult_mat4_dst(float* mat4_dst, const float* mat4_srca, const float* mat4_srcb)
{
    // init
    for (i = 0; i < 16; ++i)
    {
        mat4_dst[i] = 0.0f;
    }

    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j)
        {
            for (k = 0; k < 4; ++k)
            {
                mat4_dst[(i << 2) + j] += mat4_srca[(k << 2) + j] * mat4_srcb[(i << 2) + k];
            }
        }
    }
}

void mat4_mult_vec4_row(float* vec4_dst, const float* mat4_src)
{
    float tmp[4];

    // init
    for (i = 0; i < 4; ++i)
    {
        tmp[i] = 0.0f;
    }

    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j)
        {
            tmp[i] += vec4_dst[j] * mat4_src[(i << 2) + j];
        }
    }

    // copy
    for (i = 0; i < 4; ++i)
    {
        vec4_dst[i] = tmp[i];
    }
}

void mat4_mult_vec4_col(const float* mat4_src, float* vec4_dst)
{
    float tmp[4];

    // init
    for (i = 0; i < 4; ++i)
    {
        tmp[i] = 0.0f;
    }

    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j)
        {
            tmp[i] += mat4_src[(j << 2) + i] * vec4_dst[j];
        }
    }

    // copy
    for (i = 0; i < 4; ++i)
    {
        vec4_dst[i] = tmp[i];
    }
}

void mat4_mult_vec4_row_dst(float* vec4_dst, const float* vec4_src, const float* mat4_src)
{
    // init
    for (i = 0; i < 4; ++i)
    {
        vec4_dst[i] = 0.0f;
    }

    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j)
        {
            vec4_dst[i] += vec4_dst[j] * mat4_src[(i << 2) + j];
        }
    }
}

void mat4_mult_vec4_col_dst(float* vec4_dst, const float* mat4_src, const float* vec4_src)
{
    // init
    for (i = 0; i < 4; ++i)
    {
        vec4_dst[i] = 0.0f;
    }

    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j)
        {
            vec4_dst[i] += mat4_src[(j << 2) + i] * vec4_src[j];
        }
    }
}

void mat4_transpose(float* mat4_dst)
{
    float tmp[16];
    
    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j)
        {
            tmp[(j << 2) + i] = mat4_dst[(i << 2) + j];
        }
    }

    // copy
    for (i = 0; i < 16; ++i)
    {
        mat4_dst[i] = tmp[i];
    }
}

void mat4_transpose_dst(float* mat4_dst, const float* mat4_src)
{
    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j)
        {
            mat4_dst[(j << 2) + i] = mat4_src[(i << 2) + j];
        }
    }
}

void mat4_inverse(float* mat4_dst)
{
    // TODO:
}

void mat4_inverse_dst(float* mat4_dst, const float* mat4_src)
{
    // TODO:
}