/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:31:43 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/14 09:31:45 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	inner(unsigned int n, int fd)
{
	if (n < 10)
	{
		ft_putchar_fd((n + '0'), fd);
	}
	else
	{
		inner(n / 10, fd);
		ft_putchar_fd(((n % 10) + '0'), fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		inner(-n, fd);
	}
	else
		inner(n, fd);
}

// #include <stdio.h>
// #include <limits.h>
// int main() {
// 	int str = INT_MAX;
// 	ft_putnbr_fd(str, 1);
// }