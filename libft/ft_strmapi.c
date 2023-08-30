/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:32:07 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/14 09:32:09 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		size;
	char	*res;

	size = ft_strlen(s);
	res = malloc((size + 1) * sizeof(char));
	if (res != NULL)
	{
		res[size] = '\0';
		size = 0;
		while (s[size] != '\0')
		{
			res[size] = (*f)(size, s[size]);
			size++;
		}
	}
	return (res);
}
