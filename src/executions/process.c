/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:08:23 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/06 16:12:11 by jlyu             ###   ########.fr       */
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

	create_pipe(fd);
	pipe_handle(rl, cmd_args);
	create_fork(&pid);
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
		process_parent(cmd_args, fd);
	}
	init_signal();
}
