#include "scop.h"

scop_t *ft_get_context(void)
{
	static scop_t statique;
	return (&statique);
}

int normalizing_coordinates(scop_t *context)
{
	int	max = 0;
	int		i = -1;

	while (++i < context->amount_coordinates)
		if (i%6 < 3 && (int)fabs(context->vertices[i]) > max)
			max = context->vertices[i];
	if (max >= 1)
	{
		max += 1;
		i = 0;
		while (i < context->amount_coordinates)
		{
			if (i%6 < 3)
				context->vertices[i] /= 2;
			i++;
		}
		return(normalizing_coordinates(context));
	}
	else
		return(0);
}

void	get_center(float *center, int amount_coordinates, float *vertices)
{
	int		i = 0;
	float	min_x = INFINITY;
	float	max_x = -INFINITY;
	float	min_y = INFINITY;
	float	max_y = -INFINITY;
	float	min_z = INFINITY;
	float	max_z = -INFINITY;
	while (i+2 < amount_coordinates)
	{
		if (vertices[i] < min_x)
			min_x = vertices[i];
		else if (vertices[i] > max_x)
			max_x = vertices[i];
		i++;
		if (vertices[i] < min_y)
			min_y = vertices[i];
		else if (vertices[i] > max_y)
			max_y = vertices[i];
		i++;
		if (vertices[i] < min_z)
			min_z = vertices[i];
		else if (vertices[i] > max_z)
			max_z = vertices[i];
		i +=4;
	}
	center[3] = (min_x + max_x)/2;
	center[7] = (min_y + max_y)/2;
	center[11] = (min_z + max_z)/2;
}

void	invert_w(float *inverted_matrice, float *matrice)
{
	inverted_matrice[3] = -matrice[3];
	inverted_matrice[7] = -matrice[7];
	inverted_matrice[11] = -matrice[11];
}