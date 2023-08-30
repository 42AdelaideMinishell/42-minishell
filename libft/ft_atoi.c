/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:29:19 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/14 09:29:20 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned int	res;
	int				flag;

	res = 0;
	flag = 1;
	while (*str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			flag = -1;
		str++;
	}
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			res = res * 10 + (*str - '0');
		else
			break ;
		str++;
	}
	return (res * flag);
}

// #include <stdio.h>
// #include <stdlib.h>
// int main() {
// 	const char *str = "	 91";
// 	int num = ft_atoi(str);
// 	printf("Converted number: %d\n", num);
// 	int num1 = atoi(str);
// 	printf("Converted number: %d\n", num1);
// return 0;
// }
