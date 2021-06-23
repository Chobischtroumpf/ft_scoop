#include "scop.h"

void	rotate_y(scop_t *context)
{
	static float rotation;
	int transform = glGetUniformLocation(context->shader_program, "transform");
	if (!context->rotation_speed)
		rotation = ROTATION_SPEED * glfwGetTime() *  (PI / 180);
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