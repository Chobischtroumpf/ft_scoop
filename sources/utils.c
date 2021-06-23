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

void	center_object(scop_t *context)
{
	float	center[3];
	int	i = -1;
	// printf("center x : %f y : %f z : %f\n", center[0], center[1], center[2]);
	get_center(center, context->amount_coordinates, context->vertices);
	while (++i < context->amount_coordinates)
		if (i%6 < 3)
			context->vertices[i] -= center[i%3];
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
	center[0] = (min_x + max_x)/2;
	center[1] = (min_y + max_y)/2;
	center[2] = (min_z + max_z)/2;
	// return (center);
}

	// float rotation = glfwGetTime() * (3.1415926535897 / 180);
	// context->rotation_matrice[0][0] = cos(rotation);
	// context->rotation_matrice[0][1] = 0;
	// context->rotation_matrice[0][2] = sin(rotation);
	// context->rotation_matrice[0][3] = 0;
	// context->rotation_matrice[1][0] = 0;
	// context->rotation_matrice[1][1] = 1;
	// context->rotation_matrice[1][2] = 0;
	// context->rotation_matrice[1][3] = 0;
	// context->rotation_matrice[2][0] = -sin(rotation);
	// context->rotation_matrice[2][1] = 0;
	// context->rotation_matrice[2][2] = cos(rotation);
	// context->rotation_matrice[2][3] = 0;
	// context->rotation_matrice[3][0] = 0;
	// context->rotation_matrice[3][1] = 0;
	// context->rotation_matrice[3][2] = 0;
	// context->rotation_matrice[3][3] = 1;

