/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:31:30 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/20 10:50:57 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
	{
		return (NULL);
	}
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
// 	const char *source = "Hello, World!";
// 	char destination1[20];
// 	char destination2[20];
// 	ft_memcpy(destination1, source, strlen(source) + 1);
// 	memcpy(destination2, source, strlen(source) + 1);
// 	printf("Copied string: %s\n", destination1);
// 	printf("Copied string: %s\n", destination2);
// 	return 0;
// }
