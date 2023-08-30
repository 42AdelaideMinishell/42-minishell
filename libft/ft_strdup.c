/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:30:19 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/14 09:30:22 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		size;
	char	*res;

	size = ft_strlen(s1);
	res = malloc((size + 1) * sizeof(char));
	if (res != NULL)
	{
		res[size] = '\0';
		while (size > 0)
		{
			res[size - 1] = s1[size - 1];
			size--;
		}
	}
	return (res);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
// 	const char *original_str = "Hello, World!";
// 	char *duplicate_str = strdup(original_str);
// 	if (duplicate_str != NULL) {
// 		printf("Original string: %s\n", original_str);
// 		printf("Duplicate string: %s\n", duplicate_str);
// 		free(duplicate_str);
// 	} else {
// 		printf("Memory allocation failed.\n");
// 	}
// 	char *duplicate_str1 = ft_strdup(original_str);
// 	if (duplicate_str1 != NULL) {
// 		printf("Original string: %s\n", original_str);
// 		printf("Duplicate string: %s\n", duplicate_str1);
// 		free(duplicate_str1);
// 	} else {
// 		printf("Memory allocation failed.\n");
// 	}
// 	return 0;
// }
