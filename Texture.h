#pragma once
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stb_image.h>

using uint = unsigned int;

class Texture {

private:
    uint ID;
    int enumType;

public:
    Texture();

    void bind(int enumType);
    void generateTexture(const char* file, int rgbType);
};

#endif

Texture::Texture() {
    glGenTextures(1, &ID);
}

void Texture::bind(int enumType) {
    this->enumType = enumType;
    glBindTexture(enumType, ID);
}

void Texture::generateTexture(const char* file, int rgbType) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

    if (nullptr == data) {
        printf("Failed to load %s resource!", file);
        glfwTerminate();
        exit(1);
    }

    glTexImage2D(enumType, 0, rgbType, width, height, 0, rgbType, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(enumType);

    stbi_image_free(data);
}