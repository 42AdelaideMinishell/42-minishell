/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:27:08 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/14 09:27:11 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (c % 128))
		{
			return ((char *)s);
		}
		s++;
	}
	if ((c % 128) == 0)
		return ((char *)s);
	else
		return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
// 	const char *str = "Hello, World!";
// 	// char ch = 'H' + 256;
// 	char *result = strchr(str, 'H' + 256);
// 	if (result != NULL) {
// 		printf("Character '%c' found at index: %ld\n", 'H', result - str);
// 	} else {
// 		printf("Character '%c' not found.\n", 'H');
// 	}
// 	char *result1 = ft_strchr(str, 'H' + 256);
// 	if (result1 != NULL) {
// 		printf("Character '%c' found at index: %ld\n", 'H', result1 - str);
// 	} else {
// 		printf("Character '%c' not found.\n", 'H');
// 	}
// 	return 0;
// }
