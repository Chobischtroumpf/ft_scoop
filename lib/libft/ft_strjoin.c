/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 09:32:08 by adorigo           #+#    #+#             */
/*   Updated: 2020/04/12 21:18:26 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*dest;

	if (s1 && s2)
	{
		if (!(dest = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1)))
			return (NULL);
		ft_strcpy(dest, s1);
		ft_strcat(dest, s2);
		return (dest);
	}
	else
		return (NULL);
}
