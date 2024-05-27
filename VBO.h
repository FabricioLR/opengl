#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

GLuint VBOCreate(GLfloat* vertices, GLsizeiptr size);
void VBOBind(GLuint VBO);
void VBOUnbind(GLuint VBO);
void VBODelete(GLuint VBO);

#endif