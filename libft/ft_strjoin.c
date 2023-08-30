/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:33:29 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/14 09:33:30 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		k;

	i = ft_strlen(s1) + ft_strlen(s2);
	res = malloc((i + 1) * sizeof(char));
	if (res != NULL)
	{
		res[i] = '\0';
		k = 0;
		while (*s1)
		{
			res[k] = *s1;
			s1++;
			k++;
		}
		while (*s2)
		{
			res[k] = *s2;
			s2++;
			k++;
		}
	}
	return (res);
}

// #include <stdio.h>
// int main() {
// 	char const *str1 = "Hello, ";
// 	char const *str2 = "World!";
// 	char *result = ft_strjoin(str1, str2);
// 	printf("%s\n", result);
// }
