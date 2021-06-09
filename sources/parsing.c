#include "scop.h"

int	parse_file(scop_t *context)
{
	int	fd;
	char *line;
	char **tab_info;

	fd = open(context->obj, O_RDONLY);
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

			}
			else if (!ft_strcmp(tab_info[0], "f"))
			{
				
			}
		}
	}
}