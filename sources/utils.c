#include "scop.h"

scop_t *ft_get_context(void)
{
	static scop_t statique;
	return (&statique);
}

void	get_center(void)
{
	scop_t *context= ft_get_context();
	int		i = 0;

	float	min_x = INFINITY;
	float	max_x = -INFINITY;
	float	min_y = INFINITY;
	float	max_y = -INFINITY;
	float	min_z = INFINITY;
	float	max_z = -INFINITY;
	while (i+2 < context->objects[0]->amount_coordinates)
	{
		if (context->objects[0]->vertices[i] < min_x)
			min_x = context->objects[0]->vertices[i];
		else if (context->objects[0]->vertices[i] > max_x)
			max_x = context->objects[0]->vertices[i];
		i++;
		if (context->objects[0]->vertices[i] < min_y)
			min_y = context->objects[0]->vertices[i];
		else if (context->objects[0]->vertices[i] > max_y)
			max_y = context->objects[0]->vertices[i];
		i++;
		if (context->objects[0]->vertices[i] < min_z)
			min_z = context->objects[0]->vertices[i];
		else if (context->objects[0]->vertices[i] > max_z)
			max_z = context->objects[0]->vertices[i];
		i +=4;
	}
	context->objects[0]->center_vector.x = (min_x + max_x)/2;
	context->objects[0]->center_vector.y = (min_y + max_y)/2;
	context->objects[0]->center_vector.z = (min_z + max_z)/2;
}

// void	invert_w(float *inverted_matrice, float *matrice)
// {
// 	inverted_matrice[3] = -matrice[3];
// 	inverted_matrice[7] = -matrice[7];
// 	inverted_matrice[11] = -matrice[11];
// }