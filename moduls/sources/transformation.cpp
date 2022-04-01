// Including
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <iostream>

#include "transformation.h"

// Using names
using namespace glm;
using namespace std;

// Load identity matrix
void loadIdentity(GLuint program_ID)
{
	mat4 m = mat4(1.0f);

	glUniformMatrix4fv(glGetUniformLocation(program_ID, "transform"), 1, GL_FALSE, value_ptr(m));
}

// View from (45, 45, 45)* angle
void standartPerspectTransform(GLuint ID)
{
	mat4 m = mat4(1.0f);
	m = rotate(m, radians(285.0f), vec3(1.0f, 0.0f, 0.0f));
	m = rotate(m, radians(225.0f), vec3(0.0f, 0.0f, 1.0f));

	glUniformMatrix4fv(glGetUniformLocation(ID, "transform"), 1, GL_FALSE, value_ptr(m));
}
