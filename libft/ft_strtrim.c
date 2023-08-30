/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:30:48 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/14 09:30:50 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		i;
	int		j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while (s1[j] && ft_strrchr(set, s1[j]) != NULL)
		j++;
	while (i > j && ft_strrchr(set, s1[i]) != NULL)
		i--;
	res = malloc((i - j + 2) * sizeof(char));
	if (res != NULL)
	{
		res[i - j + 1] = '\0';
		while (j <= i)
		{
			res[i - j] = s1[i];
			i--;
		}
	}
	return (res);
}

// #include <stdio.h>
// #include <string.h>

// int main() {
// 	char const *str = "";
// 	char const *set = "123";
// 	char *result = ft_strtrim(str, set);
// 	printf("%d\n", strcmp(result, ""));
// 	printf("%zu\n", ft_strlen(str));
// }
