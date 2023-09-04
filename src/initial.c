/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:20:54 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/04 15:17:22 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Get initial working directory
static char	*ini_pwd(void)
{
	size_t	size;
	char	*absolute_path;

	size = pathconf(".", _PC_PATH_MAX);
	absolute_path = (char *)malloc((size_t)size);
	if (absolute_path != NULL)
		absolute_path = getcwd(absolute_path, (size_t)size);
	if (absolute_path == NULL)
		perror("getcwd");
	return (absolute_path);
}

t_cmd	*initial_cmd(char **envp)
{
	t_cmd	*cmd_args;

	cmd_args = malloc(sizeof(t_cmd));
	if (cmd_args == NULL)
		return (NULL);
	cmd_args->abs_path = ini_pwd();
	cmd_args->home_path = getenv("HOME");
	cmd_args->envp = envp;
	if (cmd_args->abs_path == NULL
		|| cmd_args->home_path == NULL)
	{
		free(cmd_args);
		return (NULL);
	}
	return (cmd_args);
}
