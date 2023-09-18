/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:23:29 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/18 12:17:58 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//void	*ft_memcpy(void *dst, const void *src, size_t n)
//{
//	size_t	i;
//	i = 0;
//	if (!dst && !src)
//	{
//		return (NULL);
//	}
//	while (i < n)
//	{
//		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
//		i++;
//	}
//	return (dst);
//}

static int	get_size(char const *s)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (s[i])
	{
		while (s[i] == SPACE || s[i] == '\t')
			i++;
		if (s[i] != SPACE && s[i] != SINGLE_Q && s[i] != DOUBLE_Q)
			i = get_size_helper(s, i);
		else if (s[i] == SINGLE_Q)
			i = get_size_helper(s, i);
		else if (s[i] == DOUBLE_Q)
			i = get_size_helper(s, i);
		size++;
	}
	return (size);
}

static void	copy(char const *s, char **res)
{
	int	i;
	int	size;

	size = 0;
	while (*s != '\0')
	{
		i = move_index(s);
		res[size] = malloc((i) * sizeof(char));
		if (res[size] != NULL)
		{
			res[size][i] = '\0';
			ft_memcpy(res[size], s, i);
			s = copy_helper(s);
			size++;
		}
	}
}

static int	remove_quotes_helper(char **strs, int i, int j)
{
	while (strs[i][j])
	{
		if (strs[i][j + 1])
			strs[i][j] = strs[i][j + 1];
		else
			strs[i][j] = '\0';
		j++;
	}
	return (0);
}

static char	**remove_quotes(char **strs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if ((strs[i][j] == SINGLE_Q && strs[i][j + 1] != '$')
				|| strs[i][j] == DOUBLE_Q)
				j = remove_quotes_helper(strs, i, j);
			j++;
		}
		i++;
	}
	return (strs);
}

char	**split_cmd(char const *rl)
{
	char	**res;
	int		size;

	while (*rl == SPACE || *rl == '\t')
		rl++;
	size = get_size(rl);
	res = malloc((size + 1) * sizeof(char *));
	if (res != NULL)
	{
		res[size] = NULL;
		copy(rl, res);
	}
	res = remove_quotes(res);
	return (res);
}

//int	main(void)
//{
//	char *temp = "echo'1234' '$src'";
//	char **result = split_cmd(temp);
//	int	size = get_size(temp);
//	while (size-- > 0)
//	{
//		printf("|%s|     ", *result);
//		result++;
//	}
//	printf("\nsize - %d\n", get_size(temp));
//	return (0);
//}
