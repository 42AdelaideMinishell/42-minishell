/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:23:29 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/04 15:07:35 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	get_size(char const *s, char c)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i] != '\0' && s[i + 1] == c)
			|| (s[i] != c && s[i] != '\0' && s[i + 1] == '\0')
			|| (s[i] != '\'' && s[i] != '\0' && s[i + 1] == '\0')
			|| (s[i] != '\"' && s[i] != '\0' && s[i + 1] == '\0'))
			size++;
		i++;
	}
	return (size);
}

static void	copy(char const *s, char c, char **res)
{
	int	i;
	int	size;

	size = 0;
	while (*s)
	{
		i = 0;
		while ((s[i] != c) && (s[i] != '\'')
			&& (s[i] != '\"') && (s[i] != '\0'))
			i++;
		res[size] = malloc((i + 1) * sizeof(char));
		if (res[size] != NULL)
		{
			res[size][i] = '\0';
			ft_memcpy(res[size], s, i);
			while (*s != c && *s != '\0')
				s++;
			while ((*s == c || *s == '\'' || *s == '\"') && c != '\0')
				s++;
			size++;
		}
	}
}

char	**minishell_split(char const *s, char c)
{
	char	**res;
	int		size;

	if (!*s)
	{
		res = malloc((1) * sizeof(char *));
		res[0] = NULL;
		return (res);
	}
	while (*s == c || *s == '\'' || *s == '\"')
		s++;
	size = get_size(s, c);
	res = malloc((size + 1) * sizeof(char *));
	if (res != NULL)
	{
		res[size] = NULL;
		copy(s, c, res);
	}
	return (res);
}
