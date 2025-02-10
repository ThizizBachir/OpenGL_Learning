#pragma once
#include <iostream>          
#include "glad\glad.h"
#include "stb_image.h"


unsigned int TextureFromFile(const char* filename) {
    unsigned int id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //texture loading
    int width, height, nrchannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename, &width, &height, &nrchannels, 0);

    if (data) {

        GLenum format;
        if (nrchannels == 1)
            format = GL_RED;
        else if (nrchannels == 3)
            format = GL_RGB;
        else if (nrchannels == 4)
            format = GL_RGBA;
        glTexImage2D( GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "width:" << width << "   height:" << height << "    nrchannels:" << nrchannels << std::endl;
    }
    else
    {
        std::cout << "ERROR::Texture::Failed to load texture" << "\n"; 
    }

    stbi_image_free(data);

    return id;
}