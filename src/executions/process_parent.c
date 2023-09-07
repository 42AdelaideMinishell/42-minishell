/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:14:24 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/07 12:24:34 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// tries to run the command, if it doesn't work, returns the error message.
void	process_child(char *rl, t_cmd *cmd_args)
{
	char	**split_cmd;
	int		result;
	char	*path;

	split_cmd = space_quotes_split(rl);
	char	*temp[3] = {"cd", NULL};
	if (cmd_args->envp == NULL)
		result_error(-1, &cmd_args->cmd_one[0]);
	chdir(cmd_args->abs_path);
	path = get_path(cmd_args->cmd_one[0], cmd_args->envp);
	result = execve(path, temp, cmd_args->envp);
	result_error(result, split_cmd);
}

void	process_parent(char *rl, t_cmd *cmd_args, int status)
{
	char	**split_cmd;

	printf("%d\n", status);
	if (status != 0)
		return ;
	split_cmd = space_quotes_split(rl);
	if (ft_strncmp(split_cmd[0], "cd", sizeof(split_cmd[0])) == 0)
		process_cd(split_cmd, cmd_args);
	if (ft_strncmp(split_cmd[0], "unset", sizeof(split_cmd[0])) == 0
		&& ft_strncmp(split_cmd[1], "PATH", sizeof(split_cmd[0])) == 0)
		cmd_args->envp = NULL;
}
