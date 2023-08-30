/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:25:14 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/14 09:25:16 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	needle_len;

	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	if ((int) len < 0)
		len = ft_strlen(haystack);
	while (*haystack && (int)len >= needle_len)
	{
		if (ft_strncmp(haystack, needle, needle_len) == 0)
		{
			return ((char *)haystack);
		}
		haystack++;
		len--;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	const char *str = "Hello, World!";
// 	const char *needle = "Wo";
// 	char *result = ft_strnstr(str, needle, -1);
// 	char *result1 = strnstr(str, needle, -1);
// 	if (result != NULL) {
// 		printf("found at index: %ld\n", (const char *)result - str);
// 	} else {
// 		printf("Character not found.\n");
// 	}
// 	if (result1 != NULL) {
// 		printf("found at index: %ld\n", (const char *)result1 - str);
// 	} else {
// 		printf("Character not found.\n");
// 	}
// }
