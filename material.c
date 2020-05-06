#include "material.h"
#include "mglu.h"

void material_use(const Material* material)
{
    if (material)
    {
        /*
        glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
        glMaterialfv(GL_FRONT, GL_EMISSION, material->emission);
        glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);
        */

        //glUniform4fv(LOCATION_UNIFORM_MATERIAL_AMBIENT, 1, material->ambient);
        //glUniform4fv(LOCATION_UNIFORM_MATERIAL_DIFFUSE, 1, material->diffuse);
        //glUniform4fv(LOCATION_UNIFORM_MATERIAL_SPECULAR, 1, material->specular);
        //glUniform4fv(LOCATION_UNIFORM_MATERIAL_EMISSION, 1, material->emission);
        //glUniform1f(LOCATION_UNIFORM_MATERIAL_SHININESS, material->shininess);
        //glUniform1f(LOCATION_UNIFORM_MATERIAL_ROUGHNESS, 1, material->roughness);

        // 0 is null texture ID
        if (glIsTexture(material->texture0))
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, material->texture0);
        }
        if (glIsTexture(material->texture1))
        {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, material->texture1);
        }
        if (glIsTexture(material->texture2))
        {
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, material->texture2);
        }
        if (glIsTexture(material->texture3))
        {
            glActiveTexture(GL_TEXTURE3);
            glBindTexture(GL_TEXTURE_2D, material->texture3);
        }
    }
}