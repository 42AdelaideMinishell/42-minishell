/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:10:44 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/07 12:04:00 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// free the cmd containers after usages
void	free_container(char **temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(temp);
}

void	free_cmd1(t_cmd *cmd_args)
{
	int	i;

	i = 0;
	if (cmd_args->cmd_one)
	{
		printf("free1\n");
		while (cmd_args->cmd_one[i])
		{
			free(cmd_args->cmd_one[i]);
			i++;
		}
		free(cmd_args->cmd_one);
		cmd_args->cmd_one = NULL;
	}
}

void	free_cmd2(t_cmd *cmd_args)
{
	int	i;

	i = 0;
	if (cmd_args->cmd_two)
	{
		printf("free2\n");
		while (cmd_args->cmd_two[i])
		{
			free(cmd_args->cmd_two[i]);
			i++;
		}
		free(cmd_args->cmd_two);
		cmd_args->cmd_two = NULL;
	}
}

void	free_cmd3(t_cmd *cmd_args)
{
	int	i;

	i = 0;
	if (cmd_args->cmd_three)
	{
		printf("free3\n");
		while (cmd_args->cmd_three[i])
		{
			free(cmd_args->cmd_three[i]);
			i++;
		}
		free(cmd_args->cmd_three);
		cmd_args->cmd_three = NULL;
	}
}

void	free_all_cmd(t_cmd *cmd_args)
{
	free_cmd1(cmd_args);
	free_cmd2(cmd_args);
	free_cmd3(cmd_args);
}
