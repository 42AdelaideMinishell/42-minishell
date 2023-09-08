/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:19:07 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/08 16:03:50 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	process_export(char **split_cmd, t_cmd *cmd_args)
{
	char	*tem;
	int		i;
	int		size;
	char	**res;
	char	**tem_cmd;

// NEED TO FIX COMMAND SPLIT WITH SINGLE/DOUBLE COMMON
	tem_cmd = ft_split(split_cmd[0], '=');
	if (!tem_cmd[1])
	{
		tem_cmd[1] = split_cmd[1];
		split_cmd++;
	}
	tem = ft_strjoin(tem_cmd[0], "=");
	size = -1;
	while (cmd_args->envp[++size]);
	i = 0;
	while (cmd_args->envp[i])
	{
		if (ft_strncmp(cmd_args->envp[i], tem, ft_strlen(tem)) == 0)
			break ;
		i++;
	}
	if (i <= size)
		cmd_args->envp[i] = ft_strjoin(tem, tem_cmd[1]);
	else
	{
		res = malloc((size + 2) * sizeof(char *));
		size = -1;
		while (cmd_args->envp[++size])
			res[size] = ft_strjoin(cmd_args->envp[size], "");
		res[size] = ft_strjoin(tem, tem_cmd[1]);
		res[size + 1] = NULL;
		free_container(cmd_args->envp);
		cmd_args->envp = res;
	}
	free(tem);
	free_container(tem_cmd);
	if (*(++split_cmd))
		process_export(split_cmd, cmd_args);
}