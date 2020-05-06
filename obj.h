#ifndef OBJ_H221
#define OBJ_H221

#include "mesh.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void obj_load(const char* fileName, Mesh* mesh_ret);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // OBJ_H221