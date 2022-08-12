#include "scop.h"

char *get_vertex_shader(void)
{
	char buffer[101];
	char *source = NULL;
	char *tmp;
	char *path = ft_strjoin(OBJECT_PATH, "vertex_shader.vsh");
	int fd = open(path, O_RDONLY);
	int ret;
	if (fd < 0 || path == NULL)
		return (NULL);
	free(path);
	while ((ret = read(fd, buffer, 100)) > 0)
	{
		buffer[ret] = '\0';
		if (!source)
			source = ft_strdup(buffer);
		else 
		{
			tmp = source;
			if (!(source = ft_strjoin(tmp, buffer)))
				return (NULL);
			free(tmp);
		}
	}
	return (source);
}

char *get_fragment_shader(void)
{
	char buffer[101];
	char *source = NULL;
	char *tmp;
	char *path = ft_strjoin(OBJECT_PATH, "fragment_shader.fsh");
	int fd = open(path, O_RDONLY);
	int ret;
	free(path);
	if (fd < 0)
		return (NULL);
	while ((ret = read(fd, buffer, 100)) > 0)
	{
		buffer[ret] = '\0';
		if (!source)
			source = ft_strdup(buffer);
		else 
		{
			tmp = source;
			if (!(source = ft_strjoin(tmp, buffer)))
				return (NULL);
			free(tmp);
		}
	}
	return (source);
}