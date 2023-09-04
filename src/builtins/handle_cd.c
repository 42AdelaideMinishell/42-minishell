/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:06:09 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/04 17:33:51 by jlyu             ###   ########.fr       */
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

char	*join_dirs(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		k;

	i = ft_strlen(s1) + ft_strlen(s2);
	res = malloc((i + 1) * sizeof(char));
	if (res != NULL)
	{
		res[i] = '\0';
		k = 0;
		while (*s1)
		{
			res[k] = *s1;
			s1++;
			k++;
		}
		while (*s2)
		{
			res[k] = *s2;
			s2++;
			k++;
		}
		free(s1);
	}
	return (res);
}

static char	*update_cdm_args_back_util(char **dirs, int num)
{
	char	*bslash;
	char	*res;
	char	*tem;
	int		i;

	bslash = malloc(2 * sizeof(char));
	bslash[0] = '/';
	bslash[1] = '\0';
	if (num == 0)
		return (bslash);
	else
	{
		res = join_dirs(bslash, dirs[0]);
		i = 1;
		while (i < num)
		{
			tem = join_dirs(bslash, dirs[i]);
			res = join_dirs(res, tem);
			free(tem);
			i++;
		}
		return (res);
	}
}

static void	update_cdm_args_back(char **split_cmd, t_cmd *cmd_args)
{
	int		size_back;
	int		size_total;
	char	**dot;
	char	**dirs;

	dot = ft_split(split_cmd[1], '/');
	size_back = get_dot_num(dot);
	dirs = ft_split(++(cmd_args->abs_path), '/');
	size_total = get_dot_num(dirs);
	free(cmd_args->abs_path);
	if (size_total <= size_back)
		cmd_args->abs_path = update_cdm_args_back_util(dirs, 0);
	else
		cmd_args->abs_path = update_cdm_args_back_util(dirs, size_total - size_back);
	free_container(dot);
	free_container(dirs);
}

static void	update_cdm_args_for(char *cmd, t_cmd *cmd_args)
{
	char	*tem;

	if (cmd[0] == '/')
	{
		free(cmd_args->abs_path);
		cmd_args->abs_path = ft_strjoin("", cmd);
	}
	else
	{
		tem = ft_strjoin("/", cmd);
		cmd_args->abs_path = join_dirs(cmd_args->abs_path, tem);
		free(tem);
	}
}
// TODO
int	handle_cd(char **split_cmd, t_cmd *cmd_args)
{
	int		result;

	if (ft_strncmp(split_cmd[1], "~", sizeof(split_cmd[1])) == 0)
	{
		free(cmd_args->abs_path);
		cmd_args->abs_path = NULL;
		cmd_args->abs_path = ft_strjoin(cmd_args->home_path, "");
		return (0);
	}
	result = handle_else(split_cmd, cmd_args);
	if (result == -1)
		return (result);
	else if (ft_strncmp(split_cmd[1], "..", sizeof(split_cmd[1])) == 0
		|| ft_strncmp(split_cmd[1], "../", sizeof(split_cmd[1])) == 0)
		update_cdm_args_back(split_cmd, cmd_args);
	else if (ft_strncmp(split_cmd[1], ".", sizeof(split_cmd[1])) == 0);
	else
		update_cdm_args_for(split_cmd[1], cmd_args);
	return (result);
}