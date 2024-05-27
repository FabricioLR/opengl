#include"VBO.h"

// Constructor that generates a Vertex Buffer Object and links it to vertices
GLuint VBOCreate(GLfloat* vertices, GLsizeiptr size){
	GLuint VBO;
    
    glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    return VBO;
}

// Binds the VBO
void VBOBind(GLuint VBO){
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

// Unbinds the VBO
void VBOUnbind(GLuint VBO){
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VBODelete(GLuint VBO){
	glDeleteBuffers(1, &VBO);
}