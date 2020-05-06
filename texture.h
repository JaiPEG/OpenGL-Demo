#ifndef TEXTURE_H221
#define TEXTURE_H221

#include <Windows.h>
#include "glew.h"

GLuint DEFAULT_AMBIENT_TEXTURE;
GLuint DEFAULT_DIFFUSE_TEXTURE;
GLuint DEFAULT_SPECULAR_TEXTURE;
GLuint DEFAULT_SHININESS_TEXTURE;
GLuint DEFAULT_EMISSION_TEXTURE;
GLuint DEFAULT_NORMAL_TEXTURE;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void genDefaultTextures();
BOOL texture_create(const char* fileName, GLuint* id);
void texture_destroy(GLuint id);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // TEXTURE_H221