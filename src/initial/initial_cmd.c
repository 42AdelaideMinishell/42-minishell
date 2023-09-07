/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:20:54 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/06 14:39:24 by jaeshin          ###   ########.fr       */
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

int	count_pipe(char *rl)
{
	int	i;

	i = 0;
	while (*rl)
	{
		if (*rl == '|')
			i++;
		rl++;
	}
	return (i);
}

t_cmd	*initial_cmd(char **envp)
{
	t_cmd	*cmd_args;

	cmd_args = malloc(sizeof(t_cmd));
	if (cmd_args == NULL)
		return (NULL);
	cmd_args->abs_path = ini_pwd();
	cmd_args->pre_path = ini_pwd();
	cmd_args->home_path = getenv("HOME");
	cmd_args->envp = envp;
	cmd_args->pipe_c = 0;
	cmd_args->which_cmd = 0;
	cmd_args->cmd_one = NULL;
	cmd_args->cmd_two = NULL;
	cmd_args->cmd_three = NULL;
	if (cmd_args->abs_path == NULL
		|| cmd_args->home_path == NULL)
	{
		free(cmd_args);
		return (NULL);
	}
	return (cmd_args);
}
