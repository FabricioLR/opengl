#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "VBO.h"

GLuint VAOCreate();
void VAOLinkAttrib(GLuint VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
void VAOBind(GLuint VAO);
void VAOUnbind(GLuint VAO);
void VAODelete(GLuint VAO);

#endif