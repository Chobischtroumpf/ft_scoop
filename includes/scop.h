#ifndef SCOP_H
# define SCOP_H

# include <openGL/gl3.h>
# include <GLFW/glfw3.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2


typedef struct	faces_s
{
	int				*indexes;
	int				length;
	struct faces_s	*next;
	struct faces_s	*previous;

}		faces_t;


typedef struct scop_s
{
	GLFWmonitor			*primary;
	GLFWwindow			*window;
	const GLFWvidmode	*video_mode;
	GLuint				VBO;
	GLuint				EBO;
	GLuint				VAO;
	float				*vertices;
	faces_t				*faces;
	int					amount_coordinates;
	int					amount_faces;
	char				*obj;
	int					shader_program;
	
}	scop_t;

scop_t		*ft_get_context(void);
int			parse_file(scop_t *context);
void		create_buffers(scop_t *context);
void		normalizing_coordinates(scop_t *context);
int			compile_shader_progs(scop_t	*context);

#endif