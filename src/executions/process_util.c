/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:14:24 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/16 22:49:29 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cmd_process(t_cmd *cmd_args)
{
	int		result;
	char	*path;

	if (redirection(cmd_args))
		exit(0);
	if (ft_strncmp(cmd_args->cur_cmd[0], "cd", ft_strlen(cmd_args->cur_cmd[0])) == 0
		&& (ft_strncmp(cmd_args->cur_cmd[1], "-", ft_strlen(cmd_args->cur_cmd[1])) == 0
		|| ft_strncmp(cmd_args->cur_cmd[1], "~", ft_strlen(cmd_args->cur_cmd[1])) == 0)
		&& !cmd_args->cur_cmd[2])
		exit(0);
	if (ft_strncmp(cmd_args->cur_cmd[0], "unset", ft_strlen(cmd_args->cur_cmd[0])) == 0
		|| ft_strncmp(cmd_args->cur_cmd[0], "export", ft_strlen(cmd_args->cur_cmd[0])) == 0
		|| ft_strncmp(cmd_args->cur_cmd[0], "exit", ft_strlen(cmd_args->cur_cmd[0])) == 0)
		exit(0);
	if (ft_strncmp(cmd_args->cur_cmd[0], "echo", ft_strlen(cmd_args->cur_cmd[0])) == 0)
	 	process_echo(cmd_args->cur_cmd, cmd_args);
	if (ft_strncmp(cmd_args->cur_cmd[0], "exit", ft_strlen(cmd_args->cur_cmd[0])) == 0)
		exit(0);
	chdir(cmd_args->abs_path);
	path = get_path(cmd_args->cur_cmd[0], cmd_args->envp);
	result = execve(path, cmd_args->cur_cmd, cmd_args->envp);
	result_error(result, cmd_args);
}

void	process_parent(t_cmd *cmd_args, int status)
{
	if (status != 0)
		return ;
	if (ft_strncmp(cmd_args->cur_cmd[0], "cd", ft_strlen(cmd_args->cur_cmd[0])) == 0)
		process_cd(cmd_args->cur_cmd, cmd_args);
	if (ft_strncmp(cmd_args->cur_cmd[0], "unset", ft_strlen(cmd_args->cur_cmd[0])) == 0)
		process_unset(cmd_args->cur_cmd, cmd_args);
	if (ft_strncmp(cmd_args->cur_cmd[0], "export", ft_strlen(cmd_args->cur_cmd[0])) == 0)
		process_export(++cmd_args->cur_cmd, cmd_args);
	if (ft_strncmp(cmd_args->cur_cmd[0], "exit", ft_strlen(cmd_args->cur_cmd[0])) == 0)
		cmd_args->exit_flag = 0;
	// int i = -1;
	// while (cmd_args->envp[++i])
	// 	printf("%s\n", cmd_args->envp[i]);
}
