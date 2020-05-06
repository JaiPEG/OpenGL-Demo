#ifndef OBJECT_H221
#define OBJECT_H221

#include "mesh.h"
#include "material.h"

typedef struct
{
    const char* name;
    Mesh* mesh;
    Material* material;
} Object;

//

struct OPT_ObjectFileInfo
{
    uint32_t fileID;
    uint32_t fileSize;
    uint32_t nameOff;
    uint32_t nameSize;
    uint32_t meshOff;
    uint32_t meshSize;
    uint32_t dataOff;
    uint32_t positionComponents;
    uint32_t rotationComponents;
    uint32_t scaleComponents;
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void object_draw(const Object* object);
void object_destroy(Object* object);

//
int object_load(const char *fileName, Object *object);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // OBJECT_H221