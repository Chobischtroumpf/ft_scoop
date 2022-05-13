#include "scop.h"

void	rotate_y(scop_t *context)
{
	static float	rotation;
	t_mat4	inverted_center = m4_init();
	int transform = glGetUniformLocation(context->shader_program, "transform");
	int	trl_to_center = glGetUniformLocation(context->shader_program, "trl_to_center");
	int	trl_from_center = glGetUniformLocation(context->shader_program, "trl_from_center");
	if (!context->rotation_speed)
		rotation = ROTATION_SPEED * glfwGetTime() *  (PI / 180);
	
	// printf("\n\n");
	// int i = -1;
	// int j = -1;
	// while (++i < 4){
	// 	j = -1;
	// 	while(++j < 4)
	// 		printf("inverted_matrice[%d][%d] : %f\n", i, j, context->center_matrice.value[i][j]);
	// }
	// i = 0;
	// j = 0;
	// while (++i < 4){
	// 	j = -1;
	// 	while(++j < 4)
	// 		printf("inverted_matrice[%d][%d] : %f\n", i, j, inverted_center.value[i][j]);
	// }
	glUniformMatrix4fv(transform, 1, GL_FALSE, (float *)context->rotation_matrice.value);
	glUniformMatrix4fv(trl_from_center, 1, GL_FALSE, (float *)context->center_matrice.value);
	glUniformMatrix4fv(trl_to_center, 1, GL_FALSE, (float *)inverted_center.value);
}

void	reset_matrice(void)
{
	scop_t *context = ft_get_context();
	int i = -1;
	while (++i < 4)
	{
		int j = -1;
		while (++j < 4){
			context->center_matrice.value[i][j] = 0;
		}
	}
	context->center_matrice.value[0][0] = 1;
	context->center_matrice.value[1][1] = 1;
	context->center_matrice.value[2][2] = 1;
	context->center_matrice.value[3][3] = 1;
}

int	normalize_vertexes()
{
	scop_t *context = ft_get_context();
	int i = 0;
	t_vertex *vertex;
	float furthest_point = 0;
	float current_point = 0;
	while (i < context->amount_coordinates)
	{
		if (!(vertex = (t_vertex *)malloc(sizeof(t_vertex))))
			return (-1);
		vertex->x = context->vertices[i];
		vertex->y = context->vertices[i+1];
		vertex->z = context->vertices[i+2];
		current_point = sqrt(vertex->x*vertex->x + vertex->y*vertex->y + vertex->z*vertex->z);
		if (current_point > furthest_point)
			furthest_point = current_point;
		free(vertex);	
		i+=3;
	}
	float normalising_factor = 1 / furthest_point;
	i = 0;
	while(i < context->amount_coordinates){
		context->vertices[i] *= normalising_factor;
		context->vertices[i+1] *= normalising_factor;
		context->vertices[i+2] *= normalising_factor;
		i+= 3;
	}
	return (0);
}