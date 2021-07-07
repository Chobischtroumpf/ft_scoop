#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

// out vec4 vertexColor;
out vec4 ourColor;
uniform mat4 transform;
uniform mat4 trl_to_center;
uniform mat4 trl_from_center;
uniform mat4 coloration;

void main()
{
	gl_Position = ((trl_to_center * transform) * trl_from_center)* vec4(aPos, 1.0);
	ourColor = /*coloration * */ vec4(aColor, 1.0);
}