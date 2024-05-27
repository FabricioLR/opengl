#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <math.h>
#include <stdlib.h>
#include <string.h>


//gcc main.c glad.c -o main -lglfw3 -lopengl32 -lgdi32

GLchar const* vertexShaderSource[] = {
    "#version 330 core\n", 
    "layout (location = 0) in vec3 aPos;\n", 
    "void main(){\n", 
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n", 
    "}\0"
}; 
GLchar const* fragmentShaderSource[] = {
    "#version 330 core\n", 
    "out vec4 FragColor;\n", 
    "void main(){\n", 
    "FragColor = vec4(0.8f, 0.3f, 0.2f, 1.0f);\n", 
    "}\0"
};

char **get_file_contents(char *filename, int *length){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        printf("fopen failed\n");
    }

    char **strings;

    *length = 5;

    strings = (char**)malloc(*length * sizeof(char*)); 

    char buffer2[255];

    int i = 0;
    while (fgets(buffer2, 255, fp)) {
        strings[i] = (char*)malloc(strlen(buffer2) * sizeof(char));
        strcpy(strings[i], buffer2);
        i++;
    }

    printf("sim\n");

    return strings;
}

int main(){
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    GLuint indeces[] = {
        0, 2, 1,
        0, 3, 2
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
    //glShaderSource(vertexShader, sizeof(vertexShaderSource)/sizeof(*vertexShaderSource), vertexShaderSource, NULL);
    glShaderSource(vertexShader, lengthVert, (const GLchar * const*)vertexShaderSource2, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragmentShader, sizeof(fragmentShaderSource)/sizeof(*fragmentShaderSource), fragmentShaderSource, NULL);
    glShaderSource(fragmentShader, lengthFrag, (const GLchar * const*)fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    glClearColor(0.07f, 0.07f, 0.07f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.07f, 0.07f, 0.07f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}