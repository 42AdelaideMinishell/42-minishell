/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:28:23 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/14 09:28:26 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize == 0)
	{
		return (ft_strlen(src));
	}
	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
// 	char destination1[10];
// 	char destination2[10];
// 	const char *source = "Hello, World!";
// 	size_t result1 = ft_strlcpy(destination1, source, 0);
// 	printf("Copied string: %s\n", destination1);
// 	printf("Return value: %zu\n", result1);
// 	size_t result2 = strlcpy(destination2, source, 0);
// 	printf("Copied string: %s\n", destination2);
// 	printf("Return value: %zu\n", result2);
// 	return 0;
// }
