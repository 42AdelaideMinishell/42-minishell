/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:33:41 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/20 10:07:26 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n < 0)
	{
		n = ft_strlen(s1);
		if (n < ft_strlen(s2))
			n = ft_strlen(s2);
	}
	while (n > 0)
	{
		if (*(unsigned char *)s1 != *(unsigned char *)s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		if (*(unsigned char *)s1 == '\0')
			return (0);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
// 	const char *str1 = "atoms\0\0\0\0";
// 	const char *str2 = "atoms\0abc";
// 	int result = strncmp(str1, str2, 8);
// 	printf("%d\n", result);
// 	int result1 = ft_strncmp(str1, str2, 8);
// 	printf("%d\n", result1);
// 	return 0;
// }
