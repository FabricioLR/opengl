#include "EBO.h"

GLuint EBOCreate(GLuint* indices, GLsizeiptr size){
    GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

    return EBO;
}

void EBOBind(GLuint EBO){
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void EBOUnbind(GLuint EBO){
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBODelete(GLuint EBO){
	glDeleteBuffers(1, &EBO);
}