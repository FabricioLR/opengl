#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

GLuint EBOCreate(GLuint* indices, GLsizeiptr size);
void EBOBind(GLuint EBO);
void EBOUnbind(GLuint EBO);
void EBODelete(GLuint EBO);

#endif