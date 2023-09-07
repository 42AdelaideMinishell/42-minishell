/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:14:24 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/07 17:36:01 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// tries to run the command, if it doesn't work, returns the error message.
void	process_child(t_cmd *cmd_args)
{
	char	**cmd;
	int		result;
	char	*path;

	cmd = get_cmd(cmd_args);
	if (cmd_args->envp == NULL)
		result_error(-1, cmd_args);
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
	if (ft_strncmp(cmd[0], "cd", sizeof(cmd[0])) == 0)
		process_cd(cmd, cmd_args);
	if (ft_strncmp(cmd[0], "unset", sizeof(cmd[0])) == 0
		&& ft_strncmp(cmd[1], "PATH", sizeof(cmd[0])) == 0)
		cmd_args->envp = NULL;
}
