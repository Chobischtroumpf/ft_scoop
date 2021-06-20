#include "scop.h"

scop_t *ft_get_context(void)
{
	static scop_t statique;
	// printf("%p|%p|%p|%p|%p|%p\n", statique.primary, statique.)
	return (&statique);
}

void normalizing_coordinates(scop_t *context)
{
	int	max = 0;
	int		i = -1;

	while (++i < context->amount_coordinates)
		if ((int)context->vertices[i] > max)
			max = context->vertices[i];
	if (max >= 1)
	{
		max += 1;
		i = 0;
		while (i < context->amount_coordinates)
		{
			context->vertices[i] /= max;
			i++;
		}
	}
}

void	center_object(scop_t *context)
{
	int		i = 0;
	float	min_x = context->vertices[0];
	float	max_x = context->vertices[0];
	float	min_y = context->vertices[1];
	float	max_y = context->vertices[1];
	float	min_z = context->vertices[2];
	float	max_z = context->vertices[2];
	float	center[3];

	while (i < context->amount_coordinates && i+1 < context->amount_coordinates && i+2 < context->amount_coordinates)
	{
		if (context->vertices[i] < min_x)
			min_x = context->vertices[i];
		else if (context->vertices[i] > max_x)
			max_x = context->vertices[i];
		i++;
		if (context->vertices[i] < min_y)
			min_y = context->vertices[i];
		else if (context->vertices[i] > max_y)
			max_y = context->vertices[i];
		i++;
		if (context->vertices[i] < min_z)
			min_z = context->vertices[i];
		else if (context->vertices[i] > max_z)
			max_z = context->vertices[i];
		i++;
	}
	center[0] = (min_x + max_x)/2;
	center[1] = (min_y + max_y)/2;
	center[2] = (min_z + max_z)/2;
	i = -1;
	while (++i < context->amount_coordinates)
		context->vertices[i] -= center[i%3];
}

void	rotate_y(scop_t *context)
{
	int i = 0;
	while (i < context->amount_coordinates)
	{
		context->vertices[i] = cos(ROTATION_SPEED) * context->vertices[i] + sin(ROTATION_SPEED) * context->vertices[i+2];
		context->vertices[i+2] = -(sin(ROTATION_SPEED) * context->vertices[i]) + (cos(ROTATION_SPEED) * context->vertices[i+2]);
		i += 3;
	}
}