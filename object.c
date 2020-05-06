#include "object.h"
#include "texture.h"

void object_draw(const Object* object)
{
    if (object)
    {
        material_use(object->material);
        mesh_draw(object->mesh);
    }
}

void object_destroy(Object* object)
{
    if (object)
    {
        texture_destroy(object->material->texture0);
        texture_destroy(object->material->texture1);
        texture_destroy(object->material->texture2);
        texture_destroy(object->material->texture3);

        // can't destroy material

        mesh_destroy(object->mesh);

        // DEALLOC ???
    }
}

/*

int object_load(const char *fileName, Object *object)
{
    int ret = 0;
    
    if (fileName && object)
    {
        FILE *file;
        OPT_ObjectFileInfo objectFileInfo;
        
        file = fopen(fileName, "rb");
        
        if (file == 0)
        {
            const char *meshFileName;
            
            // read in object file info
            fread(&objectFileInfo, sizeof(OPT_ObjectFile), 1, file);
            
            // get Mesh file name
            fseek(file, (long)objectFileInfo.meshOff, SEEK_SET);
            fread(meshFileName, objectFileInfo.meshSize, 1, file);
            
            // TODO: don't copy to all objects
            // read into object->mesh
            if (mesh_load(meshFileName, &object->mesh))
            {
                // read in Object name
                fseek(file, (long)objectFileInfo.nameOff, SEEK_SET);
                fread(&object->name, objectFileInfo.nameSize, 1, file);
                
                // read in transformations
                fseek(file, (long)objectFileInfo.dataOff, SEEK_SET);
                fread(&object->position, sizeof(float), objectFileInfo.positionComponents, file);
                fread(&object->rotation, sizeof(float), objectFileInfo.rotationComponents, file);
                fread(&object->scale, sizeof(float), objectFileInfo.scaleComponents, file);
                
                ret = 1;
            }
            
            fclose(file);
        }
    }
    
    return ret;
}*/