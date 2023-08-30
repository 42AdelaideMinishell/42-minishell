/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:32:33 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/20 09:48:36 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	size_t	total_size;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	total_size = count * size;
	res = (void *)malloc(total_size);
	if (res != NULL)
		ft_bzero(res, total_size);
	return (res);
}

// #include <stdio.h>
// #include <limits.h>
// int main() {
// 	int num_elements = 2;
// 	int *array = (int *)calloc(3, -5);
// 	if (array != NULL) {
// 		for (int i = 0; i < num_elements; i++) {
// 			printf("array[%d] = %d\n", i, array[i]);
// 		}
// 		free(array);
// 	} else {
// 		printf("Memory allocation failed.\n");
// 	}
// 	int *array1 = (int *)ft_calloc(3, -5);
// 	if (array1 != NULL) {
// 		for (int i = 0; i < num_elements; i++) {
// 			printf("array[%d] = %d\n", i, array1[i]);
// 		}
// 		free(array1);
// 	} else {
// 		printf("Memory allocation failed.\n");
// 	}
// 	return 0;
// }
