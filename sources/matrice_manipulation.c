#include "scop.h"

void	rotate_y(scop_t *context)
{
	// static float	rotation;
	// t_mat4	inverted_center = m4_init();
	int transform = glGetUniformLocation(context->shader_program, "transform");
	int	translation = glGetUniformLocation(context->shader_program, "translation");
	// int	trl_from_center = glGetUniformLocation(context->shader_program, "trl_from_center");
	context->translation_matrice = m4_translate(context->translation_vector.x, context->translation_vector.y, context->translation_vector.z);
	context->rotation_matrice = m4_rotation_around_center(context->center_vector, 0, context->rotation_vector.y, 0);
	glUniformMatrix4fv(transform, 1, GL_FALSE, (float *)context->rotation_matrice.value);
	// glUniformMatrix4fv(trl_from_center, 1, GL_FALSE, (float *)context->center_matrice.value);
	// glUniformMatrix4fv(trl_to_center, 1, GL_FALSE, (float *)inverted_center.value);
	glUniformMatrix4fv(translation, 1, GL_FALSE, (float *)context->translation_matrice.value);
}

int	normalize_vertexes()
{
	scop_t *context = ft_get_context();
	int i = 0;
	t_vec3f *vertex;
	float furthest_point = 0;
	float current_point = 0;
	while (i < context->amount_coordinates)
	{
		if (!(vertex = (t_vec3f *)malloc(sizeof(t_vec3f))))
			return (-1);
		vertex->x = context->vertices[i];
		vertex->y = context->vertices[i+1];
		vertex->z = context->vertices[i+2];
		current_point =	vec_length(vertex);
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