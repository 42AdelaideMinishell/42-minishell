/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:08:23 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/08 23:45:17 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	child(t_cmd *cmd_args, int *pipe_one)
{
	close(pipe_one[0]);
	dup2(pipe_one[1], STDOUT_FILENO);
	close(pipe_one[1]);
	one_cmd_process(cmd_args);
}

void	parent(t_cmd *cmd_args, int *pipe_one, int *pipe_two)
{
	if (cmd_args->pipe_c == 2)
	{
		close(pipe_one[1]);
		dup2(pipe_one[0], STDIN_FILENO);
		close(pipe_one[0]);
		close(pipe_two[0]);
		dup2(pipe_two[1], STDOUT_FILENO);
		close(pipe_two[1]);
	}
	else
	{
		close(pipe_one[1]);
		dup2(pipe_one[0], STDIN_FILENO);
		close(pipe_one[0]);
	}
	one_cmd_process(cmd_args);
}

void	two_cmd_process(t_cmd *cmd_args, int *pipe_two)
{
	int		pipe_one[2];
	pid_t	pid;
	int		status;
	pid_t	terminated_pid;

	create_pipe(pipe_one);
	create_fork(&pid);
	if (pid == 0)
		child(cmd_args, pipe_one);
	else if (pid > 0)
	{
		ignore_signal();
		terminated_pid = wait(&status);
		signal_interruped(status);
		if (terminated_pid == pid)
		{
			cmd_args->which_cmd = 1;
			if (WIFEXITED(status))
				parent(cmd_args, pipe_one, pipe_two);
		}
		else
			perror("pid error\n");
	}
	exit(0);
}

void	three_cmd_process(t_cmd *cmd_args)
{
	int		pipe[2];
	pid_t	pid;
	int		status;
	pid_t	terminated_pid;

	create_pipe(pipe);
	create_fork(&pid);
	if (pid == 0)
		two_cmd_process(cmd_args, pipe);
	else if (pid > 0)
	{
		ignore_signal();
		terminated_pid = wait(&status);
		signal_interruped(status);
		if (terminated_pid == pid)
		{
			cmd_args->which_cmd = 2;
			cmd_args->pipe_c = 1;
			if (WIFEXITED(status))
				parent(cmd_args, pipe, NULL);
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
		if (cmd_args->pipe_c == 0)
			one_cmd_process(cmd_args);
		else if (cmd_args->pipe_c == 1)
			two_cmd_process(cmd_args, NULL);
		else
			three_cmd_process(cmd_args);
	}
	else if (pid > 0)
	{
		ignore_signal();
		terminated_pid = wait(&status);
		signal_interruped(status);
		if (terminated_pid == pid)
		{
			free(rl);
			if (WIFEXITED(status))
				process_parent(cmd_args, status);
		}
		else
			perror("pid error\n");
	}
	free_all_cmd(cmd_args);
	init_signal();
}
