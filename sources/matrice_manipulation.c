#include "scop.h"

void	rotate_y(scop_t *context)
{
	static float	rotation;
	float	inverted_center[16];
	reset_matrice(inverted_center);
	invert_w(inverted_center, context->center_matrice);
	int transform = glGetUniformLocation(context->shader_program, "transform");
	int	trl_to_center = glGetUniformLocation(context->shader_program, "trl_to_center");
	int	trl_from_center = glGetUniformLocation(context->shader_program, "trl_from_center");
	if (!context->rotation_speed)
		rotation = ROTATION_SPEED * glfwGetTime() *  (PI / 180);
	context->rotation_matrice[0] = cos(rotation);
	context->rotation_matrice[2] = sin(rotation);
	context->rotation_matrice[8] = -sin(rotation);
	context->rotation_matrice[10] = cos(rotation);
	glUniformMatrix4fv(transform, 1, GL_FALSE, context->rotation_matrice);
	glUniformMatrix4fv(trl_from_center, 1, GL_FALSE, context->center_matrice);
	glUniformMatrix4fv(trl_to_center, 1, GL_FALSE, inverted_center);
}

void reset_matrice(float *matrice)
{
	int i = 0;
	while (i < 16)
	{
		matrice[i] = 0;
		i++;
	}
	matrice[0] = 1;
	matrice[5] = 1;
	matrice[10] = 1;
	matrice[15] = 1;
}