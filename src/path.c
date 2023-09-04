/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:08:15 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/04 15:08:16 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// free the temporary containers after usages
void	free_container(char **temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(temp);
}

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
	char	**split_cmd;
	char	*one_path;
	char	*exec;

	i = 0;
	all_path = ft_split(find_path("PATH", envp), ':');
	split_cmd = ft_split(cmd, ' ');
	while (all_path[i])
	{
		one_path = ft_strjoin(all_path[i], "/");
		exec = ft_strjoin(one_path, split_cmd[0]);
		free(one_path);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_container(split_cmd);
			return (exec);
		}
		free(exec);
		i++;
	}
	free_container(all_path);
	free_container(split_cmd);
	return (cmd);
}

// tries to run the command, if it doesn't work, returns the error message.
void	execute(char *cmd, t_cmd *cmd_args)
{
	char	**split_cmd;
	int		result;

	split_cmd = ft_split(cmd, ' ');
	result = 0;
	if (ft_strncmp(split_cmd[0], "cd", sizeof(split_cmd[0])) == 0)
		result = handle_cd(split_cmd, cmd_args);
	// PWD edit can be here
	else if (ft_strncmp(split_cmd[0], "pwd", sizeof(split_cmd[0])) == 0)
		printf("%s\n", cmd_args->abs_path);
	else if (ft_strncmp(split_cmd[0], "unset", sizeof(split_cmd[0])) == 0
		&& ft_strncmp(split_cmd[1], "PATH", sizeof(split_cmd[0])) == 0)
		cmd_args->envp = NULL;
	else
	{
		printf("%s\n", cmd_args->envp[0]);
		result = handle_else(split_cmd, cmd_args);
	}
	result_error(result, split_cmd);
	exit(0);
}
