/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:14:24 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/19 09:50:02 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cmd_process_util(t_cmd *cmd_args)
{
	int		result;
	char	*path;

	chdir(cmd_args->abs_path);
	redirection(cmd_args);
	path = get_path(cmd_args->cur_cmd[0], cmd_args->envp);
	result = execve(path, cmd_args->cur_cmd, cmd_args->envp);
	result_error(result, cmd_args);
}

void	cmd_process(t_cmd *cmd_args)
{
	if (ft_strncmp(cmd_args->cur_cmd[0], "cd",
			ft_strlen(cmd_args->cur_cmd[0])) == 0
		&& (ft_strncmp(cmd_args->cur_cmd[1], "-",
				ft_strlen(cmd_args->cur_cmd[1])) == 0
			|| ft_strncmp(cmd_args->cur_cmd[1], "~",
				ft_strlen(cmd_args->cur_cmd[1])) == 0)
		&& !cmd_args->cur_cmd[2])
		exit(0);
	if (ft_strncmp(cmd_args->cur_cmd[0], "unset",
			ft_strlen(cmd_args->cur_cmd[0])) == 0
		|| ft_strncmp(cmd_args->cur_cmd[0], "export",
			ft_strlen(cmd_args->cur_cmd[0])) == 0
		|| ft_strncmp(cmd_args->cur_cmd[0], "exit",
			ft_strlen(cmd_args->cur_cmd[0])) == 0)
		exit(0);
	if (ft_strncmp(cmd_args->cur_cmd[0], "echo",
			ft_strlen(cmd_args->cur_cmd[0])) == 0)
		process_echo(cmd_args->cur_cmd, cmd_args);
	if (ft_strncmp(cmd_args->cur_cmd[0], "exit",
			ft_strlen(cmd_args->cur_cmd[0])) == 0)
		exit(0);
	cmd_process_util(cmd_args);
}

void	process_parent(t_cmd *cmd_args, int status)
{
	if (status != 0)
		return ;
	if (ft_strncmp(cmd_args->cur_cmd[0], "cd",
			ft_strlen(cmd_args->cur_cmd[0])) == 0)
		process_cd(cmd_args->cur_cmd, cmd_args);
	if (ft_strncmp(cmd_args->cur_cmd[0], "unset",
			ft_strlen(cmd_args->cur_cmd[0])) == 0)
		process_unset(cmd_args->cur_cmd, cmd_args);
	if (ft_strncmp(cmd_args->cur_cmd[0], "export",
			ft_strlen(cmd_args->cur_cmd[0])) == 0)
		process_export((cmd_args->cur_cmd + 1), cmd_args);
	if (ft_strncmp(cmd_args->cur_cmd[0], "exit",
			ft_strlen(cmd_args->cur_cmd[0])) == 0)
		cmd_args->exit_flag = 0;
}
