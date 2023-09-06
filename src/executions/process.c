/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:08:23 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/05 18:20:39 by jaeshin          ###   ########.fr       */
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

// void	child(char **argv, int *p_fd, char **envp)
// {
// 	dup2(p_fd[1], 1);
// 	close(p_fd[0]);
// 	execute(argv[2], envp);
// }

// void	parent(char **argv, int *p_fd, char **envp)
// {
// 	dup2(p_fd[0], 0);
// 	close(p_fd[1]);
// 	execute(argv[3], envp);
// }

int	count_cmd(char **split_cmd)
{
	int	i;

	i = 0;
	while (split_cmd[i] && ft_strncmp(split_cmd[i], "|", 2) != 0)
		i++;
	return (i);
}

int	separate_pipe_cmd(char **split_cmd, t_cmd *cmd_args, int i, int order)
{
	int	j;

	j = 0;
	if (order == 1)
	{
		cmd_args->cmd_one = malloc(sizeof(char *) * count_cmd(split_cmd));
		while (split_cmd[i] && ft_strncmp(split_cmd[i], "|", 2) != 0)
		{
			cmd_args->cmd_one[j] = ft_strdup(split_cmd[i]);
			i++;
			j++;
		}
	}
	else if (order == 2)
	{
		cmd_args->cmd_two = malloc(sizeof(char *) * count_cmd(split_cmd));
		while (split_cmd[i] && ft_strncmp(split_cmd[i], "|", 2) != 0)
		{
			cmd_args->cmd_two[j] = ft_strdup(split_cmd[i]);
			i++;
			j++;
		}
	}
	else if (order == 3)
	{
		cmd_args->cmd_three = malloc(sizeof(char *) * count_cmd(split_cmd));
		while (split_cmd[i] && ft_strncmp(split_cmd[i], "|", 2) != 0)
		{
			cmd_args->cmd_three[j] = ft_strdup(split_cmd[i]);
			i++;
			j++;
		}
	}
	return (i);
}

void	pipe_handle(char *rl, t_cmd *cmd_args)
{
	char	**split_cmd;
	int		i;
	int		order;

	i = 0;
	order = 1;
	split_cmd = space_quotes_split(rl);
	cmd_args->pipe_c = count_pipe(rl);
	while (cmd_args->pipe_c >= 0)
	{
		i += separate_pipe_cmd(split_cmd, cmd_args, i, order);
		order++;
		cmd_args->pipe_c--;
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
	pipe_handle(rl, cmd_args);
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
