#include "scop.h"

// int push_back_vertice(char **vertice_info)
// {
// 	scop_t *context = ft_get_context();
// 	vertices_t	*new;
// 	int i = -1;

// 	if (!(new = (vertices_t*)malloc(sizeof(*new))))
// 		return (-1);
// 	while (++i < 3)
// 		new->coordinates[i] = atof(vertice_info[i+1]);
// 	new->next = NULL;
// 	new->previous = NULL;
// 	if (context->vertices)
// 	{
// 		context->vertices->next = new;
// 		new->previous = context->vertices;
// 	}
// 	context->vertices = new;
// 	context->amount_coordinates++;
// 	return (1);
// }

int	add_vertice(char **vertices_info, scop_t *context)
{
	// scop_t *context = ft_get_context();
	int i = -1;
	int size = 0;

	while (vertices_info[size+1])
		size++;
	if (!(context->vertices = realloc(context->vertices, sizeof(float) * (context->amount_coordinates + size))))
		return (-1);
	while (++i < size)
		context->vertices[i + context->amount_coordinates] = atof(vertices_info[i+1]);
	context->amount_coordinates += size;
	return (0);
}

int	add_faces(char **face_info, scop_t *context)
{
	int i = -1;
	int size = 0;

	while (face_info[size+1])
		size++;
	if (size == 4)
		size = 6;
	if (!(context->faces = realloc(context->faces, sizeof(GLuint) * (context->amount_faces + size))))
		return (-1);
	if (size != 6)
		while (++i < size)
			context->faces[i + context->amount_faces] = atoi(face_info[i+1]) -1;
	else
	{
		while (++i < 3)
			context->faces[i + context->amount_faces] = atoi(face_info[i+1]) - 1;
		context->faces[i++ + context->amount_faces] = atoi(face_info[1]) - 1;
		context->faces[i++ + context->amount_faces] = atoi(face_info[3]) - 1;
		context->faces[i + context->amount_faces] = atoi(face_info[4]) - 1;
	}
	context->amount_faces += size;
	return (0);
}

int	parse_file(scop_t *context)
{
	int		fd;
	int		i;
	char	*line;
	char	**tab_info;

	if (!ft_strlast(context->obj, ".obj"))
		return(-1);
	fd = open(context->obj, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strncmp(line, "v", 1) && ft_strncmp(line, "f", 1))
		{
			free(line);
			continue ;
		}
		else
		{
			tab_info = ft_split(line, ' ');
			if (!ft_strcmp(tab_info[0], "v"))
			{
					if (add_vertice(tab_info, context) < 0)
						return (-1);
			}
			else if (!ft_strcmp(tab_info[0], "f"))
			{
				if (add_faces(tab_info, context) < 0)
					return (-1);
			}
			for (i = 0; i < 4; i++)
				free(tab_info[i]);
			free(tab_info);
			free(line);
		}
	}
	// int x = 0;
	// while(x < context->amount_faces)
	// 	printf("element: %d\n", context->faces[x++]);
	// printf("x : %d\n", x);
	center_object(context);
	normalizing_coordinates(context);
	return (1);
}