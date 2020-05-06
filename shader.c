#include "shader.h"

#include <stdio.h>
#include <stdlib.h>

GLuint createShader(const char* fileName, const GLenum type)
{
    GLuint id = 0;  // return
    FILE* file = NULL;
    int fileSize = 0;
    char* buffer = NULL;
    GLint compileStatus = 0;
    GLint infoLogLength = 0;
    
    if (fileName)
    {
        if (fopen_s(&file, fileName, "rb") == 0)
        {
            fseek(file, 0, SEEK_END);   // goto eof
            fileSize = ftell(file);     // get pos
            fseek(file, 0, SEEK_SET);   // ret to start
            buffer = (char*)malloc(fileSize + 1);   // alloc source buf (+ null)

            if (buffer)
            {
                fread(buffer, fileSize, 1, file);   // read into it
                buffer[fileSize] = '\0';            // set null-terminator

                id = glCreateShader(type);
                // count = 1 : 1 row (1d array);
                // lengths = NULL : null-terminated
                glShaderSource(id, 1, (const GLchar**)&buffer, NULL);
                glCompileShader(id);
                free(buffer);

                glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);

                if (compileStatus) // GL_TRUE
                {
                    printf("Successfully compiled shader.\n");
                }
                else // GL_FALSE
                {
                    printf("Failed to compile shader %s.\n", fileName);

                    // infoLogLength includes null-terminator
                    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
                    buffer = (char*)malloc(infoLogLength);

                    if (buffer)
                    {
                        glGetShaderInfoLog(id, infoLogLength, &infoLogLength, buffer);
                        printf("%s", buffer);
                        free(buffer);
                    }
                    else
                    {
                        printf("Failed to allocate memory.\n");
                    }

                    glDeleteShader(id);

                    id = 0;
                }
            }
            else
            {
                printf("Failed to allocate memory.\n");
            }
        }
        else
        {
            printf("Failed to open file.\n");
        }
    }
    else
    {
        printf("Invalied pointer to file name.\n");
    }

    return id;
}

GLuint createProgram(const GLuint vert, const GLuint frag)
{
    GLuint id = 0;
    GLint linkStatus = 0;
    GLint infoLogLength = 0;
    char* buffer = NULL;

    if (vert && frag)
    {        
        id = glCreateProgram();

        if (id)
        {
            printf("Attaching shaders.\n");
            glAttachShader(id, vert);
            glAttachShader(id, frag);

            printf("Linking shader program.\n");
            glLinkProgram(id);

            glGetProgramiv(id, GL_LINK_STATUS, &linkStatus);

            if (linkStatus)
            {
                printf("Successfully linked program.");

                // MUST call this line before getting variable locations
                glUseProgram(id);
            }
            else
            {
                printf("Failed to link program!\n");

                // infoLogLength includes null-terminator
                glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);

                // get and print info log
                buffer = (char*)malloc(infoLogLength);

                if (buffer)
                {
                    glGetProgramInfoLog(id, infoLogLength, &infoLogLength, buffer);
                    printf("%s", buffer);
                    free(buffer);
                }
                else
                {
                    printf("Failed to allocate memory for error info log.\n");
                }

                // delete failed program
                glDetachShader(id, vert);
                glDetachShader(id, frag);
                glDeleteProgram(id);

                // set id to 0 for return
                id = 0;
            }
        }
        else
        {
            printf("Failed to create program.\n");
        }
    }
    else
    {
        printf("Invalid arguments.\n");
    }

    return id;
}