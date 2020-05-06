#include "light.h"
#include <GL/glew.h>
#include "mglu.h"
#include "mat.h"
#include "vec.h"

void light_loadShadowMatrix(const struct Light* light, float* mat4, const struct Shard* shard)
{
    float planeNormal[4];
    float dot;
    float v0[3];
    float v1[3];

    vec3_subv_dst(v0, shard->p1, shard->p0);
    vec3_subv_dst(v1, shard->p2, shard->p0);

    vec3_cross_dst(planeNormal, v0, v1);
    vec3_normalize(planeNormal);
    // Find the last coefficient by back substitutions
    planeNormal[3] = -vec3_dot(planeNormal, shard->p2);

    dot = vec4_dot(planeNormal, light->position);

    // col0
    mat4[0 + 0 * 4] = dot  - light->position[0] * planeNormal[0];
    mat4[1 + 0 * 4] = 0.0f - light->position[0] * planeNormal[1];
    mat4[2 + 0 * 4] = 0.0f - light->position[0] * planeNormal[2];
    mat4[3 + 0 * 4] = 0.0f - light->position[0] * planeNormal[3];

    // col1
    mat4[0 + 1 * 4] = 0.0f - light->position[1] * planeNormal[0];
    mat4[1 + 1 * 4] = dot  - light->position[1] * planeNormal[1];
    mat4[2 + 1 * 4] = 0.0f - light->position[1] * planeNormal[2];
    mat4[3 + 1 * 4] = 0.0f - light->position[1] * planeNormal[3];

    // col2
    mat4[0 + 2 * 4] = 0.0f - light->position[2] * planeNormal[0];
    mat4[1 + 2 * 4] = 0.0f - light->position[2] * planeNormal[1];
    mat4[2 + 2 * 4] = dot  - light->position[2] * planeNormal[2];
    mat4[3 + 2 * 4] = 0.0f - light->position[2] * planeNormal[3];

    // col3
    mat4[0 + 3 * 4] = 0.0f - light->position[3] * planeNormal[0];
    mat4[1 + 3 * 4] = 0.0f - light->position[3] * planeNormal[1];
    mat4[2 + 3 * 4] = 0.0f - light->position[3] * planeNormal[2];
    mat4[3 + 3 * 4] = dot  - light->position[3] * planeNormal[3];
}

void light_multShadowMatrix(const struct Light* light, float* mat4, const struct Shard* shard)
{
    float tmp[16];

    light_loadShadowMatrix(light, mat4, shard);
    mat4_mult_mat4_rgt(tmp, mat4);
}

void light_use(const struct Light* light, const float* modelViewMatrix)
{
    float position_view[4];
    
    if (light && modelViewMatrix)
    {
        mat4_mult_vec4_col_dst(position_view, modelViewMatrix, light->position);
        glUniform4fv(LOCATION_UNIFORM_LIGHT_POSITION, 1, position_view);
        glUniform4fv(LOCATION_UNIFORM_LIGHT_AMBIENT, 1, light->ambient);
        glUniform4fv(LOCATION_UNIFORM_LIGHT_DIFFUSE, 1, light->diffuse);
        glUniform4fv(LOCATION_UNIFORM_LIGHT_SPECULAR, 1, light->specular);
        glUniform1f(LOCATION_UNIFORM_LIGHT_CATTENUATION, 1.0f / light->intensity);
        glUniform1f(LOCATION_UNIFORM_LIGHT_QATTENUATION, light->attenuation);
        glUniform1f(LOCATION_UNIFORM_LIGHT_RADIUS, light->radius);
    }
}