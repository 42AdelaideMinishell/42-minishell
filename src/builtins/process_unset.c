/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:17:30 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/08 15:17:32 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	process_unset(char **split_cmd, t_cmd *cmd_args)
{
	char	*tem;
	int		i;
	int		size;
	char	**res;

	tem = ft_strjoin(split_cmd[1], "=");
	size = -1;
	while (cmd_args->envp[++size]);
	i = 0;
	while (cmd_args->envp[i])
	{
		if (ft_strncmp(cmd_args->envp[i], tem, ft_strlen(tem)) == 0)
			break ;
		i++;
	}
	if (i <= size)
	{
		res = malloc(size * sizeof(char *));
		size = -1;
		while (cmd_args->envp[++size])
		{
			if ( size == i)
				res[size] = ft_strjoin(tem, "");
			else
				res[size] = ft_strjoin(cmd_args->envp[size], "");
		}
		res[size] = NULL;
		free_container(cmd_args->envp);
		cmd_args->envp = res;
	}
	free(tem);
}