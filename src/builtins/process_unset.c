/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:17:30 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/19 10:43:37 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	process_unset_util(t_cmd *cmd_args, int i, char **res)
{
	int		j;
	int		size;

	size = -1;
	j = 0;
	while (cmd_args->envp[++size + j])
	{
		if (size == i)
		{
			free(cmd_args->envp[size + j]);
			j = 1;
			if (!cmd_args->envp[size + j])
				break ;
		}
		res[size] = ft_strjoin(cmd_args->envp[size + j], "");
		free(cmd_args->envp[size + j]);
	}
	res[size] = NULL;
	cmd_args->envp = res;
}

void	process_unset(char **split_cmd, t_cmd *cmd_args)
{
	char	*tem;
	int		i;
	char	**res;

	tem = ft_strjoin(split_cmd[1], "=");
	i = 0;
	while (cmd_args->envp[i])
	{
		if (ft_strncmp(cmd_args->envp[i], tem, ft_strlen(tem)) == 0)
			break ;
		i++;
	}
	if (i < cmd_args->envp_size)
	{
		cmd_args->envp_size--;
		res = malloc((cmd_args->envp_size + 1) * sizeof(char *));
		process_unset_util(cmd_args, i, res);
	}
	free(tem);
}
