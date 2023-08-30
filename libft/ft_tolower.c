/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:33:54 by jlyu              #+#    #+#             */
/*   Updated: 2023/07/14 09:33:57 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return ('a' + (c - 'A'));
	}
	return (c);
}

// #include <stdio.h>
// #include <ctype.h>
// int main() {
// 	char ch = 'G';
// 	char converted_ch = ft_tolower(ch);
// 	printf("Original character: %c\n", ch);
// 	printf("Uppercase character: %c\n", converted_ch);
// 	char converted_ch1 = tolower(ch);
// 	printf("Original character: %c\n", ch);
// 	printf("Uppercase character: %c\n", converted_ch1);
// 	return 0;
// }
