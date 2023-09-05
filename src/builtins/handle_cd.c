/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:06:09 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/05 17:01:08 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_dot_num(char **array)
{
	int size;

	size = 0;
	while (array[size] != NULL)
	{
		if (array[size][0] == '\0')
		{
			size--;
			break ;
		}
		size++;
	}
	return (size);
}

static void	update_cdm_args_back_util(t_cmd *cmd_args, int num)
{
	int		i;
	int		j;
	char	*res;

	i = -1;
	j = 0;
	while ((cmd_args->abs_path)[j])
	{
		if ((cmd_args->abs_path)[j] == '/')
			i++;
		if (i == num)
			break ;
		j++;
	}
	res = malloc((j + 1) * sizeof(char));
	ft_memcpy(res, cmd_args->abs_path, j);
	res[j] = '\0';
	free(cmd_args->abs_path);
	cmd_args->abs_path = ft_strjoin(res, "");
}

static void	update_cdm_args_back(char *cmd, t_cmd *cmd_args)
{
	int		size_back;
	int		size_total;
	char	*dirs;

	size_back = 0;
	while (*cmd)
	{
		if (*cmd == '.' && *(cmd + 1) == '.')
			size_back++;
		cmd++;
	}
	size_total = 0;
	dirs = cmd_args->abs_path;
	while (*dirs)
	{
		if (*dirs == '/')
			size_total++;
		dirs++;
	}
	if (size_total <= size_back)
		(cmd_args->abs_path)[1] = '\0';
	else
		update_cdm_args_back_util(cmd_args, size_total - size_back);
}

static void	update_cdm_args_for(char *cmd, t_cmd *cmd_args)
{
	if (access(cmd, F_OK | X_OK) == 0)
	{
		free(cmd_args->abs_path);
		cmd_args->abs_path = ft_strjoin(cmd, "");
	}
	else
		printf("cd: %s: No such file or directory\n", cmd);
}

static void	update_cdm_args_to_child(char *cmd, t_cmd *cmd_args)
{
	char	*path;
	char	*cmd_path;
	int		i;

	cmd_path = ft_strjoin("/", cmd);
	path = ft_strjoin(cmd_args->abs_path, cmd_path);
	i = ft_strlen(path);
	if (path[i - 1] == '/')
		path[i - 1] = '\0';
	if (access(path, F_OK | X_OK) == 0)
	{
		free(cmd_args->abs_path);
		cmd_args->abs_path = ft_strjoin(path, "");
	}
	else
		printf("cd: %s: No such file or directory\n", cmd);
	free(cmd_path);
	free(path);
}

int	handle_cd(char **split_cmd, t_cmd *cmd_args)
{
	int	size;

	size = get_dot_num(split_cmd);
	if (size == 3)
	{
		printf("cd: string not in pwd: %s\n", split_cmd[1]);
		return (1);
	}
	if (size > 3)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	if (!split_cmd[1]
		|| ft_strncmp(split_cmd[1], "~", sizeof(split_cmd[1])) == 0)
	{
		free(cmd_args->abs_path);
		cmd_args->abs_path = NULL;
		cmd_args->abs_path = ft_strjoin(cmd_args->home_path, "");
		return (0);
	}
	if (ft_strncmp(split_cmd[1], "-", sizeof(split_cmd[1])) == 0)
		return (2);
	if (ft_strncmp(split_cmd[1], ".", sizeof(split_cmd[1])) == 0)
		return (3);
	if (split_cmd[1][0] == '.' && split_cmd[1][1] == '.')
		update_cdm_args_back(split_cmd[1], cmd_args);
	else if (split_cmd[1][0] == '/')
		update_cdm_args_for(split_cmd[1], cmd_args);
	else
		update_cdm_args_to_child(split_cmd[1], cmd_args);
	return (0);
}