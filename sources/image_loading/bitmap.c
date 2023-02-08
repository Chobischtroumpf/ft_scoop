#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "bitmap.h"

int		read_BMP_image(t_bmp_img *bmp_image, unsigned char *memory)
{
	//we need to read in 4 parts:
	//1. bitmap header
	//2. the DIB header
	//3. the color palette
	//4. the pixel data

	//1. bitmap header
	memcpy(&bmp_image->test, &memory[0], 2); //test for BM
	memcpy(&bmp_image->size, &memory[2], 4); //size of the file
	memcpy(&bmp_image->reserved, &memory[6], 4);	 //reserved
	memcpy(&bmp_image->offset, &memory[10], 4); //offset to the pixel array

	//2. DIB header BITMAPINFOHEADER
	memcpy(&bmp_image->dibSize, &memory[14], 4); //size of the DIB header
	if (bmp_image->dibSize != 40)
	{
		printf("Error: DIB header size is %d, should be 40, exiting.\n", bmp_image->dibSize);
		return (0);
	}
	memcpy(&bmp_image->pixel_width,				&memory[18], 4); //width of the image
	memcpy(&bmp_image->pixel_height,			&memory[22], 4);
	memcpy(&bmp_image->num_color_panes,			&memory[26], 2);
	memcpy(&bmp_image->color_depth,				&memory[28], 2);
	memcpy(&bmp_image->compression_method,		&memory[30], 4);
	memcpy(&bmp_image->image_size,				&memory[34], 4);
	memcpy(&bmp_image->x_resolution,			&memory[38], 4);
	memcpy(&bmp_image->y_resolution,			&memory[42], 4);
	memcpy(&bmp_image->num_colors,				&memory[46], 4);
	memcpy(&bmp_image->num_important_colors,	&memory[50], 4);

	if (bmp_image->compression_method != 0)
	{
		printf("Error: Compression method %d not supported, exiting.\n", bmp_image->compression_method);
		return (0);
	}

	//3. color palette
	if (bmp_image->num_colors != 0)
	{
		fprintf(stderr, "Error: Color palette detected and not supported, exiting.\n");
		return (0);
	}

	if (bmp_image->color_depth != 24)
	{
		fprintf(stderr, "Error: Color depth %d not supported, exiting.\n", bmp_image->color_depth);
		return (0);
	}

	//load the pixel data
	bmp_image->row_size = ( ( (bmp_image->color_depth * bmp_image->pixel_width) + 31) / 32) * 4; 
	bmp_image->array_size = bmp_image->pixel_width * bmp_image->pixel_height; //size of pixel image without padding

	bmp_image->pixels = (t_pixel *)malloc(bmp_image->array_size * sizeof(t_pixel));
	if (bmp_image->pixels == NULL)
	{
		printf("Error: Could not allocate memory for pixel array, exiting.\n");
		return (0);
	}

	int index = 0;
	for (int i=0; i < bmp_image->pixel_height; i++)
	{
		//we load the raw data into memory with full padded size
		unsigned char *rawdata = (unsigned char*)malloc(bmp_image->row_size * sizeof(unsigned char));
		//we add offset to number of rows we have looped over
		memcpy(rawdata, &memory[bmp_image->offset + i * bmp_image->row_size], bmp_image->row_size);
		//we load the raw data into the pixel array
		for (int j=0; j < bmp_image->pixel_width*3; j+=3)
		{
			bmp_image->pixels[index].r = rawdata[j + 2];
			bmp_image->pixels[index].g = rawdata[j + 1];
			bmp_image->pixels[index].b = rawdata[j + 0];
			index++;
		}

		free(rawdata);
	}

	return (1);

}

t_bmp_img	*load_BMP(char *file)
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
	t_bmp_img *img = (t_bmp_img *)malloc(fsize * sizeof(t_bmp_img));
	if (img == NULL)
	{
		free(buffer);
		printf("Error: Could not allocate memory for image %s, exiting.\n", file);
		return NULL;
	}

	// read the image
	if (read_BMP_image(img, buffer) == 0)
	{
		free(buffer);
		free(img);
		printf("Error: Could not load image %s, exiting.\n", file);
		return NULL;
	}
}

void unload_BMP(t_bmp_img *img)
{
	free(img->pixels);
	free(img);
}
