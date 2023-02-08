#include "xpm_loader.h"

void	ft_lstadd_back(t_color **alst, t_color *new)
{
	t_list	*ptr;

	if (!alst)
		return ;
	if (!*alst)
		*alst = new;
	else if (alst && *alst)
	{
		ptr = *alst;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

char *retrieve_file(char *path)
{
	int		fd;
	char	*line;
	char	*file;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (NULL);
	file = ft_strnew(0);
	while (get_next_line(fd, &line) > 0)
	{
		file = ft_strjoin(file, line);
		file = ft_strjoin(file, "\n");
		free(line);
	}
	close(fd);
	return (file);
}

t_xpm *xpm_loader(char *path)
{
	t_xpm	*image;
	char	*file;
	char	**lines;
	int		i;

	if (!(image = (t_xpm *)malloc(sizeof(t_xpm))))
		return (NULL);
	if (!(file = retrieve_file(path)))
		return (NULL);
	lines = ft_split(file, '\n');
	// first we retrieve the amount of colors, how many chars represent one color and the dimensions of the image
	char *line = ft_strtrim(lines[3], "\",");
	printf("line: %s\n", line);
	char **line_info = ft_split(line, ' ');
	free(line);
	image->width = ft_atoi(line_info[0]);
	image->height = ft_atoi(line_info[1]);
	image->colors = ft_atoi(line_info[2]);
	image->chars = ft_atoi(line_info[3]);
	printf("width: %d\n", image->width);
	printf("height: %d\n", image->height);
	printf("colors: %d\n", image->colors);
	printf("chars: %d\n", image->chars);
	while (*line_info)
		free(*line_info++);

	// then we retrieve the colors
	image->color_data = NULL;
	i = 0;
	while (i < image->colors)
	{
		t_color *color = (t_color *)malloc(sizeof(t_color));
		char *tmp = ft_strtrim(lines[4 + i], "\",");
		free(line);
		line = tmp;
		printf("line: %s\n", line);
		char **color_info = ft_split(line, ' ');
		color->name = ft_strndup(line, image->chars);
		free(line);
		color->color = ft_atoi_base(color_info[1], 16);

	}

	// then we retrieve the image data
	image->data = (char **)malloc(sizeof(char *) * image->height);
	i = 0;
	while (i < image->height)
	{
		line = ft_strtrim(lines[4 + image->colors + i], "\",");
		printf("line: %s\n", line);
		image->data[i] = ft_strdup(line);
		printf("data: %s\n", image->data[i]);
		i++;
	}
}


int main()
{
	printf("xpm_loader\n");
	xpm_loader("test.xpm");
	printf("done\n");
}