/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:22:29 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/06 15:23:06 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_cd(char **split_cmd, t_cmd *cmd_args, int *fd)
{
	int		result;
	char	*tem;

	result = handle_cd(split_cmd, cmd_args);
	if (result == 1)
		exit(1);
	if (result == 0)
		tem = ft_strjoin("path", cmd_args->abs_path);
	else if (result == 2)
		tem = ft_strjoin("pathpre", "");
	else
		tem = ft_strjoin("pathkeep", "");
	close(fd[0]);
	write(fd[1], tem, ft_strlen(tem));
	close(fd[1]);
	free(tem);
	exit(0);
}

void	execute_unset(int *fd)
{
	char	*tem;

	tem = ft_strjoin("envp", "");
	close(fd[0]);
	write(fd[1], tem, ft_strlen(tem));
	close(fd[1]);
	free(tem);
	exit(0);
}

// tries to run the command, if it doesn't work, returns the error message.
void	execute(char *rl, t_cmd *cmd_args, int *fd)
{
	char	**split_cmd;
	int		result;

	split_cmd = space_quotes_split(rl);
	if (ft_strncmp(split_cmd[0], "cd", sizeof(split_cmd[0])) == 0)
		execute_cd(split_cmd, cmd_args, fd);
	if (ft_strncmp(split_cmd[0], "unset", sizeof(split_cmd[0])) == 0
		&& ft_strncmp(split_cmd[1], "PATH", sizeof(split_cmd[0])) == 0)
		execute_unset(fd);
	close(fd[0]);
	write(fd[1], "null", 4);
	close(fd[1]);
	if (ft_strncmp(split_cmd[0], "pwd", sizeof(split_cmd[0])) == 0)
	{
		if (split_cmd[1] == NULL)
			printf("%s\n", cmd_args->abs_path);
		else
			printf("pwd: too many arguments\n");
		exit(0);
	}
	result = handle_else(cmd_args);
	result_error(result, split_cmd);
}
