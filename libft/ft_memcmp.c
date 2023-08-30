/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:29:46 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/20 10:40:23 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
// 	const char *str1 = (void *)0;
// 	const char *str2 = "segfaulter tu dois";
// 	int result = memcmp(str1, str2, 17);
// 	printf("%d\n", result);
// 	int result1 = ft_memcmp(str1, str2, 17);
// 	printf("%d\n", result1);
// 	return 0;
// }
