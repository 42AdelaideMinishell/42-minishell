/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:14:24 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/11 16:05:01 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// tries to run the command, if it doesn't work, returns the error message.
void	one_cmd_process(t_cmd *cmd_args)
{
	char	**cmd;
	int		result;
	char	*path;

	cmd = get_cmd(cmd_args);
	if (ft_strncmp(cmd_args->cmd_one[0], "cd", ft_strlen(cmd_args->cmd_one[0])) == 0
		&& (ft_strncmp(cmd_args->cmd_one[1], "-", ft_strlen(cmd_args->cmd_one[1])) == 0
			|| ft_strncmp(cmd_args->cmd_one[1], "~", ft_strlen(cmd_args->cmd_one[1])) == 0)
		&& !cmd_args->cmd_one[2])
		exit(0);
	if (ft_strncmp(cmd_args->cmd_one[0], "unset", ft_strlen(cmd_args->cmd_one[0])) == 0
		|| ft_strncmp(cmd_args->cmd_one[0], "export", ft_strlen(cmd_args->cmd_one[0])) == 0
		|| ft_strncmp(cmd_args->cmd_one[0], "exit", ft_strlen(cmd_args->cmd_one[0])) == 0)
		exit(0);
// Sigle common should be handle
	// if (ft_strncmp(cmd_args->cmd_one[0], "echo", ft_strlen(cmd_args->cmd_one[0])) == 0)
	// 	process_echo(cmd, cmd_args);
	if (ft_strncmp(cmd_args->cmd_one[0], "exit", ft_strlen(cmd_args->cmd_one[0])) == 0)
		exit(0);
	chdir(cmd_args->abs_path);
	path = get_path(cmd[0], cmd_args->envp);
	result = execve(path, cmd, cmd_args->envp);
	result_error(result, cmd_args);
}

void	process_parent(t_cmd *cmd_args, int status)
{
	char	**cmd;

	if (status != 0)
		return ;
	cmd = get_cmd(cmd_args);
	if (ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])) == 0)
		process_cd(cmd, cmd_args);
	if (ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])) == 0)
		process_unset(cmd, cmd_args);
	if (ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])) == 0)
		process_export(++cmd, cmd_args);
	if (ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])) == 0)
		cmd_args->exit_flag = 0;
	// int i = -1;
	// while (cmd_args->envp[++i])
	// 	printf("%s\n", cmd_args->envp[i]);
}
