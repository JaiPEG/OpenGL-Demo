#include "obj.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

typedef int BOOL;

#ifndef TRUE
#define TRUE 1
#endif // TRUE

#ifndef FALSE
#define FALSE 0
#endif // FALSE

typedef struct
{
    float x;
    float y;
    float z;
} OBJVertex;

typedef struct
{
    float x;
    float y;
    float z;
} OBJNormal;

typedef struct
{
    int index;
    int vertices[3];
} OBJFace;

typedef struct
{
    const char* name;
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float emission[4];
    float alpha;
    float ni;
    float ns;
    int illum;
    int texture;
} OBJMaterial;

typedef struct
{
    float u;
    float v;
} OBJTexCoord;

void obj_load(const char* fileName, Mesh* mesh_ret)
{
    FILE* file;

    char line[256];
    char objectName[32];

    Vector vertices;    // OBJVertex*
    Vector normals;     // OBJNormal*
    Vector faces;       // OBJFace*
    Vector materials;   // OBJMaterial*

    BOOL vertexNormals = FALSE;
    OBJVertex tmpVertex;
    OBJNormal tmpNormal;
    OBJFace tmpFace;
    OBJMaterial tmpMaterial;

    mesh_ret = NULL;

    if (fopen_s(&file, fileName, "r"))
    {
        vector_init(&vertices, sizeof(OBJVertex*));
        vector_init(&normals, sizeof(OBJNormal*));
        vector_init(&faces, sizeof(OBJFace*));
        vector_init(&materials, sizeof(OBJMaterial*));
        
        while (fgets(line, sizeof(line), file))
        {
            // comment, newline
            if (*line == '#' ||
                *line == '\n')
            {
                continue;
            }

            // object
            if (*line == 'o')
            {
                strcpy_s(objectName, sizeof(objectName), line + 2);
            }

            // vertex
            if (line[0] == 'v' &&
                line[1] == ' ')
            {
                sscanf_s(line, "v %f %f %f", &tmpVertex.x, &tmpVertex.y, &tmpVertex.z);

                vector_push(&vertices, &tmpVertex, sizeof(OBJVertex));
            }

            // normal
            if (line[0] == 'v' &&
                line[1] == 'n' &&
                line[2] == ' ')
            {
                sscanf_s(line, "vn %f %f %f", &tmpNormal.x, &tmpNormal.y, &tmpNormal.z);

                vector_push(&normals, &tmpNormal, sizeof(OBJNormal));
            }

            // face
            if (*line == 'f')
            {
                sscanf_s(line, "f %d//%d %d//%d %d//%d", &tmpFace.vertices[0], &tmpFace.index,
                                                         &tmpFace.vertices[1], &tmpFace.index,
                                                         &tmpFace.vertices[2], &tmpFace.index);

                vector_push(&faces, &tmpFace, sizeof(OBJFace));
            }

            // vertex normals
            if (*line == 's')
            {
                // maybe other cases too?
                if (line[2] == '1')
                {
                    vertexNormals = TRUE;
                }
                else if (strcmp(line + 2, "off") == 0)
                {
                    vertexNormals = FALSE;
                }
                else
                {
                    vertexNormals = FALSE;
                }
            }
        }

        // exited b/c of error or EOF, determine
        if (feof(file))
        {
            Vertex* vertexBuffer = NULL;
            unsigned int* indexBuffer = NULL;
            unsigned int v, f;
            unsigned int numVertices = vertices.size / sizeof(Vertex);
            unsigned int numIndices;
            
            if (vertexNormals)
            {
                vertexBuffer = (Vertex*)malloc(vertices.size + normals.size + normals.size /* + texCoords.size*/);
            }
            else
            {
                vertexBuffer = (Vertex*)malloc(vertices.size + vertices.size + vertices.size /* + texCoords.size*/);
            }

            // TODO
            // indexBuffer = malloc();

            for (v = 0, f = 0; f < vertices.size / sizeof(float); ++v, f += 3)
            {
                // copy position data to vertexBuffer
                vertexBuffer[v].position.x = ((float*)vertices.base)[f + 0];
                vertexBuffer[v].position.y = ((float*)vertices.base)[f + 1];
                vertexBuffer[v].position.z = ((float*)vertices.base)[f + 2];

                // TODO
                // copy texCoord data to vertexBuffer
                vertexBuffer[v].texCoord.x = 0.0f;
                vertexBuffer[v].texCoord.y = 0.0f;
            }

            if (vertexNormals)
            {
                for (v = 0, f = 0; f < normals.size / sizeof(float); ++v, f += 3)
                {
                    // copy normal data to vertexBuffer
                    vertexBuffer[v].normal.x = ((float*)normals.base)[f + 0];
                    vertexBuffer[v].normal.y = ((float*)normals.base)[f + 1];
                    vertexBuffer[v].normal.z = ((float*)normals.base)[f + 2];

                    // TODO
                    // copy tangent data to vertexBuffer
                    vertexBuffer[v].tangent.x = 1.0f;
                    vertexBuffer[v].tangent.y = 0.0f;
                    vertexBuffer[v].tangent.z = 0.0f;
                }
            }
            else
            {
                // TODO
                for (v = 0, f = 0; f < normals.size / sizeof(float); ++v, f += 3)
                {
                    // TODO
                    // copy normal data to vertexBuffer
                    vertexBuffer[v].normal.x = 0.0f;
                    vertexBuffer[v].normal.y = 0.0f;
                    vertexBuffer[v].normal.z = 1.0f;

                    // TODO
                    // copy tangent data to vertexBuffer
                    vertexBuffer[v].tangent.x = 1.0f;
                    vertexBuffer[v].tangent.y = 0.0f;
                    vertexBuffer[v].tangent.z = 0.0f;
                }
            }

            /* work in progress */
            /* mesh_init(mesh_ret, NULL, numVertices, numIndices, vertexBuffer, indexBuffer); */

            if (vertexBuffer)
            {
                free(vertexBuffer);
            }

            if (indexBuffer)
            {
                free(indexBuffer);
            }
        }

        // exited b/c of error or EOF, determine
        if (ferror(file))
        {
            printf("Error reading file.");
        }

        fclose(file);

        vector_destroy(&vertices, FALSE);
        vector_destroy(&normals, FALSE);
        vector_destroy(&faces, FALSE);
        vector_destroy(&materials, FALSE);
    }
}