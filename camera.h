#ifndef CAMERA_H
#define CAMERA_H

#define GLM_ENABLE_EXPERIMENTAL

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

void CameraCreate(int width, int height, glm::vec3 position, GLFWwindow* window);
void CameraMatrix(float FOVdeg, float nearPlane, float farPlane, GLuint shaderProgram, const char* uniform);
void CameraInputs(GLFWwindow* window);

#endif