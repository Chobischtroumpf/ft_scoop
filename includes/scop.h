#ifndef SCOP_H
# define SCOP_H

# include <openGL/gl3.h>
# include <GLFW/glfw3.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
#include <math.h>
# include "libft.h"

#define ROUND_UP 0.01
#define ROTATION_SPEED 0.017453292

typedef struct scop_s
{
	GLFWmonitor			*primary;
	GLFWwindow			*window;
	const GLFWvidmode	*video_mode;
	GLuint				VBO;
	GLuint				EBO;
	GLuint				VAO;
	float				*vertices;
	GLuint				*faces;
	int					amount_faces;
	int					amount_coordinates;
	// float				center[3];
	char				*obj;
	int					shader_program;
	
}	scop_t;

scop_t	*ft_get_context(void);
int		parse_file(scop_t *context);
void	create_buffers(scop_t *context);
void	normalizing_coordinates(scop_t *context);
int		compile_shader_progs(scop_t	*context);
void	rotate_y(scop_t *context);
void	update_buffers(scop_t *context);
void	center_object(scop_t *context);

#endif