/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:11:46 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/09 22:04:53 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Get number of cmds based on number of pipes
int	count_cmd(char **split_cmd)
{
	int	i;

	i = 0;
	while (split_cmd[i] && ft_strncmp(split_cmd[i], "|", 2) != 0)
		i++;
	return (i);
}

// Separate the cmds and put into each memory
int	separate_pipe_cmd(char **split_cmd, t_cmd *cmd_args, int i, int cmd_nbr)
{
	int	j;

	j = 0;
	if (cmd_nbr == 1)
	{
		cmd_args->cmd_one = malloc(sizeof(char *) * (count_cmd(split_cmd) + 1));
		while (split_cmd[i] && ft_strncmp(split_cmd[i], "|", 2) != 0)
		{
			cmd_args->cmd_one[j] = ft_strdup(split_cmd[i]);
			i++;
			j++;
		}
		cmd_args->cmd_one[j] = NULL;
	}
	else if (cmd_nbr == 2)
	{
		i++;
		cmd_args->cmd_two = malloc(sizeof(char *) * (count_cmd(split_cmd) + 1));
		while (split_cmd[i] && ft_strncmp(split_cmd[i], "|", 2) != 0)
		{
			cmd_args->cmd_two[j] = ft_strdup(split_cmd[i]);
			i++;
			j++;
		}
		cmd_args->cmd_two[j] = NULL;
	}
	else if (cmd_nbr == 3)
	{
		i++;
		cmd_args->cmd_three = malloc(sizeof(char *) * (count_cmd(split_cmd) + 1));
		while (split_cmd[i] && ft_strncmp(split_cmd[i], "|", 2) != 0)
		{
			cmd_args->cmd_three[j] = ft_strdup(split_cmd[i]);
			i++;
			j++;
		}
		cmd_args->cmd_three[j] = NULL;
	}
	return (i);
}

// Allocate the cmds to the struct
void	cmd_by_pipe(char *rl, t_cmd *cmd_args)
{
	char	**split_cmd;
	int		i;
	int		cmd_nbr;

	split_cmd = space_quotes_split(rl);
	i = 0;
	cmd_nbr = 1;
	cmd_args->pipe_c = count_pipe(rl);
	while (cmd_args->pipe_c >= 0)
	{
		i = separate_pipe_cmd(split_cmd, cmd_args, i, cmd_nbr);
		cmd_nbr++;
		cmd_args->pipe_c--;
	}
	cmd_args->pipe_c = count_pipe(rl);
}

char	**get_cmd(t_cmd *cmd_args)
{
	if (cmd_args->which_cmd == 0)
		return (cmd_args->cmd_one);
	else if (cmd_args->which_cmd == 1)
		return (cmd_args->cmd_two);
	else if (cmd_args->which_cmd == 2)
		return (cmd_args->cmd_three);
	return (NULL);
}
