/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:08:23 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/08 14:57:32 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	child(t_cmd *cmd_args, int *p_fd)
{
	close(p_fd[0]);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
	process_child(cmd_args);
}

void	parent(t_cmd *cmd_args, int *p_fd_f, int *p_fd_s)
{
	int tem[2] = {STDIN_FILENO, STDOUT_FILENO};

	if (cmd_args->pipe_c > 1)
	{
		close(p_fd_f[1]);
		dup2(p_fd_f[0], STDIN_FILENO);
		close(p_fd_f[0]);
		close(p_fd_s[0]);
		dup2(p_fd_s[1], STDOUT_FILENO);
		close(p_fd_s[1]);
	}
	else
	{
		close(p_fd_f[1]);
		dup2(p_fd_f[0], STDIN_FILENO);
		close(p_fd_f[0]);
	}
	process_child(cmd_args);
}

void	second_child(t_cmd *cmd_args, int *p_fd_s)
{
	int		p_fd_f[2];
	pid_t	pid;
	int		status;
	pid_t	terminated_pid;

	create_pipe(p_fd_f);
	create_fork(&pid);
	if (pid == 0)
	{
		child(cmd_args, p_fd_f);
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
				parent(cmd_args, p_fd_f, p_fd_s);
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
	create_fork(&pid);
	if (pid == 0)
	{
		second_child(cmd_args, p_fd);
	}
	else if (pid > 0)
	{
		signal_ignore();
		terminated_pid = wait(&status);
		signal_interruped(status);
		if (terminated_pid == pid)
		{
			cmd_args->which_cmd = 2;
			int tem[2] = {STDIN_FILENO, STDOUT_FILENO};
			if (WIFEXITED(status))
			{
				cmd_args->pipe_c = 1;
				parent(cmd_args, p_fd, tem);
			}
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
	if (pid == 0)
	{
		int tem[2] = {STDIN_FILENO, STDOUT_FILENO};
		if (cmd_args->pipe_c == 1)
			second_child(cmd_args, tem);
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
