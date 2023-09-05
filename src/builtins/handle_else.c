/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_else.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:05:32 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/05 11:32:22 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_else(char **split_cmd, t_cmd *cmd_args)
{
	char	*path;
	int		result;

	if (cmd_args->envp == NULL)
		result_error(-1, split_cmd);
	path = get_path(split_cmd[0], cmd_args->envp);
	result = execve(path, split_cmd, cmd_args->envp);
	return (result);
}
