/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:23:42 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/14 09:23:45 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(char const *s, char c)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i] != '\0' && s[i + 1] == c)
			|| (s[i] != c && s[i] != '\0' && s[i + 1] == '\0'))
			size++;
		i++;
	}
	return (size);
}

static void	copy(char const *s, char c, char **res)
{
	int	i;
	int	size;

	size = 0;
	while (*s)
	{
		i = 0;
		while ((s[i] != c) && (s[i] != '\0'))
			i++;
		res[size] = malloc((i + 1) * sizeof(char));
		if (res[size] != NULL)
		{
			res[size][i] = '\0';
			ft_memcpy(res[size], s, i);
			while ((*s != c) && (*s != '\0'))
				s++;
			while (*s == c && c != '\0')
				s++;
			size++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		size;

	if (!*s)
	{
		res = malloc((1) * sizeof(char *));
		res[0] = NULL;
		return (res);
	}
	while (*s == c)
		s++;
	size = get_size(s, c);
	res = malloc((size + 1) * sizeof(char *));
	if (res != NULL)
	{
		res[size] = NULL;
		copy(s, c, res);
	}
	return (res);
}

// #include <stdio.h>
// int main() {
// 	char const *str = "\0";
// 	char **result = ft_split(str, 0);
// 	int i = 0;
// 	while(result[i] != NULL)
// 	{
// 		printf("%s\n", result[i]);
// 		i++;
// 	}
// 	printf("%s\n", result[0]);
// 	free(result);
// }