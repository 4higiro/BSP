// Including
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <fstream>
#include <string>

#include "buffer_objects/buffer_objects.h"
#include "shaders/shaders.h"
#include "avl_tree/avl_tree.h"

using namespace std;

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
	const char* source = "#version 330 core\n"
		"layout(location = 0) in vec3 vertexCoords;\n"
		"layout(location = 1) in vec3 vertexColors;\n"
		"out vec3 color;\n"
		"void main()"
		"{"
		"color = vertexColors;\n"
		"gl_Position = vec4(vertexCoords, 1.0f);\n"
		"}";
	colorVertexShader.changeShader(source);
	fragment_shader colorFragmentShader;
	source = "#version 330 core\n"
		"in vec3 color;\n"
		"out vec4 fragmentColor;\n"
		"void main()"
		"{"
		"fragmentColor = vec4(color, 0.0f);\n"
		"}";
	colorFragmentShader.changeShader(source);

	// Create shader program for color rendering
	shader_program colorShaderProgram(colorVertexShader, colorFragmentShader);

	// Using shader program
	colorShaderProgram.use();

	/////////////////////////////////////////////////////////////////////////////////////////////////
	int coordsArraySize = 0;
	int colorsArraySize = 0;

	GLfloat* coords = new GLfloat[coordsArraySize];
	GLfloat* colors = new GLfloat[colorsArraySize];
	GLuint indexes[6] = {
		0, 1, 2, 1, 2, 3
	};
	
	ifstream coordsFile;
	ifstream colorsFile;

	cout << "Coords:" << endl;
	coordsFile.open("coordsFile.txt");

	if (!coordsFile.is_open()) {

		cout << "Cant open file" << endl;

	}
	else {

		while (coordsFile >> coords[coordsArraySize]) {

			cout << coords[coordsArraySize] << endl;
			coordsArraySize++;
		}
	}

	cout << "Colors:" << endl;
	colorsFile.open("colorsFile.txt");

	if (!colorsFile.is_open()) {

		cout << "Cant open file" << endl;

	}
	else {

		while (colorsFile >> colors[colorsArraySize]) {

			cout << colors[colorsArraySize] << endl;
			colorsArraySize++;
		}
	}

	vbo coordsVBO(coords, coordsArraySize, 3);
	vbo colorsVBO(colors, colorsArraySize, 3);

	vao VAO;
	VAO.addVBO(coordsVBO);
	VAO.addVBO(colorsVBO);

	ebo EBO(VAO, indexes, coordsArraySize/12);
	/////////////////////////////////////////////////////////////////////////////////////////////////

	// Rendering
	while (!glfwWindowShouldClose(window))
	{
		processKeyboardEvents(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		EBO.draw(GL_TRIANGLES);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 1, 4);

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