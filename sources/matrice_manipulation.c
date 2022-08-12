#include "scop.h"

void	rotate_y(scop_t *context)
{
	for (int i = 0; i < context->amount_objects; i++)
	{
		int transform = glGetUniformLocation(context->shader_program, "transform");
		int	translation = glGetUniformLocation(context->shader_program, "translation");
		context->objects[i]->translation_matrice = m4_translate(context->objects[i]->translation_vector.x,
			context->objects[i]->translation_vector.y, context->objects[i]->translation_vector.z);
		context->objects[i]->rotation_matrice = m4_rotation_around_center(context->objects[i]->center_vector,
			0, context->objects[i]->rotation_vector.y, i);
		glUniformMatrix4fv(transform, 1, GL_FALSE,
			(float *)context->objects[i]->rotation_matrice.value);
		glUniformMatrix4fv(translation, 1, GL_FALSE,
			(float *)context->objects[i]->translation_matrice.value);
		m4_print(context->objects[i]->rotation_matrice);
		m4_print(context->objects[i]->translation_matrice);
	}
}

int	normalize_vertexes()
{
	scop_t *context = ft_get_context();
	for (int j = 0; j < context->amount_objects; j++)
	{
		int i = 0;
		t_vec3f *vertex;
		float furthest_point = 0;
		float current_point = 0;
		while (i < context->objects[j]->amount_coordinates)
		{
			if (!(vertex = (t_vec3f *)malloc(sizeof(t_vec3f))))
				return (-1);
			vertex->x = context->objects[j]->vertices[i];
			vertex->y = context->objects[j]->vertices[i+1];
			vertex->z = context->objects[j]->vertices[i+2];
			current_point =	vec_length(vertex);
			if (current_point > furthest_point)
				furthest_point = current_point;
			free(vertex);	
			i+=3;
		}
		float normalising_factor = 1 / furthest_point;
		i = 0;
		while(i < context->objects[j]->amount_coordinates){
			context->objects[j]->vertices[i] *= normalising_factor;
			context->objects[j]->vertices[i+1] *= normalising_factor;
			context->objects[j]->vertices[i+2] *= normalising_factor;
			i+= 3;
		}
	}
	return (0);
}