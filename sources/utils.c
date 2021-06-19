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