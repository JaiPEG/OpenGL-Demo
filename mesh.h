#ifndef VERTEXBUFFER_H22
#define VERTEXBUFFER_H22

#include "glew.h"

#include <stdint.h>

typedef struct
{
    float x;
    float y;
    float z;
} Point;

typedef struct
{
    float x;
    float y;
    float z;
} Normal;

typedef struct
{
    float x;
    float y;
    float z;
} Tangent;

typedef struct
{
    float x;
    float y;
} TexCoord;

typedef struct
{
    Point position;
    Normal normal;
    Tangent tangent;
    TexCoord texCoord;
} Vertex;

typedef struct
{
    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    GLuint PAD;
    unsigned int numVertices;
    unsigned int numIndices;
    Vertex* vertexBuffer;
    unsigned int* indexBuffer;
} Mesh;

typedef struct
{
    GLuint position;
    GLuint normal;
    GLuint tangent;
    GLuint texCoord;
} AttribLocations;

//

#pragma pack(push, 1)

struct OPT_MeshFileInfo
{
    uint32_t fileID;
    uint32_t fileSize;
    uint32_t vertexComponents;
    uint32_t normalComponents;
    uint32_t tangentComponents;
    uint32_t texCoordComponents;
    uint32_t vertexBufferOff;
    uint32_t vertexBufferSize;
    uint32_t indexBufferOff;
    uint32_t indexBufferSize;
};

#pragma pack(pop)

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void mesh_genCube(Mesh* mesh, AttribLocations* attribLocations);
void mesh_genPlane(Mesh* mesh, AttribLocations* attribLocations, float nx, float ny, float nz);
void mesh_genSphere(Mesh* mesh, AttribLocations* attribLocations, unsigned int slices, unsigned int stacks);
void mesh_init(Mesh* mesh, AttribLocations* attribLocations, unsigned int numVertices, unsigned int numIndices, Vertex* vertices, unsigned int* indices);
void mesh_destroy(Mesh* mesh);
void mesh_draw(const Mesh* mesh);

//
int mesh_load(const char* fileName);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // VERTEXBUFFER_H22