#ifndef BITMAP_H
# define BITMAP_H

# include <stdio.h>
# include "libft.h"

typedef struct		s_bmp_pixel
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_pixel;

typedef struct		s_ppm_img
{
	// file header
	unsigned char	file_type[2];
	unsigned int	width;
	unsigned int	height;
	unsigned int	max_color;
		
	t_pixel				*pixels;
}						t_ppm_img;

t_ppm_img				*load_PPM(const char *file);
void					unload_PPM(t_ppm_img *img);

#endif