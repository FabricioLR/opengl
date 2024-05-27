#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <stdbool.h>

GLuint TextureCreate(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
void TextureTexUnit(GLuint shaderProgram, const char* uniform, GLuint unit);
void TextureBind(GLuint Texture, GLenum texType);
void TextureUnbind(GLenum texType);
void TextureDelete(GLuint Texture);

#endif