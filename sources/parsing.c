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
// 	context->amount_vertices++;
// 	return (1);
// }

int	add_vertice(char **vertices_info)
{
	scop_t *context = ft_get_context();
	int i = -1;
	int size = 0;

	while (vertices_info[size+1])
		size++;
	if (!(context->vertices = realloc(context->vertices, sizeof(float*) * (context->amount_vertices + size))))
		return (-1);
	context->amount_vertices += size;
	while (++i < size)
		context->vertices[i + context->amount_vertices] = atof(vertices_info[i+1]);
	return (0);
}

int	push_back_faces(char **face_info)
{
	int		i = 0;
	int		size = 0;
	faces_t	*new;
	scop_t	*context = ft_get_context();

	while (face_info[size+1])
		size++;
	if (!(new = (faces_t *)malloc(sizeof(*new))))
		return (-1);
	new->length = size;
	if (!(new->indexes = malloc(sizeof(int) * size)))
		return (-1);
	while (face_info[++i])
		new->indexes[i-1] = atoi(face_info[i]);
	if (context->faces)
	{
		context->faces->next = new;
		new->previous = context->faces;
	}
	context->faces = new;
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
					if (add_vertice(tab_info) < 0)
						return (-1);
			}
			else if (!ft_strcmp(tab_info[0], "f"))
				if (push_back_faces(tab_info) < 0)
					return (-1);
		// else if ((ft_strcmp(tab_info[0], "mtllib")))
		// {

		// }
			for (i = 0; i < 4; i++)
				free(tab_info[i]);
			free(tab_info);
			free(line);
		}
	}
	return (1);
}