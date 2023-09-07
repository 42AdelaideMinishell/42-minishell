/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:14:24 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/07 14:11:23 by jlyu             ###   ########.fr       */
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

void	process_parent(char *rl, t_cmd *cmd_args, int status)
{
	char	**split_cmd;

	if (status != 0)
		return ;
	split_cmd = space_quotes_split(rl);
	if (ft_strncmp(split_cmd[0], "cd", sizeof(split_cmd[0])) == 0)
		process_cd(split_cmd, cmd_args);
	if (ft_strncmp(split_cmd[0], "unset", sizeof(split_cmd[0])) == 0
		&& ft_strncmp(split_cmd[1], "PATH", sizeof(split_cmd[0])) == 0)
		cmd_args->envp = NULL;
}
