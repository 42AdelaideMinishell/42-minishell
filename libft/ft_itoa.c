/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:23:13 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/20 10:24:25 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static void	int_to_string(int n, char *res, int i, int flag)
{
	res[i] = '\0';
	if (n == 0)
		res[0] = '0';
	if (flag)
	{
		res[0] = '-';
		while (n != 0)
		{
			res[i - 1] = -(n % 10) + '0';
			n = n / 10;
			i--;
		}
	}
	else
	{
		while (n != 0)
		{
			res[i - 1] = (n % 10) + '0';
			n = n / 10;
			i--;
		}
	}
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;
	int		flag;

	i = get_size(n);
	flag = 0;
	if (n != 0)
	{
		if (n < 0)
		{
			i++;
			flag = 1;
		}
		res = malloc((i + 1) * sizeof(char));
		if (res != NULL)
			int_to_string(n, res, i, flag);
	}
	else
	{
		res = malloc(2 * sizeof(char));
		if (res != NULL)
			int_to_string(n, res, 1, flag);
	}
	return (res);
}

// #include <stdio.h>
// #include <limits.h>
// int main() {
// 	int str = INT_MAX;
// 	char *result = ft_itoa(str);
// 	printf("%s", result);
// }
