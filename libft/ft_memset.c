/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:23:27 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/20 10:44:34 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (len > i)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
// 	char str1[10];
// 	char str2[10];
// 	ft_memset(str1, 'A', 1);
// 	memset(str2, 'A', 1);
// 	printf("%s\n", str1);
// 	printf("%s\n", str2);
// 	return 0;
// }
