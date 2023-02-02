#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

// out vec4 vertexColor;
out vec4 ourColor;
uniform mat4 transform;
uniform mat4 translation;
uniform mat4 coloration;

void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * aColor;

	vec3 result= ambient * objectColor
	gl_Position = transform* vec4(aPos, 0.5);
	resultingColor = /*coloration * */ 
}