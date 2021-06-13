#include "scop.h"

int push_back_vertice(char **vertice_info)
{
	scop_t *context = ft_get_context();
	vertices_t	*new;
	int i = -1;

	if (!(new = (vertices_t*)malloc(sizeof(*new))))
		return (-1);
	while (++i < 3)
		new->coordinates[i] = atof(vertice_info[i+1]);
	new->next = NULL;
	new->previous = NULL;
	if (context->vertices)
	{
		context->vertices->next = new;
		new->previous = context->vertices;
	}
	context->vertices = new;
	context->amount_vertices++;
	return (1);
}

push_back_faces(char **face_info)
{
	scop_t		*context = ft_get_context();
	faces_t		*new;
	vertices_t	*vertice;
	int i = 0;

	if (!(new = (faces_t *)malloc(sizeof(*new))))
		return (-1);
	new->length = 0;
	
	while (face_info[++i])
	{
		vertice = get_vertice(face_info[i]);
		new->coordinates = realloc(new->coordinates, sizeof(float*) * new->length + 3);
		new->coordinates[new->length++] = vertice->coordinates[0];
		new->coordinates[new->length++] = vertice->coordinates[1];
		new->coordinates[new->length++] = vertice->coordinates[2];
	}
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
				push_back_vertice(tab_info);
			else if (!ft_strcmp(tab_info[0], "f"))
				push_back_faces(tab_info);
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