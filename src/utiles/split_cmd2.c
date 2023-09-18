/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:19:17 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/18 12:20:11 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_size_helper(char const *s, int i)
{
	if (s[i] == SINGLE_Q)
	{
		i++;
		while (s[i] && s[i] != SINGLE_Q)
			i++;
	}
	else if (s[i] == DOUBLE_Q)
	{
		i++;
		while (s[i] && s[i] != DOUBLE_Q)
			i++;
	}
	while (s[i] && s[i] != SPACE)
		i++;
	while (s[i] && s[i] == SPACE)
		i++;
	return (i);
}

int	move_index(char const *s)
{
	int	i;

	i = 0;
	if (s[i] == SINGLE_Q)
	{
		i++;
		while (s[i] && s[i] != SINGLE_Q)
			i++;
	}
	else if (s[i] == DOUBLE_Q)
	{
		i++;
		while (s[i] && s[i] != DOUBLE_Q)
			i++;
	}
	while (s[i] && s[i] != SPACE)
		i++;
	return (i);
}

char const	*copy_helper(char const *s)
{
	if (*s == DOUBLE_Q)
	{
		s++;
		while (*s && *s != DOUBLE_Q)
			s++;
	}
	else if (*s == SINGLE_Q)
	{
		s++;
		while (*s && *s != SINGLE_Q)
			s++;
	}
	while (*s && *s != SPACE)
		s++;
	while (*s && *s == SPACE)
		s++;
	return (s);
}
