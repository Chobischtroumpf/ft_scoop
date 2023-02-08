#pragma once

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

typedef struct s_color
{
	char	*name;
	int		color;
	struct s_color *next;
}				t_color;

typedef struct s_xpm
{
	int			width;
	int			height;
	int			colors;
	int			chars;
	t_color		*color_data;
	char		**data;
}				t_xpm;

t_xpm	*xpm_loader(char *path);
