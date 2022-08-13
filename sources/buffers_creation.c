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
	
	if (vertex_shader_source == (GLchar *)NULL || fragment_shader_source == (GLchar *)NULL){
		printf("Error: can't get shader source\n");
		return(-1);
	}
	for (int i = 0; i < context->amount_objects; i++)
	{
		// printf("Compiling shader program %d\n", i);
		// printf("creating vertex_shader\n");
		GLuint	vertex_shader = creating_shader_obj(vertex_shader_source, GL_VERTEX_SHADER);
		// printf("creating fragment_shader\n");
		GLuint	fragment_shader = creating_shader_obj(fragment_shader_source, GL_FRAGMENT_SHADER);
		if (!vertex_shader || !fragment_shader){
			printf("Error: can't create shader\n");
			return (-1);
		}
		// printf("freeing vertex_shader\n");
		// free((void *)vertex_shader_source);
		// printf("freeing fragment_shader\n");
		// free((void *)fragment_shader_source);
		printf("%s\n", vertex_shader_source);
		printf("%s\n", fragment_shader_source);
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
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);  
	}
	return (0);
}

void	create_buffers(object_t **objects)
{
	for (int i =0; i < ft_get_context()->amount_objects; i++)
	{
		glGenBuffers(1, &(objects[i]->VBO));
		glBindBuffer(GL_ARRAY_BUFFER, objects[i]->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * objects[i]->amount_coordinates, objects[i]->vertices, GL_DYNAMIC_DRAW);
		glGenBuffers(1, &(objects[i]->EBO));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objects[i]->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * objects[i]->amount_faces, objects[i]->faces, GL_STATIC_DRAW);
		glGenVertexArrays(1, &(objects[i]->VAO));
		glBindVertexArray(objects[i]->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, objects[i]->VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objects[i]->EBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glUniformMatrix4fv(glGetUniformLocation(ft_get_context()->shader_program, "transform"), 1, GL_FALSE, (void*)objects[i]->rotation_matrice.value);
	}
}

void update_buffers(scop_t *context)
{
	for (int i = 0; i < context->amount_objects; i++)
	{
		glBindVertexArray(context->objects[i]->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, context->objects[i]->VBO);
		rotate_y(context);
		// printf("apres rotate_y\n");
		// m4_print(context->objects[i]->rotation_matrice);
		// m4_print(context->objects[i]->translation_matrice);

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * context->objects[i]->amount_coordinates, context->objects[i]->vertices, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, context->objects[i]->EBO);
		// Position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		// Color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	}
}
