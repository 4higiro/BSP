#version 330 core
layout (location = 0) in vec3 vertexCoords;
layout (location = 1) in vec3 vertexColors;
out vec3 color;
uniform mat4 transform;
void main() 
{
	color = vertexColors;
	gl_Position = transform * vec4(vertexCoords, 1.0f);
}