#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "ppm_img.h"

void	rotate_image(t_ppm_img *img)
{
	t_pixel *new_pixels = (t_pixel *)malloc(img->width * img->height * sizeof(t_pixel) + 1 * sizeof(t_pixel));
	ft_bzero(new_pixels, img->width * img->height * sizeof(t_pixel) + 1 * sizeof(t_pixel));
	if (new_pixels == NULL)
	{
		printf("Error: Could not allocate memory for image pixels, exiting.\n");
		return;
	}
	int i = 0;
	int j = 0;
	while (i < img->width * img->height)
	{
		new_pixels[i].r = img->pixels[j].r;
		new_pixels[i].g = img->pixels[j].g;
		new_pixels[i].b = img->pixels[j].b;
		i++;
		j++;
	}
	free(img->pixels);
	img->pixels = new_pixels;
}

int read_PPM_image(t_ppm_img *img, unsigned char *buffer)
{
	// read the file type
	memcpy(&img->file_type[0], &buffer[0], 2);

	if (img->file_type[0] != 'P' || (img->file_type[1] != '6' && img->file_type[1] != '3'))
	{
		printf("Error: File is not a PPM image, exiting.\n");
		return 0;
	}

	// read the width
	int i = 3;
	while (ft_isspace(buffer[i]))
		i++;
	img->width = ft_atoi(&buffer[i]);
	// read the height
	while (ft_isdigit(buffer[i]))
		i++;
	while (ft_isspace(buffer[i]))
		i++;
	img->height = ft_atoi(&buffer[i]);
	// read the max color
	while (ft_isdigit(buffer[i]))
		i++;
	while (ft_isspace(buffer[i]))
		i++;
	img->max_color = ft_atoi(&buffer[i]);
	// read the pixels
	while (ft_isdigit(buffer[i]))
		i++;
	while (ft_isspace(buffer[i]))
		i++;
	
	img->pixels = (t_pixel *)malloc(img->width * img->height * sizeof(t_pixel) + 1 * sizeof(t_pixel));
	ft_bzero(img->pixels, img->width * img->height * sizeof(t_pixel));
	if (img->pixels == NULL)
	{
		printf("Error: Could not allocate memory for image pixels, exiting.\n");
		return 0;
	}

	int j = 0;
	while (j < img->width * img->height)
	{
		img->pixels[j].r = buffer[i];
		img->pixels[j].g = buffer[i + 1];
		img->pixels[j].b = buffer[i + 2];
		i += 3;
		j++;
	}
	return 1;
}

t_ppm_img	*load_PPM(char *file)
{
	// open the file
	FILE * fd_size = fopen(file, "r");
	if (fd_size == NULL) 
	{
		printf("Error: Could not open file %s, exiting.\n", file);
		return NULL;
	}
	fseek(fd_size, 0L, SEEK_END);
    long fsize = ftell(fd_size);
	fclose(fd_size); // close the file
	FILE * fd = fopen (file, "r");
	if (fd_size == NULL) 
	{
		printf("Error: Could not open file %s, exiting.\n", file);
		return NULL;
	}

	unsigned char *buffer = malloc(fsize * sizeof(unsigned char)); // allocate memory for the whole file
	fread(buffer, 1, fsize, fd); // read the whole file into the buffer
	fclose(fd); // close the file

	// now we have the whole file in memory, we can start reading it
	t_ppm_img *img = (t_ppm_img *)malloc(fsize * sizeof(t_ppm_img));
	if (img == NULL)
	{
		free(buffer);
		printf("Error: Could not allocate memory for image %s, exiting.\n", file);
		return NULL;
	}

	// read the image
	if (read_PPM_image(img, buffer) == 0)
	{
		free(buffer);
		free(img);
		printf("Error: Could not load image %s, exiting.\n", file);
		return NULL;
	}
	else	
	{
		printf("Image %s loaded successfully.\n", file);
		printf("Image size: %d x %d\n", img->width, img->height);
		printf("Image max color: %d\n", img->max_color);
		free(buffer);
	}
	invert_image(img);
	return img;
}

void unload_PPM(t_ppm_img *img)
{
	free(img->pixels);
	// printf("Image unloaded successfully.\n");
	free(img);
	printf("Image structure freed successfully.\n");
}
