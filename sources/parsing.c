#include "scop.h"

int	add_vertex(char **vertices_info, object_t *object)
{

	if (!(object->vertices = realloc(object->vertices, sizeof(float) * (object->amount_coordinates + 6))))
		return (-1);
	object->vertices[object->amount_coordinates] = atof(vertices_info[1]);
	object->vertices[object->amount_coordinates + 1] = atof(vertices_info[2]);
	object->vertices[object->amount_coordinates + 2] = atof(vertices_info[3]);
	object->amount_coordinates += 3;
	int value = rand() % 10;
	int i = 0;
	while (i < 3)
	{
		object->vertices[i + object->amount_coordinates] = 0.1f * value;
		i++;
	}
	object->amount_coordinates += 3;
	return (0);
}

int	add_faces(char **face_info, object_t *object)
{
	int i = -1;
	int size = 0;

	while (face_info[size+1])
		size++;
	if (size == 4)
		size = 6;
	if (!(object->faces = realloc(object->faces, sizeof(GLuint) * (object->amount_faces + size))))
		return (-1);
	if (size != 6)
		while (++i < size)
			object->faces[i + object->amount_faces] = atoi(face_info[i+1]) -1;
	else
	{
		while (++i < 3)
			object->faces[i + object->amount_faces] = atoi(face_info[i+1]) - 1;
		object->faces[i++ + object->amount_faces] = atoi(face_info[1]) - 1;
		object->faces[i++ + object->amount_faces] = atoi(face_info[3]) - 1;
		object->faces[i + object->amount_faces] = atoi(face_info[4]) - 1;
	}
	object->amount_faces += size;
	return (0);
}

int	parse_files(scop_t *context)
{
	int		fd;
	int		i;
	char	*line;
	char	**tab_info;

	for (int j = 0; j < context->amount_objects; j++)
	{
		if (!ft_strlast(context->obj[j], ".obj"))
			return(-1);
		fd = open(context->obj[j], O_RDONLY);
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
						if (add_vertex(tab_info, (context->objects[j])) < 0)
							return (-1);
				}
				else if (!ft_strcmp(tab_info[0], "f"))
				{
					if (add_faces(tab_info, context->objects[j]) < 0)
						return (-1);
				}
				for (i = 0; i < 4; i++)
					free(tab_info[i]);
				free(tab_info);
				free(line);
			}
		}
		close(fd);
		i = 0;
		// for (; i < context->amount_coordinates; i++)
		// {
		// 	printf("%f\n", context->vertices[i]);
		// 	if (i %3 == 0)
		// 		printf("\n");
		// }
		// center_object(context);
		if (normalize_vertexes() < 0)
			return (-1);
		get_center();
	}	
	return (1);
}