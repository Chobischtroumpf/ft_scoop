#ifndef BITMAP_H
# define BITMAP_H

# include <stdio.h>

typedef struct		s_bmp_pixel
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_pixel;

typedef struct		s_bmp_img
{
	// file header
	unsigned char		test[2];
	unsigned int		size;
	unsigned int		reserved;
	unsigned int		offset;

	//DIB header
	unsigned int		dibSize;
	unsigned int		pixel_width;
	unsigned int		pixel_height;
	unsigned short		num_color_panes;
	unsigned short		color_depth;
	unsigned int		compression_method;
	unsigned int		image_size;
	int 				x_resolution;
	int 				y_resolution;
	unsigned int		num_colors;
	unsigned int		num_important_colors;
	
	// pixel info
	unsigned int		row_size;
	unsigned int		array_size;
	t_pixel				*pixels;
}						t_bmp_img;

t_bmp_img				*load_BMP(char *file);

void					unload_BMP(t_bmp_img *img);

#endif