/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:30:33 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/14 09:30:36 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	res;

	res = 0;
	while (*str)
	{
		res++;
		str++;
	}
	return (res);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	printf("%lu\n", ft_strlen("Hello, World!"));
// 	printf("%lu", strlen("Hello, World!"));
// }
