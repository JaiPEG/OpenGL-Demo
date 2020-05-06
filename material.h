#ifndef MATERIAL_H221
#define MATERIAL_H221

#include "glew.h"

typedef struct
{
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float emission[4];
    float shininess;
    float roughness;
    GLuint texture0;
    GLuint texture1;
    GLuint texture2;
    GLuint texture3;
} Material;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void material_use(const Material* material);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // MATERIAL_H221