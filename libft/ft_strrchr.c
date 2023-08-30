/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:28:45 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/14 09:28:49 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;

	res = NULL;
	while (*s)
	{
		if (*s == (c % 128))
		{
			res = (char *)s;
		}
		s++;
	}
	if ((c % 128) == 0)
		return ((char *)s);
	else
		return (res);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
// 	const char *str = "Hello, World!";
// 	char ch = '\0';
// 	char *result = strrchr(str, ch);
// 	if (result != NULL) {
// 		printf("Character '%c' found at index: %ld\n", ch, result - str);
// 	} else {
// 		printf("Character '%c' not found.\n", ch);
// 	}
// 	char *result1 = ft_strrchr(str, ch);
// 	if (result1 != NULL) {
// 		printf("Character '%c' found at index: %ld\n", ch, result1 - str);
// 	} else {
// 		printf("Character '%c' not found.\n", ch);
// 	}
// 	return 0;
// }
