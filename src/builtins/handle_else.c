/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_else.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:05:32 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/05 19:42:52 by jaeshin          ###   ########.fr       */
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

	path = get_path(cmd_args->cmd_one[0], cmd_args->envp);
	// not handling options;;
	result = execve(path, cmd_args->cmd_one, cmd_args->envp);
	return (result);
}
