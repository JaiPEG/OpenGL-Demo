#ifndef SHADER_H221
#define SHADER_H221

#include "glew.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

GLuint createShader(const char* fileName, const GLenum type);
GLuint createProgram(const GLuint vert, const GLuint frag);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SHADER_H221