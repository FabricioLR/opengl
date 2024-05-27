#include"VAO.h"

// Constructor that generates a VAO ID
GLuint VAOCreate(){
    GLuint VAO;

	glGenVertexArrays(1, &VAO);

    return VAO;
}

// Links a VBO Attribute such as a position or color to the VAO
void VAOLinkAttrib(GLuint VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset){
	VBOBind(VBO);
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBOUnbind(VBO);
}

// Binds the VAO
void VAOBind(GLuint VAO){
	glBindVertexArray(VAO);
}

// Unbinds the VAO
void VAOUnbind(GLuint VAO){
	glBindVertexArray(0);
}

// Deletes the VAO
void VAODelete(GLuint VAO){
	glDeleteVertexArrays(1, &VAO);
}