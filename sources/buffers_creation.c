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
	const GLchar		*vertex_shader_source = get_vertex_shader();
	const GLchar		*fragment_shader_source = get_fragment_shader();
	
	if (!vertex_shader_source || !fragment_shader_source)
		return(-1);
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
	// glUseProgram(context->shader_program);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);  
	return (0);
}

void	create_buffers(scop_t	*context)
{
	glGenBuffers(1, &(context->VBO));
	glBindBuffer(GL_ARRAY_BUFFER, context->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * context->amount_coordinates, context->vertices, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &(context->EBO));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, context->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * context->amount_faces, context->faces, GL_STATIC_DRAW);
	glGenVertexArrays(1, &(context->VAO));
	glBindVertexArray(context->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, context->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, context->EBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	context->rotation_matrice[0] = 1;
	context->rotation_matrice[5] = 1;
	context->rotation_matrice[10] = 1;
	context->rotation_matrice[15] = 1;
	glUniformMatrix4fv(glGetUniformLocation(context->shader_program, "transform"), 1, GL_FALSE, context->rotation_matrice);

}

void update_buffers(scop_t *context)
{
	glBindVertexArray(context->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, context->VBO);
	rotate_y(context);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * context->amount_coordinates, context->vertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, context->EBO);
	// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	// Color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
}