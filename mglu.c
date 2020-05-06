#include "mglu.h"
#include "mat.h"

void mgluUpdateMatrices(const float* modelMatrix, const float* viewMatrix, const float* projectionMatrix)
{
    float modelViewMatrix[16];
    float modelViewProjectionMatrix[16];
    float normalMatrix[9];
    
    if (modelMatrix, viewMatrix, projectionMatrix)
    {
        mat4_mult_mat4_dst(modelViewMatrix, viewMatrix, modelMatrix);
        mat4_mult_mat4_dst(modelViewProjectionMatrix, projectionMatrix, modelViewMatrix);
        mat3_extract_mat4_dst(normalMatrix, modelViewMatrix);
        // TODO
        // mat3_transpose(normalMatrix);
        // mat3_inverse(normalMatrix);

        glUniformMatrix4fv(LOCATION_UNIFORM_MATRIX_MODEL, 1, GL_FALSE, modelMatrix);
        glUniformMatrix4fv(LOCATION_UNIFORM_MATRIX_VIEW, 1, GL_FALSE, viewMatrix);
        glUniformMatrix4fv(LOCATION_UNIFORM_MATRIX_PROJECTION, 1, GL_FALSE, projectionMatrix);
        glUniformMatrix4fv(LOCATION_UNIFORM_MATRIX_MODELVIEW, 1, GL_FALSE, modelViewMatrix);
        glUniformMatrix4fv(LOCATION_UNIFORM_MATRIX_MODELVIEWPROJECTION, 1, GL_FALSE, modelViewProjectionMatrix);
        glUniformMatrix3fv(LOCATION_UNIFORM_MATRIX_NORMAL, 1, GL_FALSE, normalMatrix);
    }
}