/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:33:03 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/20 11:02:32 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		i = (int)len - 1;
		while (i >= 0)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < (int)len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
//     char str1[20] = "Hello, World!";
//     memmove(str1 - 3, str1, strlen(str1) + 1);
//     printf("After memmove: %s\n", str1);
// 				char str2[20] = "Hello, World!";
//     ft_memmove(str2 - 3, str2, strlen(str2) + 1);
//     printf("After memmove: %s\n", str2);
//     return 0;
// }
