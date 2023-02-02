#pragma once
#ifndef SCOP_H
# define SCOP_H

// #if __linux__
	// # include <GL/gl.h>
	# include <glad/glad.h>
// #elif __MACH__
// 	# include <openGL/gl3.h>
// #endif

# include <GLFW/glfw3.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h> 
# include "libft.h"
# include "libvec.h"


// #define ROUND_UP 0.01

#ifndef OBJECT_PATH
# define OBJECT_PATH "./sources/shaders/object_shaders/"
#endif
#ifndef LIGHT_PATH
# define LIGHT_PATH "./sources/shaders/lighting_shaders/"
#endif

#define WIDTH 1280
#define HEIGHT 1280

#define PI 3.14

typedef struct s_vertices
{
	float	x;
	float	y;
	float	z;

}				t_vertex;

typedef struct object_s
{
	float				angle_in_radians;
	float 				delta;
	float				*vertices;
	int					amount_faces;
	int					amount_coordinates;
	short				should_rotate;
	GLuint				VBO;
	GLuint				EBO;
	GLuint				VAO;
	GLuint				*faces;
	t_mat4				translation_matrice;
	t_vec3f				translation_vector;
	t_vec3f				center_vector;
	t_mat4				rotation_matrice;
	t_vec3f				rotation_vector;
	t_mat4				color_matrice;
	t_mat4				lighting_matrice;

}				object_t;


typedef struct scop_s
{
	char				**obj;
	int					amount_objects;
	int					working_object;
	int					shader_program;
	GLFWmonitor			*primary;
	GLFWwindow			*window;
	const GLFWvidmode	*video_mode;
	object_t			**objects;
	object_t			*lighting;

}	scop_t;

scop_t	*ft_get_context(void);
int		parse_files(scop_t *context);
int		normalize_vertexes(void);
int		compile_shader_progs(scop_t	*context);
void	rotate_y(scop_t *context);
void	create_buffers(object_t **objects);
void	update_buffers(scop_t *context);
void	center_object(scop_t *context);
void	reset_matrice();
GLchar	*get_vertex_shader(void);
GLchar	*get_fragment_shader(void);
void	get_center(void);
void	invert_w(float *inverted_matrice ,float *matrice);

#endif