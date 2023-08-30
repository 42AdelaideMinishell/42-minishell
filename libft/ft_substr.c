/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:32:21 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/14 09:32:23 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	size;

	size = ft_strlen(s);
	if (size < len)
		len = size;
	res = malloc((len + 1) * sizeof(char));
	if (res != NULL)
	{
		i = 0;
		j = 0;
		while (i < size)
		{
			if (i >= start && j < len)
			{
				res[j] = s[i];
				j++;
			}
			i++;
		}
		res[j] = '\0';
	}
	return (res);
}

// #include <stdio.h>
// int main() {
// 	char const *str = "Hello, World!";
// 	char *result = ft_substr(str, 100, 1);
// 	printf("%s\n", result);
// 	printf("%zu", ft_strlen(result));
// }