/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:14:24 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/06 16:15:05 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parent_cd(t_cmd *cmd_args, char *buffer)
{
	char	*tem;

	if (ft_strncmp(buffer, "pathkeep", 7) != 0)
	{
		tem = ft_strjoin(cmd_args->abs_path, "");
		free(cmd_args->abs_path);
		if (ft_strncmp(buffer, "pathpre", 7) == 0)
			cmd_args->abs_path = ft_strjoin(cmd_args->pre_path, "");
		else if (ft_strncmp(buffer, "path/", 5) == 0)
			cmd_args->abs_path = ft_strjoin(buffer + 4, "");
		cmd_args->pre_path = ft_strjoin(tem, "");
		free(tem);
	}
}

void	process_parent(t_cmd *cmd_args, int *fd)
{
	char	buffer[100];
	int		i;

	i = -1;
	while (++i < 100)
		buffer[i] = '\0';
	close(fd[1]);
	read(fd[0], buffer, 100);
	close(fd[0]);
	if (ft_strncmp(buffer, "null", 4) != 0)
	{
		if (ft_strncmp(buffer, "path", 4) == 0)
			parent_cd(cmd_args, buffer);
		else if (ft_strncmp(buffer, "envp", 4) == 0)
			cmd_args->envp = NULL;
	}
}
