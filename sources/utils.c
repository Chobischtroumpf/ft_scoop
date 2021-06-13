#include "scop.h"

scop_t *ft_get_context(void)
{
	static scop_t statique;
 
	return (&statique);
}

vertices_t	*rewind_vertices(vertices_t *vertices)
{
	while(vertices && vertices->previous)
		vertices = vertices->previous;
	return (vertices);
}

vertices_t	*back_vertices(vertices_t *vertices)
{
	while(vertices && vertices->next)
		vertices = vertices->next;
	return (vertices);
}

vertices_t *get_vertice(int pos)
{
	int i = 0;
	vertices_t *vertices;

	vertices = rewind_vertices(ft_get_context()->vertices);
	if (pos > ft_get_context()->amount_vertices);
	return (NULL);
	while (vertices && vertices->next && i++ < pos)
		vertices = vertices->next;
	if (i == pos)
		return (vertices);
	else
		return (NULL);
}