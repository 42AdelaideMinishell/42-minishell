/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:06:09 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/07 16:49:20 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	update_cdm_args_back_util(t_cmd *cmd_args, int num, char *dirs)
{
	int		i;
	int		j;
	char	*res;

	i = -1;
	j = 0;
	while (dirs[j])
	{
		if (dirs[j] == '/')
			i++;
		if (i == num)
			break ;
		j++;
	}
	res = malloc((j + 1) * sizeof(char));
	ft_memcpy(res, dirs, j);
	res[j] = '\0';
	cmd_args->abs_path = ft_strjoin(res, "");
}

static void	update_cdm_args_back(char *cmd, t_cmd *cmd_args, char *tem)
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
	dirs = tem;
	while (*dirs)
	{
		if (*dirs == '/')
			size_total++;
		dirs++;
	}
	if (size_total <= size_back)
		cmd_args->abs_path = ft_strjoin("/", "");
	else
		update_cdm_args_back_util(cmd_args, size_total - size_back, tem);
}

static void	update_cdm_args_to_child(char *cmd, t_cmd *cmd_args, char *tem)
{
	char	*path;
	char	*cmd_path;
	int		i;

	cmd_path = ft_strjoin("/", cmd);
	path = ft_strjoin(tem, cmd_path);
	i = ft_strlen(path);
	if (path[i - 1] == '/')
		path[i - 1] = '\0';
	cmd_args->abs_path = ft_strjoin(path, "");
	free(cmd_path);
	free(path);
}

void	process_cd(char **split_cmd, t_cmd *cmd_args)
{
	char	*tem;

	tem = ft_strjoin(cmd_args->abs_path, "");
	free(cmd_args->abs_path);
	if (!split_cmd[1]
		|| ft_strncmp(split_cmd[1], "~", sizeof(split_cmd[1])) == 0)
		cmd_args->abs_path = ft_strjoin(cmd_args->home_path, "");
	else if (ft_strncmp(split_cmd[1], "-", sizeof(split_cmd[1])) == 0)
		cmd_args->abs_path = ft_strjoin(cmd_args->pre_path, "");
	else if (split_cmd[1][0] == '.' && split_cmd[1][1] == '.')
		update_cdm_args_back(split_cmd[1], cmd_args, tem);
	else if (ft_strncmp(split_cmd[1], ".", sizeof(split_cmd[1])) == 0)
	{
		cmd_args->abs_path = ft_strjoin(tem, "");
		free(tem);
		tem = ft_strjoin(cmd_args->pre_path, "");
		free(cmd_args->pre_path);
	}
	else if (split_cmd[1][0] == '/')
		cmd_args->abs_path = ft_strjoin(split_cmd[1], "");
	else
		update_cdm_args_to_child(split_cmd[1], cmd_args, tem);
	cmd_args->pre_path = ft_strjoin(tem, "");
	free(tem);
}
