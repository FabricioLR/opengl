#include "camera.h"

glm::vec3 Position;
glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

int global_width;
int global_height;

bool firstClick = true;

float speed = 0.005f;
float sensitivity = 100.0f;

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
    double mouseX;
    double mouseY;

    glfwGetCursorPos(window, &mouseX, &mouseY);

    float rotX = sensitivity * (float)(mouseY - (global_height / 2)) / global_height;
    float rotY = sensitivity * (float)(mouseX - (global_width / 2)) / global_width;

    printf("%f %f\n", rotX, rotY);

    glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

    if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f)){
        Orientation = newOrientation;
    }

    Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

    //glfwSetCursorPos(window, (global_width / 2), (global_height / 2));
}

void CameraCreate(int width, int height, glm::vec3 position, GLFWwindow* window){
	global_width = width;
	global_height = height;
	Position = position;

    //glfwSetCursorPosCallback(window, cursor_position_callback);
}

void CameraMatrix(float FOVdeg, float nearPlane, float farPlane, GLuint shaderProgram, const char* uniform){
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(Position, Position + Orientation, Up);
    projection = glm::perspective(glm::radians(FOVdeg), (float)global_width / global_height, nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void CameraInputs(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        Position += speed * Orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        Position += speed * -glm::normalize(glm::cross(Orientation, Up));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        Position += speed * -Orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        Position += speed * glm::normalize(glm::cross(Orientation, Up));
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        Position += speed * Up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
		Position += speed * -Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
		speed = 0.02f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE){
		speed = 0.005f;
	}

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (firstClick){
			glfwSetCursorPos(window, (global_width / 2), (global_height / 2));
			firstClick = false;
		}

        double mouseX;
		double mouseY;
    
		glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotX = sensitivity * (float)(mouseY - (global_height / 2)) / global_height;
		float rotY = sensitivity * (float)(mouseX - (global_width / 2)) / global_width;

        glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f)){
			Orientation = newOrientation;
		}

		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		glfwSetCursorPos(window, (global_width / 2), (global_height / 2));

    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        firstClick = true;
    }
}

