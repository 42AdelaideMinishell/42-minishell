/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cur_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:11:46 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/18 16:27:38 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// char	*ft_strdup(const char *s1)
// {
// 	int		size;
// 	char	*res;
// 	size = ft_strlen(s1);
// 	res = malloc((size + 1) * sizeof(char));
// 	if (res != NULL)
// 	{
// 		res[size] = '\0';
// 		while (size > 0)
// 		{
// 			res[size - 1] = s1[size - 1];
// 			size--;
// 		}
// 	}
// 	return (res);
// }

// size_t	ft_strlen(const char *str)
// {
// 	size_t	res;
// 	res = 0;
// 	while (*str)
// 	{
// 		res++;
// 		str++;
// 	}
// 	return (res);
// }

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	if (n < 0)
// 	{
// 		n = ft_strlen(s1);
// 		if (n < ft_strlen(s2))
// 			n = ft_strlen(s2);
// 	}
// 	while (n > 0)
// 	{
// 		if (*(unsigned char *)s1 != *(unsigned char *)s2)
// 			return (*(unsigned char *)s1 - *(unsigned char *)s2);
// 		if (*(unsigned char *)s1 == '\0')
// 			return (0);
// 		s1++;
// 		s2++;
// 		n--;
// 	}
// 	return (0);
// }

int	count_pipe(char **split_cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (split_cmd[i])
	{
		if (ft_strncmp(split_cmd[i], "|", 2) == 0)
			count++;
		i++;
	}
	return (count);
}

int	count_pipe_redirection(char **split_cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (split_cmd[i])
	{
		if ((ft_strncmp(split_cmd[i], "|", 2) == 0)
			|| (ft_strncmp(split_cmd[i], ">", 2) == 0)
			|| (ft_strncmp(split_cmd[i], "<", 2) == 0)
			|| (ft_strncmp(split_cmd[i], ">>", 3) == 0)
			|| (ft_strncmp(split_cmd[i], "<<", 3) == 0))
			count++;
		i++;
	}
	return (count);
}

static int	cmd_size(char **cmd)
{
	int	i;

	i = 0;
	if ((cmd[i] && ft_strncmp(cmd[i], ">", 2) == 0)
		|| (cmd[i] && ft_strncmp(cmd[i], ">>", 3) == 0)
		|| (cmd[i] && ft_strncmp(cmd[i], "<", 2) == 0)
		|| (cmd[i] && ft_strncmp(cmd[i], "<<", 3) == 0))
		i++;
	while ((cmd[i] && ft_strncmp(cmd[i], "|", 2) != 0)
		&& (cmd[i] && ft_strncmp(cmd[i], ">", 2) != 0)
		&& (cmd[i] && ft_strncmp(cmd[i], ">>", 3) != 0)
		&& (cmd[i] && ft_strncmp(cmd[i], "<", 2) != 0)
		&& (cmd[i] && ft_strncmp(cmd[i], "<<", 3) != 0))
		i++;
	return (i);
}

static char	**choose_cur_cmd_helper(char **cmd, int cmd_order)
{
	while (cmd_order > 0)
	{
		if ((*cmd && ft_strncmp(*cmd, ">", 2) == 0)
			|| (*cmd && ft_strncmp(*cmd, ">>", 3) == 0)
			|| (*cmd && ft_strncmp(*cmd, "<", 2) == 0)
			|| (*cmd && ft_strncmp(*cmd, "<<", 3) == 0))
			cmd++;
		while ((*cmd && ft_strncmp(*cmd, "|", 2) != 0)
			&& (*cmd && ft_strncmp(*cmd, ">", 2) != 0)
			&& (*cmd && ft_strncmp(*cmd, ">>", 3) != 0)
			&& (*cmd && ft_strncmp(*cmd, "<", 2) != 0)
			&& (*cmd && ft_strncmp(*cmd, "<<", 3) != 0))
			cmd++;
		if (*cmd && ft_strncmp(*cmd, "|", 2) == 0)
			cmd++;
		cmd_order--;
	}
	return (cmd);
}

char	**choose_cur_cmd(char **cmd, int cmd_order)
{
	int		i;
	char	**result;

	i = 0;
	cmd = choose_cur_cmd_helper(cmd, cmd_order);
	result = malloc(sizeof(char *) * (cmd_size(cmd) + 1));
	while ((*cmd && ft_strncmp(*cmd, "|", 2) != 0))
	{
		result[i] = ft_strdup(*cmd);
		cmd++;
		i++;
		if ((*cmd && ft_strncmp(*cmd, ">", 2) == 0)
			|| (*cmd && ft_strncmp(*cmd, ">>", 3)) == 0
			|| (*cmd && ft_strncmp(*cmd, "<", 2)) == 0
			|| (*cmd && ft_strncmp(*cmd, "<<", 3)) == 0)
			break ;
	}
	result[i] = NULL;
	return (result);
}
