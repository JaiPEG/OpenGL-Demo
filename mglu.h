#ifndef MGLU_H221
#define MGLU_H221

#include "glew.h"

#define LOCATION_UNIFORM_MATRIX_MODEL               0
#define LOCATION_UNIFORM_MATRIX_VIEW                4
#define LOCATION_UNIFORM_MATRIX_PROJECTION          8
#define LOCATION_UNIFORM_MATRIX_MODELVIEW           12
#define LOCATION_UNIFORM_MATRIX_MODELVIEWPROJECTION 16
#define LOCATION_UNIFORM_MATRIX_NORMAL              20
#define LOCATION_UNIFORM_LIGHT_POSITION             24
#define LOCATION_UNIFORM_LIGHT_AMBIENT              25
#define LOCATION_UNIFORM_LIGHT_DIFFUSE              26
#define LOCATION_UNIFORM_LIGHT_SPECULAR             27
#define LOCATION_UNIFORM_LIGHT_CATTENUATION         28
#define LOCATION_UNIFORM_LIGHT_QATTENUATION         29
#define LOCATION_UNIFORM_LIGHT_RADIUS               30
#define LOCATION_UNIFORM_MATERIAL_AMBIENT           31
#define LOCATION_UNIFORM_MATERIAL_DIFFUSE           32
#define LOCATION_UNIFORM_MATERIAL_SPECULAR          33
#define LOCATION_UNIFORM_MATERIAL_SHININESS         34
#define LOCATION_UNIFORM_MATERIAL_EMISSION          35
#define LOCATION_UNIFORM_TEXTURE_AMBIENT            36
#define LOCATION_UNIFORM_TEXTURE_DIFFUSE            37
#define LOCATION_UNIFORM_TEXTURE_SPECULAR           38
#define LOCATION_UNIFORM_TEXTURE_SHININESS          39
#define LOCATION_UNIFORM_TEXTURE_NORMAL             40
#define LOCATION_ATTRIB_POSITION                    0
#define LOCATION_ATTRIB_NORMAL                      1
#define LOCATION_ATTRIB_TANGENT                     2
#define LOCATION_ATTRIB_TEXCOORD                    3

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void mgluUpdateMatrices(const float* modelMatrix, const float* viewMatrix, const float* projectionMatrix);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // MGLU_H221