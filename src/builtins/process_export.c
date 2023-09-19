/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:19:07 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/19 10:35:58 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	process_export_util(t_cmd *cmd_args, char *tem, char **tem_cmd, int i)
{
	int		size;
	char	**res;

	if (i < cmd_args->envp_size)
	{
		free(cmd_args->envp[i]);
		cmd_args->envp[i] = ft_strjoin(tem, tem_cmd[1]);
	}
	else
	{
		cmd_args->envp_size++;
		res = malloc((cmd_args->envp_size + 1) * sizeof(char *));
		size = -1;
		while (cmd_args->envp[++size])
		{
			res[size] = ft_strjoin(cmd_args->envp[size], "");
			free(cmd_args->envp[size]);
		}
		res[size] = ft_strjoin(tem, tem_cmd[1]);
		res[size + 1] = NULL;
		cmd_args->envp = res;
	}
}

void	process_export(char **split_cmd, t_cmd *cmd_args)
{
	char	*tem;
	int		i;
	char	**tem_cmd;

	tem_cmd = ft_split(split_cmd[0], '=');
	if (!tem_cmd[1])
	{
		tem_cmd[1] = split_cmd[1];
		split_cmd++;
	}
	tem = ft_strjoin(tem_cmd[0], "=");
	i = 0;
	while (cmd_args->envp[i])
	{
		if (ft_strncmp(cmd_args->envp[i], tem, ft_strlen(tem)) == 0)
			break ;
		i++;
	}
	process_export_util(cmd_args, tem, tem_cmd, i);
	free(tem);
	free_container(tem_cmd);
	if (*(++split_cmd))
		process_export(split_cmd, cmd_args);
}
