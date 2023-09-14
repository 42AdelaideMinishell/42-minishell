/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:08:15 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/12 17:08:24 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// takes the env pointer and search for the path where commands are stored
char	*find_path(char *name, char **envp)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		sub = ft_substr(envp[i], 0, j);
		if (ft_strncmp(name, sub, ft_strlen(name)) == 0)
		{
			free(sub);
			return (envp[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

// modify the path has been found through 'find_path'
// and check the the accessibility or permissions using 'access'
char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	**all_path;
	char	**splited_cmd;
	char	*one_path;
	char	*exec;

	i = 0;
	all_path = ft_split(find_path("PATH", envp), ':');
	splited_cmd = split_cmd(cmd);
	while (all_path[i])
	{
		one_path = ft_strjoin(all_path[i], "/");
		exec = ft_strjoin(one_path, splited_cmd[0]);
		free(one_path);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_container(splited_cmd);
			return (exec);
		}
		free(exec);
		i++;
	}
	free_container(all_path);
	free_container(splited_cmd);
	return (cmd);
}
