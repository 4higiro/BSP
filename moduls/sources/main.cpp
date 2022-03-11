// Including
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shaders/shaders.h"
#include "buffer_objects/buffer_objects.h"
#include "avl_tree/avl_tree.h"

// Size of window
#define WINDOW_WIDTH 450
#define WINDOW_HEIGHT 450

// Callback function GLFW
void sizeCallback(GLFWwindow* window, int width, int height);

// General keyboard event proccesor
void processKeyboardEvents(GLFWwindow* window);

// Namespaces
using namespace std;

// Input in program
int main()
{
	// Add russion language
	setlocale(LC_ALL, "Ru");

	// GLFW init
	if (!glfwInit())
		return -1;

	// Set version OpenGL 3.3 Core Profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create graphic window
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GRAPHICS WINDOW", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Make OpenGL context for window
	glfwMakeContextCurrent(window);

	// GLAD init
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		return -1;
	}

	// Limitation viewport
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(window, sizeCallback);

	// Load shaders for color rendering
	vertex_shader colorVertexShader;
	string path = COLOR_SHADER_PATH + (string)"vertex_shader.glsl";
	loadShader(path.c_str(), &colorVertexShader);
	fragment_shader colorFragmentShader;
	path = COLOR_SHADER_PATH + (string)"fragment_shader.glsl";
	loadShader(path.c_str(), &colorFragmentShader);

	// Create shader program for color rendering
	shader_program colorShaderProgram(colorVertexShader, colorFragmentShader);

	// Using shader program
	colorShaderProgram.use();

	/////////////////////////////////////////////////////////////////////////////////////////////////

	GLfloat coords[9] = {
		-0.5f, -0.3f, 0.0f,
		0.5f, -0.3f, 0.0f,
		0.0f, 0.7f, 0.0f
	};

	GLfloat colors[9] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	GLuint indexes[3] = { 0, 1, 2 };

	vbo coordsVBO(coords, 9, 3);
	vbo colorsVBO(colors, 9, 3);
	vao VAO;
	VAO.addVBO(coordsVBO);
	VAO.addVBO(colorsVBO);
	ebo EBO(VAO, indexes, 3);

	/////////////////////////////////////////////////////////////////////////////////////////////////

	// Rendering
	while (!glfwWindowShouldClose(window))
	{
		processKeyboardEvents(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		EBO.draw(GL_TRIANGLES);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// GLFW resources clear
	glfwTerminate();
	return 0;
}

// General keyboard event proccesor
void processKeyboardEvents(GLFWwindow* window)
{
	// Cloose window (ESCAPE)
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// Callback function GLFW
void sizeCallback(GLFWwindow* window, int width, int height)
{
	// Change window size
	glViewport(0, 0, width, height);
}