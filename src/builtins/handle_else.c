/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_else.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:05:32 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/06 15:33:52 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// void	get_each_path(t_cmd *cmd_args, char *cmd, char **envp)
// {
// 	int	count;

// 	count = cmd_args->pipe_c;
// 	while (count >= 0)
// 	{

// 	}
// }

int	handle_else(t_cmd *cmd_args)
{
	char	*path;
	int		result;

	char	*temp[4] = {"ls", "-l", cmd_args->abs_path, NULL};
	if (cmd_args->envp == NULL)
		result_error(-1, &cmd_args->cmd_one[0]);
	path = get_path(cmd_args->cmd_one[0], cmd_args->envp);
	result = execve(path, temp, cmd_args->envp);
	return (result);
}
