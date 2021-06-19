#include "scop.h"

static GLuint	creating_shader_obj(const GLchar *fragment_shader_source, int shader_opt)
{
	GLuint shader;
	int  success;
	char infoLog[512];

	shader = glCreateShader(shader_opt);
	glShaderSource(shader, 1, &(fragment_shader_source), NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("Error: %s\n", infoLog);
		return (0);
	}
	return (shader);
}

int	compile_shader_progs(scop_t	*context)
{
	int  success;
	char infoLog[512];
	const GLchar		*vertex_shader_source = "#version 330 core\nlayout (location = 0) in vec3 aPos;\n"
		"void main()\n{\n	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}\0";
	const GLchar		*fragment_shader_source = "#version 330 core\nout vec4 FragColor;\n"
		"void main()\n{\n	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n}\0";
	GLuint				vertex_shader = creating_shader_obj(vertex_shader_source, GL_VERTEX_SHADER);
	GLuint				fragment_shader = creating_shader_obj(fragment_shader_source, GL_FRAGMENT_SHADER);
	
	if (!vertex_shader || !fragment_shader)
		return (-1);
 	context->shader_program = glCreateProgram();
	glAttachShader(context->shader_program, vertex_shader);
	glAttachShader(context->shader_program, fragment_shader);
	glLinkProgram(context->shader_program);
	glGetProgramiv(context->shader_program, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(context->shader_program, 512, NULL, infoLog);
		printf("Error: %s\n", infoLog);
		return (-1);
	}
	glUseProgram(context->shader_program);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);  
	return (0);
}

void	create_buffers(scop_t	*context)
{
	glGenBuffers(1, &(context->VBO));
	glBindBuffer(GL_ARRAY_BUFFER, context->VBO);
	glBufferData(GL_ARRAY_BUFFER, (3 * sizeof(float) * context->amount_coordinates), context->vertices, GL_DYNAMIC_DRAW);

	glGenVertexArrays(1, &(context->VAO));
	glBindVertexArray(context->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, context->VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float*), (void*)0);
	glEnableVertexAttribArray(0);
}