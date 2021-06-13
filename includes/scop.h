#ifndef SCOP_H
# define SCOP_H

# include <openGL/gl.h>
# include <GLFW/glfw3.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2


typedef struct	vertices_s
{
	char				type;
	float				coordinates[3];
	struct vertices_s	*next;
	struct vertices_s	*previous;

}		vertices_t;

typedef struct	faces_s
{
	float				*coordinates;
	int					length;
	GLuint				VBO;
	struct faces_s	*next;
	struct faces_s	*previous;

}		faces_t;


typedef struct scop_s
{
	GLFWmonitor			*primary;
	GLFWwindow			*window;
	const GLFWvidmode	*video_mode;
	vertices_t			*vertices;
	int					amount_vertices;
	faces_t				*faces;
	int					amount_faces; 
	char				*obj;
}	scop_t;

scop_t		*ft_get_context(void);
vertices_t	*rewind_vertices(vertices_t *vertices);
vertices_t	*back_vertices(vertices_t *vertices);
vertices_t	*new_vertice(void);
int			parse_file(scop_t *context);
vertices_t	*get_vertice(int pos);

#endif