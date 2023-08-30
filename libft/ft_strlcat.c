/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:24:55 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/14 09:24:59 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	j = 0;
	while (src[j] && i + j < dstsize - 1)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i + j <= dstsize - 1)
		dst[i + j] = '\0';
	while (src[j])
		j++;
	return (i + j);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
// 	char destination1[30] = "BBBB";
// 	const char *source = "AAAAAAAAA";
// 	size_t result1 = ft_strlcat(destination1, source, 3);
// 	printf("Concatenated string: %s\n", destination1);
// 	printf("Return value: %zu\n", result1);
// 	char destination2[30] = "BBBB";
// 	size_t result2 = strlcat(destination2, source, 3);
// 	printf("Concatenated string: %s\n", destination2);
// 	printf("Return value: %zu\n", result2);
// 	return 0;
// }
