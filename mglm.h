#ifndef MGLM_H221
#define MGLM_H221

// My OpenGL Math Library.

#ifndef COLUMN_MAJOR
#define COLUMN_MAJOR
#endif // COLUMN_MAJOR

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void mglmLoadIdentity(float* mat4);
void mglmLoadFrustum(float* mat4, float left, float right, float bottom, float top, float zNear, float zFar);
void mglmLoadOrtho(float* mat4, float left, float right, float bottom, float top, float zNear, float zFar);
void mglmLoadPerspective(float* mat4, float fov, float aspect, float near, float zFar);
void mglmFrustum(float* mat4, float left, float right, float bottom, float top, float zNear, float zFar);
void mglmOrtho(float* mat4, float left, float right, float bottom, float top, float zNear, float zFar);
void mglmPerspective(float* mat4, float fov, float aspect, float near, float zFar);
void mglmRotate(float* mat4, float angle, float x, float y, float z);
void mglmRotateX(float* mat4, float angle);
void mglmRotateY(float* mat4, float angle);
void mglmRotateZ(float* mat4, float angle);
void mglmScale(float* mat4, float x, float y, float z);
void mglmTranslate(float* mat4, float x, float y, float z);
void mglmZero(float* mat4);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // MGLM_H221