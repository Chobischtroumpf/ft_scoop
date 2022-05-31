#pragma once
#ifndef SCOP_H
# define SCOP_H

// #if linux
// 	# include <GL/gl.h>
// #elif darwin
// 	# include <openGL/gl3.h>
// #endif

# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
#include <math.h>
# include "libft.h"
# include "libvec.h"

// #define ROUND_UP 0.01

#ifndef SHADERS_PATH
# define SHADERS_PATH "./sources/shaders/"
#endif
#define PI 3.14159265

typedef struct s_vertices
{
	float	x;
	float	y;
	float	z;

}				t_vertex;

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
	t_mat4				translation_matrice;
	t_vec3f				translation_vector;
	t_vec3f				center_vector;
	t_mat4				rotation_matrice;
	t_vec3f				rotation_vector;
	t_mat4				color_matrice;
	char				*obj;
	int					shader_program;
	float				rotation_speed;
}	scop_t;

scop_t	*ft_get_context(void);
int		parse_file(scop_t *context);
void	create_buffers(scop_t *context);
int		normalize_vertexes(void);
int		compile_shader_progs(scop_t	*context);
void	rotate_y(scop_t *context);
void	update_buffers(scop_t *context);
void	center_object(scop_t *context);
void	reset_matrice();
char	*get_vertex_shader(void);
char	*get_fragment_shader(void);
void	get_center(void);
void	invert_w(float *inverted_matrice ,float *matrice);

#endif