/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:11:06 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/19 09:57:31 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*dollar_cmd_util(char *cmd, t_cmd *cmd_args, char *tem)
{
	int		i;
	int		j;
	char	*sub;

	if (*tem)
	{
		i = 0;
		while (cmd_args->envp[i])
		{
			j = 0;
			while (cmd_args->envp[i][j] && cmd_args->envp[i][j] != '=')
				j++;
			sub = ft_substr(cmd_args->envp[i], 0, j);
			if (ft_strncmp(tem, sub, ft_strlen(tem)) == 0)
			{
				free(sub);
				return (cmd_args->envp[i] + j + 1);
			}
			free(sub);
			i++;
		}
		return ("");
	}
	return (cmd);
}

static char	*dollar_cmd(char *cmd, t_cmd *cmd_args)
{
	char	*tem;

	tem = cmd;
	while (*tem)
	{
		if (*tem == '\'' && *(tem + 1) == '$')
		{
			printf("%s\n", (tem + 1));
			exit(0);
		}
		if (*tem == '$' && *(tem + 1) != '\0')
		{
			tem++;
			break ;
		}
		tem++;
	}
	return (dollar_cmd_util(cmd, cmd_args, tem));
}

void	process_echo(char **split_cmd, t_cmd *cmd_args)
{
	int	i;

	i = -1;
	while (split_cmd[++i])
		split_cmd[i] = dollar_cmd(split_cmd[i], cmd_args);
}
