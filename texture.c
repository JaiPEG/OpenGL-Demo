#include "texture.h"

#include "bmp.h"

float defaultAmbientTexture[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float defaultDiffuseTexture[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float defaultSpecularTexture[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float defaultShininessTexture[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float defaultEmissionTexture[4] = {0.0f, 0.0f, 0.0f, 1.0f};
float defaultNormalTexture[4] = {0.0f, 0.0f, 1.0f, 1.0f};

void genDefaultTextures()
{
    glGenTextures(1, &DEFAULT_AMBIENT_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, DEFAULT_AMBIENT_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_FLOAT, defaultAmbientTexture);

    glGenTextures(1, &DEFAULT_DIFFUSE_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, DEFAULT_DIFFUSE_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_FLOAT, defaultDiffuseTexture);

    glGenTextures(1, &DEFAULT_SPECULAR_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, DEFAULT_SPECULAR_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_FLOAT, defaultSpecularTexture);

    glGenTextures(1, &DEFAULT_SHININESS_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, DEFAULT_SHININESS_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_FLOAT, defaultShininessTexture);

    glGenTextures(1, &DEFAULT_EMISSION_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, DEFAULT_EMISSION_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_FLOAT, defaultEmissionTexture);

    glGenTextures(1, &DEFAULT_NORMAL_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, DEFAULT_NORMAL_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_FLOAT, defaultNormalTexture);
}

BOOL texture_create(const char* fileName, GLuint* id)
{
    BOOL ret = FALSE;

    Image image;
    
    if (fileName && id)
    {
        // (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
        // GetObject(bitmap, sizeof(BITMAP), &bitmapStruct);
        // DeleteObject(bitmap);

        if (loadBmp(fileName, &image))
        {
            glGenTextures(1, id);
            glBindTexture(GL_TEXTURE_2D, *id);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

            if (image.redBits == 8 &&
                image.redBits == 8 &&
                image.redBits == 8)
            {
                if (image.alphaBits == 0)
                {
                    glTexImage2D(GL_TEXTURE_2D, 0, image.pixelBytes, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data);
                }
                else if (image.alphaBits == 8)
                {
                    glTexImage2D(GL_TEXTURE_2D, 0, image.pixelBytes, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data);
                }

                // call this AFTER creating the texture
                glGenerateMipmap(GL_TEXTURE_2D);
            }

            free(image.data);
        }
    }

    return ret;
}

void texture_destroy(GLuint id)
{
    if (glIsTexture(id))
    {
        glDeleteTextures(1, &id);
    }
}