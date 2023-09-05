/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:08:23 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/05 17:12:17 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// handles ctrl+c during operations
void	wait_child(int status)
{
	int	signal;

	if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGINT)
			ft_putendl_fd("^C", 2);
		else if (signal == SIGQUIT)
			ft_putendl_fd("^\\minishell: quit ", 2);
	}
}

void	handle_process(char *rl, t_cmd *cmd_args)
{
	pid_t	pid;
	pid_t	terminated_pid;
	int		status;
	int		fd[2];
	char	buffer[100];
	int 	i;

	i = 0;
	while (i < 100)
	{
		buffer[i] = '\0';
		i++;
	}
	if (pipe(fd) == -1)
	{
		perror("pipe");
	}
	pid = fork();
	fork_error(pid);
	if (pid == 0)
		execute(rl, cmd_args, fd);
	else if (pid > 0)
	{
		signal_ignore();
		terminated_pid = wait(&status);
		wait_child(status);
		if (terminated_pid == pid)
		{
			if (WIFEXITED(status))
				free(rl);
		}
		else
			perror("pid error\n");
		close(fd[1]);
		read(fd[0], buffer, 100);
		close(fd[0]);
		if (ft_strncmp(buffer, "null", 4) != 0)
		{
			if (ft_strncmp(buffer, "path", 4) == 0)
			{
				if (ft_strncmp(buffer, "pathkeep", 7) != 0)
				{
					char *tem = ft_strjoin(cmd_args->abs_path, "");
					free(cmd_args->abs_path);
					if (ft_strncmp(buffer, "pathpre", 7) == 0)
						cmd_args->abs_path = ft_strjoin(cmd_args->pre_path, "");
					else if (ft_strncmp(buffer, "path/", 5) == 0)
						cmd_args->abs_path = ft_strjoin(buffer + 4, "");
					cmd_args->pre_path = ft_strjoin(tem, "");
					free(tem);
				}
			}
			else if (ft_strncmp(buffer, "envp", 4) == 0)
				cmd_args->envp = NULL;
		}
	}
	init_signal();
}
