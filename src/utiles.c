/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:23:29 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/04 20:28:52 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	get_size(char const *s)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (s[i])
	{
		if ((s[i] != ' ' && s[i] != '\0' && s[i + 1] == ' ')
			|| (s[i] != ' ' && s[i] != '\0' && s[i + 1] == '\0')
			|| (s[i] != '\'' && s[i] != '\0' && s[i + 1] == '\0')
			|| (s[i] != '\"' && s[i] != '\0' && s[i + 1] == '\0'))
			size++;
		i++;
	}
	return (size);
}

static void	copy(char const *s, char **res)
{
	int	i;
	int	size;

	size = 0;
	while (*s)
	{
		i = 0;
		while ((s[i] != ' ') && (s[i] != '\'')
			&& (s[i] != '\"') && (s[i] != '\0'))
			i++;
		res[size] = malloc((i + 1) * sizeof(char));
		if (res[size] != NULL)
		{
			res[size][i] = '\0';
			ft_memcpy(res[size], s, i);
			while (*s != ' ' && *s != '\0')
				s++;
			while ((*s == ' ' || *s == '\'' || *s == '\"'))
				s++;
			size++;
		}
	}
}

char	**space_quotes_split(char const *s)
{
	char	**res;
	int		size;

	if (!*s)
	{
		res = malloc((1) * sizeof(char *));
		res[0] = NULL;
		return (res);
	}
	while (*s == ' ' || *s == '\'' || *s == '\"')
		s++;
	size = get_size(s);
	res = malloc((size + 1) * sizeof(char *));
	if (res != NULL)
	{
		res[size] = NULL;
		copy(s, res);
	}
	return (res);
}
