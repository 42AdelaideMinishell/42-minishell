/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:25:28 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/14 09:25:31 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return ('A' + (c - 'a'));
	}
	return (c);
}

// #include <stdio.h>
// #include <ctype.h>
// int main() {
// 	char ch = 'o';
// 	char converted_ch = ft_toupper(ch);
// 	printf("Original character: %c\n", ch);
// 	printf("Uppercase character: %c\n", converted_ch);
// 	char converted_ch1 = toupper(ch);
// 	printf("Original character: %c\n", ch);
// 	printf("Uppercase character: %c\n", converted_ch1);
// 	return 0;
// }
