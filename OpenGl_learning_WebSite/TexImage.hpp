#pragma once
#include <iostream>          
#include "glad\glad.h"
#include "stb_image.h"


unsigned int makeTexture2D(const char* filename, GLint rgb_rgba ,bool log_W_H=false) {
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
        glTexImage2D(GL_TEXTURE_2D, 0, rgb_rgba, width, height, 0, rgb_rgba, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else { std::cout << "ERROR::Texture::Failed to load texture" << "\n"; }

    if (log_W_H) {
        std::cout << "widhth=" << width << " height=" << height << "\n";
    }

    stbi_image_free(data);
    return id;
}