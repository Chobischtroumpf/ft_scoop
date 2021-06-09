#include "scop.h"

scop_t *ft_get_context(void)
{
	static scop_t statique;
 
	return (&statique);
}

void	rewind_vertices(vertices_t **vertices)
{
	while(*vertices && (*vertices)->previous)
		*vertices = (*vertices)->previous;
}

vertices_t	*new_vertice(void)
{
	vertices_t	*new;

	new = (vertices_t *)malloc(sizeof(new));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->previous = NULL;
	new->coordinates[0] = 0;
	new->coordinates[1] = 0;
	new->coordinates[2] = 0;
	return (new);
}