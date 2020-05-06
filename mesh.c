#include "mesh.h"

#include <stdlib.h>
#include <memory.h>
#include "vec.h"

/*
 * VAO
 *
 * stores format of vertex data
 * stores vertex buffers providing the vertex data array
 *
 * ~stores vertex buffer binding?
 * stores index buffer binding
 */

/*
 * VBO
 *
 * buffer in GPU
 */

void mesh_genCube(Mesh* mesh, AttribLocations* attribLocations)
{
    Vertex vertices[24];
    unsigned int indices[36];
    unsigned int numVertices = 24;
    unsigned int numIndices = 36;
    unsigned int i;
    
    if (mesh)
    {
        /*
         *    4-----7
         * 0--+--3  |
         * |  |  |  |
         * |  5--|--6
         * 1-----2
         */

        /* POSITION */

        // front
        vec3_set((float*)(&vertices[0].position), -1.0f,  1.0f,  1.0f);
        vec3_set((float*)(&vertices[1].position), -1.0f, -1.0f,  1.0f);
        vec3_set((float*)(&vertices[2].position),  1.0f, -1.0f,  1.0f);
        vec3_set((float*)(&vertices[3].position),  1.0f,  1.0f,  1.0f);
        // right
        vec3_set((float*)(&vertices[4].position),  1.0f,  1.0f,  1.0f);
        vec3_set((float*)(&vertices[5].position),  1.0f, -1.0f,  1.0f);
        vec3_set((float*)(&vertices[6].position),  1.0f, -1.0f, -1.0f);
        vec3_set((float*)(&vertices[7].position),  1.0f,  1.0f, -1.0f);
        // back
        vec3_set((float*)(&vertices[8].position),   1.0f,  1.0f, -1.0f);
        vec3_set((float*)(&vertices[9].position),   1.0f, -1.0f, -1.0f);
        vec3_set((float*)(&vertices[10].position), -1.0f, -1.0f, -1.0f);
        vec3_set((float*)(&vertices[11].position), -1.0f,  1.0f, -1.0f);
        // left
        vec3_set((float*)(&vertices[12].position), -1.0f,  1.0f, -1.0f);
        vec3_set((float*)(&vertices[13].position), -1.0f, -1.0f, -1.0f);
        vec3_set((float*)(&vertices[14].position), -1.0f, -1.0f,  1.0f);
        vec3_set((float*)(&vertices[15].position), -1.0f,  1.0f,  1.0f);
        // top
        vec3_set((float*)(&vertices[16].position), -1.0f,  1.0f, -1.0f);
        vec3_set((float*)(&vertices[17].position), -1.0f,  1.0f,  1.0f);
        vec3_set((float*)(&vertices[18].position),  1.0f,  1.0f,  1.0f);
        vec3_set((float*)(&vertices[19].position),  1.0f,  1.0f, -1.0f);
        // back
        vec3_set((float*)(&vertices[20].position), -1.0f, -1.0f,  1.0f);
        vec3_set((float*)(&vertices[21].position), -1.0f, -1.0f, -1.0f);
        vec3_set((float*)(&vertices[22].position),  1.0f, -1.0f, -1.0f);
        vec3_set((float*)(&vertices[23].position),  1.0f, -1.0f,  1.0f);

        /* NORMALS */

        // front
        vec3_set((float*)(&vertices[0].normal),  0.0f,  0.0f,  1.0f);
        vec3_setv((float*)(&vertices[1].normal), (float*)(&vertices[0].normal));
        vec3_setv((float*)(&vertices[2].normal), (float*)(&vertices[0].normal));
        vec3_setv((float*)(&vertices[3].normal), (float*)(&vertices[0].normal));
        // right
        vec3_set((float*)(&vertices[4].normal),  1.0f,  0.0f,  0.0f);
        vec3_setv((float*)(&vertices[5].normal), (float*)(&vertices[4].normal));
        vec3_setv((float*)(&vertices[6].normal), (float*)(&vertices[4].normal));
        vec3_setv((float*)(&vertices[7].normal), (float*)(&vertices[4].normal));
        // back
        vec3_set((float*)(&vertices[8].normal),   0.0f,  0.0f, -1.0f);
        vec3_setv((float*)(&vertices[9].normal),  (float*)(&vertices[8].normal));
        vec3_setv((float*)(&vertices[10].normal), (float*)(&vertices[8].normal));
        vec3_setv((float*)(&vertices[11].normal), (float*)(&vertices[8].normal));
        // left
        vec3_set((float*)(&vertices[12].normal), -1.0f,  0.0f,  0.0f);
        vec3_setv((float*)(&vertices[13].normal), (float*)(&vertices[12].normal));
        vec3_setv((float*)(&vertices[14].normal), (float*)(&vertices[12].normal));
        vec3_setv((float*)(&vertices[15].normal), (float*)(&vertices[12].normal));
        // top
        vec3_set((float*)(&vertices[16].normal),  0.0f,  1.0f,  0.0f);
        vec3_setv((float*)(&vertices[17].normal), (float*)(&vertices[16].normal));
        vec3_setv((float*)(&vertices[18].normal), (float*)(&vertices[16].normal));
        vec3_setv((float*)(&vertices[19].normal), (float*)(&vertices[16].normal));
        // bottom
        vec3_set((float*)(&vertices[20].normal),  0.0f, -1.0f,  0.0f);
        vec3_setv((float*)(&vertices[21].normal), (float*)(&vertices[20].normal));
        vec3_setv((float*)(&vertices[22].normal), (float*)(&vertices[20].normal));
        vec3_setv((float*)(&vertices[23].normal), (float*)(&vertices[20].normal));

        /* TANGENT */

        // front
        vec3_set((float*)(&vertices[0].tangent),  1.0f,  0.0f,  0.0f);
        vec3_setv((float*)(&vertices[1].tangent), (float*)(&vertices[0].tangent));
        vec3_setv((float*)(&vertices[2].tangent), (float*)(&vertices[0].tangent));
        vec3_setv((float*)(&vertices[3].tangent), (float*)(&vertices[0].tangent));
        // right
        vec3_set((float*)(&vertices[4].tangent),  0.0f,  0.0f, -1.0f);
        vec3_setv((float*)(&vertices[5].tangent), (float*)(&vertices[4].tangent));
        vec3_setv((float*)(&vertices[6].tangent), (float*)(&vertices[4].tangent));
        vec3_setv((float*)(&vertices[7].tangent), (float*)(&vertices[4].tangent));
        // back
        vec3_set((float*)(&vertices[8].tangent),  -1.0f,  0.0f,  0.0f);
        vec3_setv((float*)(&vertices[9].tangent),  (float*)(&vertices[8].tangent));
        vec3_setv((float*)(&vertices[10].tangent), (float*)(&vertices[8].tangent));
        vec3_setv((float*)(&vertices[11].tangent), (float*)(&vertices[8].tangent));
        // left
        vec3_set((float*)(&vertices[12].tangent),  0.0f,  0.0f,  1.0f);
        vec3_setv((float*)(&vertices[13].tangent), (float*)(&vertices[12].tangent));
        vec3_setv((float*)(&vertices[14].tangent), (float*)(&vertices[12].tangent));
        vec3_setv((float*)(&vertices[15].tangent), (float*)(&vertices[12].tangent));
        // top
        vec3_set((float*)(&vertices[16].tangent),  1.0f,  0.0f,  0.0f);
        vec3_setv((float*)(&vertices[17].tangent), (float*)(&vertices[16].tangent));
        vec3_setv((float*)(&vertices[18].tangent), (float*)(&vertices[16].tangent));
        vec3_setv((float*)(&vertices[19].tangent), (float*)(&vertices[16].tangent));
        // bottom
        vec3_set((float*)(&vertices[20].tangent),  1.0f,  0.0f,  0.0f);
        vec3_setv((float*)(&vertices[21].tangent), (float*)(&vertices[20].tangent));
        vec3_setv((float*)(&vertices[22].tangent), (float*)(&vertices[20].tangent));
        vec3_setv((float*)(&vertices[23].tangent), (float*)(&vertices[20].tangent));

        /* TEXCOORD */

        for (i = 0; i < numVertices; i += 4)
        {
            vec2_set((float*)(&vertices[i + 0].texCoord),  0.0f,  1.0f);
            vec2_set((float*)(&vertices[i + 1].texCoord),  0.0f,  0.0f);
            vec2_set((float*)(&vertices[i + 2].texCoord),  1.0f,  0.0f);
            vec2_set((float*)(&vertices[i + 3].texCoord),  1.0f,  1.0f);
        }

        /* INDICES */

        // front
        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 2;
        indices[3] = 2;
        indices[4] = 3;
        indices[5] = 0;
        // right
        indices[6] = 4;
        indices[7] = 5;
        indices[8] = 6;
        indices[9] = 6;
        indices[10] = 7;
        indices[11] = 4;
        // back
        indices[12] = 8;
        indices[13] = 9;
        indices[14] = 10;
        indices[15] = 10;
        indices[16] = 11;
        indices[17] = 8;
        // left
        indices[18] = 12;
        indices[19] = 13;
        indices[20] = 14;
        indices[21] = 14;
        indices[22] = 15;
        indices[23] = 12;
        // top
        indices[24] = 16;
        indices[25] = 17;
        indices[26] = 18;
        indices[27] = 18;
        indices[28] = 19;
        indices[29] = 16;
        // bottom
        indices[30] = 20;
        indices[31] = 21;
        indices[32] = 22;
        indices[33] = 22;
        indices[34] = 23;
        indices[35] = 20;

        mesh_init(mesh, attribLocations, numVertices, numIndices, vertices, indices);
    }
}

void mesh_genPlane(Mesh* mesh, AttribLocations* attribLocations, float nx, float ny, float nz)
{
    float normal[3];
    float tangent[3];
    float binormal[3];
    float z[3];
    float tmp[3];
    Vertex vertices[4];
    unsigned int indices[6];

    if (mesh)
    {
        vec3_set(normal, nx, ny, nz);
        vec3_set(z, 0.0f, 0.0f, 1.0f);

        vec3_cross_dst(tangent, normal, z);
        vec3_normalize(tangent);
        vec3_cross_dst(binormal, tangent, normal);

        /*
         * 0-----3
         * |     |
         * |     |
         * 1-----2
         */

        /*
         * -tangent + binormal
         * -tangent - binormal
         *  tangent - binormal
         *  tangent + binormal
         */

        vec3_zero(tmp);
        vec3_subv(tmp, tangent);
        vec3_addv(tmp, binormal);
        vec3_setv((float*)(&vertices[0].position), tmp);
        vec3_zero(tmp);
        vec3_subv(tmp, tangent);
        vec3_subv(tmp, binormal);
        vec3_setv((float*)(&vertices[1].position), tmp);
        vec3_zero(tmp);
        vec3_addv(tmp, tangent);
        vec3_subv(tmp, binormal);
        vec3_setv((float*)(&vertices[1].position), tmp);
        vec3_zero(tmp);
        vec3_addv(tmp, tangent);
        vec3_addv(tmp, binormal);
        vec3_setv((float*)(&vertices[1].position), tmp);

        vec3_setv((float*)(&vertices[0].normal), normal);
        vec3_setv((float*)(&vertices[1].normal), normal);
        vec3_setv((float*)(&vertices[2].normal), normal);
        vec3_setv((float*)(&vertices[3].normal), normal);

        vec3_setv((float*)(&vertices[0].tangent), tangent);
        vec3_setv((float*)(&vertices[1].tangent), tangent);
        vec3_setv((float*)(&vertices[2].tangent), tangent);
        vec3_setv((float*)(&vertices[3].tangent), tangent);

        vec2_set((float*)(&vertices[0].texCoord), 0.0f, 1.0f);
        vec2_set((float*)(&vertices[1].texCoord), 0.0f, 0.0f);
        vec2_set((float*)(&vertices[2].texCoord), 1.0f, 0.0f);
        vec2_set((float*)(&vertices[3].texCoord), 1.0f, 1.0f);

        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 2;
        indices[3] = 2;
        indices[4] = 3;
        indices[5] = 0;

        mesh_init(mesh, attribLocations,
                  sizeof(vertices) / sizeof(Vertex),
                  sizeof(indices) / sizeof(unsigned int),
                  vertices, indices);
    }
}

void mesh_genSphere(Mesh* mesh, AttribLocations* attribLocations, unsigned int slices, unsigned int stacks)
{

}

void mesh_init(Mesh* mesh, AttribLocations* attribLocations, unsigned int numVertices, unsigned int numIndices, Vertex* vertexBuffer, unsigned int* indexBuffer)
{
    if (mesh && numVertices && numIndices && vertexBuffer && indexBuffer && attribLocations)
    {
        // init to safe state
        mesh->vao = 0;
        mesh->vbo = 0;
        mesh->ibo = 0;
        mesh->numVertices = 0;
        mesh->numIndices = 0;
        mesh->vertexBuffer = NULL;
        mesh->indexBuffer = NULL;
        
        // alloc buffers
        mesh->vertexBuffer = (Vertex*)malloc(numVertices * sizeof(Vertex));
        mesh->indexBuffer = (unsigned int*)malloc(numIndices * sizeof(unsigned int));

        if (mesh->vertexBuffer && mesh->indexBuffer)
        {
            // copy info to Mesh struct
            mesh->numVertices = numVertices;
            mesh->numIndices = numIndices;
            memcpy(mesh->vertexBuffer, vertexBuffer, numVertices * sizeof(Vertex));
            memcpy(mesh->indexBuffer, indexBuffer, numIndices * sizeof(unsigned int));
        
            // generate new vao
            glGenVertexArrays(1, &mesh->vao);
            // make current
            glBindVertexArray(mesh->vao);
            // enable vao access to vertex attributes
            // part of vao state
            glEnableVertexAttribArray(attribLocations->position);
            glEnableVertexAttribArray(attribLocations->normal);
            glEnableVertexAttribArray(attribLocations->tangent);
            glEnableVertexAttribArray(attribLocations->texCoord);
            // generate new vbo
            glGenBuffers(1, &mesh->vbo);
            // generate new ibo
            glGenBuffers(1, &mesh->ibo);
            // make current (writes vbo index to global var GL_ARRAY_BUFFER)
            // GL_ARRAY_BUFFER NOT part of vao state!
            glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
            // fill w/ data
            glBufferData(GL_ARRAY_BUFFER, mesh->numVertices * sizeof(Vertex), mesh->vertexBuffer, GL_STATIC_DRAW);
            // make current (writes ibo index to global var GL_ELEMENT_ARRAY_BUFFER)
            // GL_ELEMENT_ARRAY_BUFFER NOT part of vao state?
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
            // fill w/ data
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->numIndices * sizeof(unsigned int), mesh->indexBuffer, GL_STATIC_DRAW);
            // format vertex attribute data
            // attribute index x gets data from buffer currently bound to GL_ARRAY_BUFFER
            // (and will continue to do so even after a different one is bound to GL_ARRAY_BUFFER)?
            // (reads global variable GL_ARRAY_BUFFER (has value of currently bound vbo index)
            // and stores it in the vao)
            glVertexAttribPointer(attribLocations->position, sizeof(Point) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
            glVertexAttribPointer(attribLocations->normal, sizeof(Normal) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Point)));
            glVertexAttribPointer(attribLocations->tangent, sizeof(Tangent) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Point) + sizeof(Normal)));
            glVertexAttribPointer(attribLocations->texCoord, sizeof(TexCoord) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Point) + sizeof(Normal) + sizeof(Tangent)));
        }
    }
}

void mesh_destroy(Mesh* mesh)
{
    if (mesh)
    {
        if (mesh->vertexBuffer)
        {
            free(mesh->vertexBuffer);
        }

        if (mesh->indexBuffer)
        {
            free(mesh->indexBuffer);
        }

        glDeleteBuffers(1, &mesh->ibo);
        glDeleteBuffers(1, &mesh->vbo);
        glDeleteVertexArrays(1, &mesh->vao);
    }
}

void mesh_draw(const Mesh* mesh)
{
    if (mesh)
    {
        glBindVertexArray(mesh->vao);
        glDrawElements(GL_TRIANGLES, mesh->numIndices, GL_UNSIGNED_INT, NULL);
    }
}

//

#include "vector.h"
/*
static struct Vector vector;

int mesh_load(const char *fileName, Mesh *mesh)
{
    int ret = 0;
    
    // check for null-pointers
    if (fileName && object)
    {
        FILE *file;
        OPT_MeshFileInfo meshFileInfo;
        
        file = fopen(fileName, "rb");
        
        // check if file opened properly
        if (file == 0)
        {
            fread(&meshFileInfo, sizeof(OPT_MeshFileInfo), 1, file);
            
            // check if file too small
            if (feof(file) == 0)
            {
                // check file signature
                if (meshFileInfo.fileID == 0x4853454D); // "MESH"
                {
                    // vertexBuffer
                    if ((mesh->vertexBuffer = malloc(meshFileInfo.vertexBufferSize)) != NULL)
                    {
                        #define USE_VECTOR
                        #ifdef USE_VECTOR
                        struct Mesh *mesh = malloc(sizeof(*mesh));
                        #endif
                        
                        fseek(file, (long)meshFileInfo.vertexBufferOff, SEEK_SET);
                        fread(mesh->vertexBuffer, meshFileInfo.vertexBufferSize, 1, file);
                        mesh->numVertices = meshFileInfo.vertexBufferSize;
                        
                        // indexBuffer
                        if ((mesh->indexBuffer = malloc(indexBufferSize)) != NULL)
                        {
                            fseek(file, (long)meshFileInfo.indexBufferOff, SEEK_SET);
                            fread(mesh->indexBuffer, meshFileInfo.indexBufferSize, 1, file);
                            mesh->numIndices = meshFileInfo.indexBufferSize;
                            
                            mesh_register(mesh);
                            
                            #ifdef USE_VECTOR
                            vector_push(&vector, &mesh, sizeof(mesh));
                            #endif
                            
                            // all went well
                            ret = 1;
                        }
                        else
                        {
                            free(mesh->vertexBuffer);
                            fprintf(stderr, "Out of memory.\n");
                        }
                        
                        #ifdef USE_VECTOR
                        free(mesh);
                        #endif
                    }
                    else
                    {
                        fprintf(stderr, "Out of memory.\n");
                    }
                }
                else
                {
                    fprintf(stderr, "Invalid file format.\n");
                }
            }
            else
            }
                fprintf(stderr, "Invalid file format.\n");
            }
            
            fclose(file);
        }
        else
        {
            fprintf(stderr, "Failed to open file %s.\n", fileName);
        }
    }
    
    return ret;
}*/