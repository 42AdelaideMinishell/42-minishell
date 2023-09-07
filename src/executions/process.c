/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:08:23 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/07 18:07:24 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	child(t_cmd *cmd_args, int *p_fd)
{
	// int	fd;

	// fd = open_file("infile", 0);
	// dup2(fd, 0);
	close(p_fd[0]);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
	process_child(cmd_args);
}

// Todo
void	parent(t_cmd *cmd_args, int *p_fd)
{
	// int	fd;

	// fd = open_file("outfile", 1);
	// dup2(fd, 1);
	if (cmd_args->pipe_c > 1)
	{
		close(p_fd[0]);
		dup2(p_fd[1], STDOUT_FILENO);
		close(p_fd[1]);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], STDIN_FILENO);
		close(p_fd[0]);
	}
	process_child(cmd_args);
}

void	second_child(t_cmd *cmd_args)
{
	int		p_fd[2];
	pid_t	pid;
	int		status;
	pid_t	terminated_pid;

	if (pipe(p_fd) == -1)
		exit(1);
	pid = fork();
	fork_error(pid);
	if (pid == 0)
	{
		child(cmd_args, p_fd);
	}
	else if (pid > 0)
	{
		signal_ignore();
		terminated_pid = wait(&status);
		signal_interruped(status);
		if (terminated_pid == pid)
		{
			cmd_args->which_cmd = 1;
			if (WIFEXITED(status))
				parent(cmd_args, p_fd);
		}
		else
			perror("pid error\n");
	}
	exit(0);
}

void	third_child(t_cmd *cmd_args)
{
	int		p_fd[2];
	pid_t	pid;
	int		status;
	pid_t	terminated_pid;

	create_pipe(p_fd);
	pid = fork();
	fork_error(pid);
	if (pid == 0)
	{
		second_child(cmd_args);
	}
	else if (pid > 0)
	{
		signal_ignore();
		terminated_pid = wait(&status);
		signal_interruped(status);
		if (terminated_pid == pid)
		{
			cmd_args->which_cmd = 2;
			if (WIFEXITED(status))
				parent(cmd_args, p_fd);
		}
		else
			perror("pid error\n");
	}
	exit(0);
}

void	handle_process(char *rl, t_cmd *cmd_args)
{
	pid_t	pid;
	pid_t	terminated_pid;
	int		status;

	create_fork(&pid);
	cmd_by_pipe(rl, cmd_args);
	if (pid == 0)
	{
		if (cmd_args->pipe_c == 1)
			second_child(cmd_args);
		else if (cmd_args->pipe_c == 2)
			third_child(cmd_args);
		else
			process_child(cmd_args);
	}
	else if (pid > 0)
	{
		signal_ignore();
		terminated_pid = wait(&status);
		signal_interruped(status);
		if (terminated_pid == pid)
		{
			if (WIFEXITED(status))
			{
				process_parent(cmd_args, status);
				free(rl);
			}
		}
		else
			perror("pid error\n");
	}
	free_all_cmd(cmd_args);
	init_signal();
}
