#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "camera.h"
#include "texture.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

char **get_file_contents(char *filename, int *length){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        printf("fopen failed\n");
    }

    int lines = 1;
    while(!feof(fp)){
        if(fgetc(fp) == '\n'){
            lines++;
        }
    }

    if (strcmp(filename, "default.vert") == 0){
        //lines++;
    }

    fseek(fp, 0, SEEK_SET);

    char **strings;

    *length = lines;

    printf("lines start %d\n", lines);
 
    strings = (char**)malloc(*length * sizeof(char*)); 

    printf("sim\n");
    char buffer2[1500];

    int i = 0;
    while (fgets(buffer2, 1500, fp)) {
        printf("%d %s\n", i, buffer2);
        strings[i] = (char*)malloc(strlen(buffer2) * sizeof(char));
        strcpy(strings[i], buffer2);
        //printf("index: %d string: %s\n", i, strings[i]);
        i++;
    }
    printf("lines end %d\n", i);
    printf("string: %s\n", strings[i - 1]);

    return strings;
}

void compileErrors(unsigned int shader, const char* type){
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM"){
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE){
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			printf("SHADER_COMPILATION_ERROR for: %s %s\n", type, infoLog);
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE){
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            printf("SHADER_LINKING_ERROR for: %s %s\n", type, infoLog);
		}
	}
}

int main(){
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat vertices[] = {
        -0.1f, -0.1f,  0.1f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
        -0.1f, -0.1f, -0.1f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,
        0.1f, -0.1f, -0.1f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        0.1f, -0.1f,  0.1f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
        -0.1f,  0.1f,  0.1f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
        -0.1f,  0.1f, -0.1f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,
        0.1f,  0.1f, -0.1f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        0.1f,  0.1f,  0.1f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 4, 7,
        0, 7, 3,
        3, 7, 6,
        3, 6, 2,
        2, 6, 5,
        2, 5, 1,
        1, 5, 4,
        1, 4, 0,
        4, 5, 6,
        4, 6, 7
    };

    GLFWwindow *window = glfwCreateWindow(800, 800, "OPENGL", NULL, NULL);
    if (window == NULL){
        printf("glfwCreateWindow failed\n");
        return 0;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, 800, 800);

    int lengthVert, lengthFrag;
    char **vertexShaderSource2 = get_file_contents("default.vert", &lengthVert);
    char **fragmentShaderSource2 = get_file_contents("default.frag", &lengthFrag);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, lengthVert, (const GLchar * const*)vertexShaderSource2, NULL);
    glCompileShader(vertexShader);

    compileErrors(vertexShader, "VERTEX");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, lengthFrag, (const GLchar * const*)fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader);

    compileErrors(fragmentShader, "FRAGMENT");

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    compileErrors(shaderProgram, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VAO1 = VAOCreate();
	VAOBind(VAO1);

	GLuint VBO1 = VBOCreate(vertices, sizeof(vertices));
	GLuint EBO1 = EBOCreate(indices, sizeof(indices));

	VAOLinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAOLinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAOLinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAOUnbind(VAO1);
	VBOUnbind(VBO1);
	EBOUnbind(EBO1);

    //GLuint uniID = glGetUniformLocation(shaderProgram, "scale");

	GLuint brick = TextureCreate("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	TextureTexUnit(shaderProgram, "tex0", 0);

    glEnable(GL_DEPTH_TEST);

    CameraCreate(800, 800, glm::vec3(0.0f, 0.0f, 2.0f), window);

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.07f, 0.07f, 0.07f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);

        TextureBind(brick, GL_TEXTURE_2D);

        CameraInputs(window);
        CameraMatrix(80.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

        //glUniform1f(uniID, 0.2f);

        VAOBind(VAO1);
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    VAODelete(VAO1);
	VBODelete(VBO1);
	EBODelete(EBO1);
    TextureDelete(brick);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}