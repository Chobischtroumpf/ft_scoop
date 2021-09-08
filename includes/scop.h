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
# include "libvec.h"

// #define ROUND_UP 0.01

#ifndef ROTATION_SPEED
# define ROTATION_SPEED 25
#endif

#ifndef SHADERS_PATH
# define SHADERS_PATH "./sources/shaders/"
#endif
#define PI 3.14159265
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
	t_mat4				rotation_matrice;
	t_mat4				color_matrice;
	t_mat4				center_matrice;
	char				*obj;
	int					shader_program;
	float				rotation_speed;
}	scop_t;

scop_t	*ft_get_context(void);
int		parse_file(scop_t *context);
void	create_buffers(scop_t *context);
int		normalizing_coordinates(scop_t *context);
int		compile_shader_progs(scop_t	*context);
void	rotate_y(scop_t *context);
void	update_buffers(scop_t *context);
void	center_object(scop_t *context);
void	reset_matrice(float *matrice);
char	*get_vertex_shader(void);
char	*get_fragment_shader(void);
void	get_center(float *center, int amount_coordinates, float *vertices);
void	invert_w(float *inverted_matrice ,float *matrice);

#endif