/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:26:08 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/14 09:26:11 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n > 0)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		s++;
		n--;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
// 	const char *str = "Hello, World!";
// 	char ch = ' ';
// 	const void *result1 = memchr(str, ch, strlen(str));
// 	if (result1 != NULL) {
// 		printf("Character '%c' found at index: %ld\n", ch, 
// (const char *)result1 - str);
// 	} else {
// 		printf("Character '%c' not found.\n", ch);
// 	}
// 	const void *result2 = ft_memchr(str, ch, strlen(str));
// 	if (result2 != NULL) {
// 		printf("Character '%c' found at index: %ld\n", ch,
// (const char *)result2 - str);
// 	} else {
// 		printf("Character '%c' not found.\n", ch);
// 	}
// 	return 0;
// }
