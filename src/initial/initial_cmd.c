/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:20:54 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/19 10:20:17 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

char	**ini_envp(char **envp)
{
	int		size;
	char	**res;

	size = -1;
	while (envp[++size])
	{
	}
	res = malloc((size + 1) * sizeof(char *));
	size = -1;
	while (envp[++size])
		res[size] = ft_strjoin(envp[size], "");
	res[size] = NULL;
	return (res);
}

t_cmd	*initial_cmd(char **envp)
{
	t_cmd	*cmd_args;

	cmd_args = malloc(sizeof(t_cmd));
	if (cmd_args == NULL)
		return (NULL);
	cmd_args->exit_flag = 1;
	cmd_args->abs_path = ini_pwd();
	cmd_args->pre_path = ini_pwd();
	cmd_args->home_path = getenv("HOME");
	cmd_args->envp = ini_envp(envp);
	cmd_args->p_re_count = 0;
	cmd_args->cmd_order = 0;
	cmd_args->cmd = NULL;
	cmd_args->cur_cmd = NULL;
	cmd_args->envp_size = 0;
	while (cmd_args->envp[cmd_args->envp_size])
		cmd_args->envp_size++;
	if (cmd_args->abs_path == NULL
		|| cmd_args->home_path == NULL)
	{
		free(cmd_args);
		return (NULL);
	}
	return (cmd_args);
}
