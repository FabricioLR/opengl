#include "texture.h"

GLenum type;

GLuint TextureCreate(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType){
	GLuint Texture;

    type = texType;

	int widthImg, heightImg, numColCh;
	
	stbi_set_flip_vertically_on_load(true);

	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	glGenTextures(1, &Texture);
	glActiveTexture(slot);
	glBindTexture(texType, Texture);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);

	stbi_image_free(bytes);

	glBindTexture(texType, 0);

    return Texture;
}

void TextureTexUnit(GLuint shaderProgram, const char* uniform, GLuint unit){
	GLuint texUni = glGetUniformLocation(shaderProgram, uniform);

	glUseProgram(shaderProgram);

	glUniform1i(texUni, unit);
}

void TextureBind(GLuint Texture, GLenum texType){
	glBindTexture(type, Texture);
}

void TextureUnbind(GLenum texType){
	glBindTexture(type, 0);
}

void TextureDelete(GLuint Texture){
	glDeleteTextures(1, &Texture);
}