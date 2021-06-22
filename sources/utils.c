#include "scop.h"

scop_t *ft_get_context(void)
{
	static scop_t statique;
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
	float rotation = context->rotation_speed * glfwGetTime() *  (3.14159265 / 180);
	int transform = glGetUniformLocation(context->shader_program, "transform");
	context->rotation_matrice[0] = cos(rotation);
	context->rotation_matrice[2] = sin(rotation);
	context->rotation_matrice[5] = 1;
	context->rotation_matrice[8] = -sin(rotation);
	context->rotation_matrice[10] = cos(rotation);
	context->rotation_matrice[15] = 1;
	glUniformMatrix4fv(transform, 1, GL_FALSE, context->rotation_matrice);
}

void reset_matrice(scop_t *context)
{
	int i = 0;
	while (i < 16)
	{
		context->rotation_matrice[i] = 0;
		i++;
	}
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

