/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:31:04 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/14 09:31:08 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	while (n > 0)
	{
		((unsigned char *)s)[n - 1] = 0;
		n--;
	}
}

// #include <stdio.h>
// #include <strings.h>
// int main() {
// 	char str1[20];
// 	char str2[20];
// 	ft_bzero(str1, sizeof(str1));
// 	bzero(str2, sizeof(str2));
// 	printf("After bzero: %s\n", str1);
// 	printf("After bzero: %s\n", str2);
// 	return 0;
// }
