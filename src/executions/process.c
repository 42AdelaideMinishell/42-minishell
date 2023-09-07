/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:08:23 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/07 13:45:25 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	child(t_cmd *cmd_args, int *p_fd)
{
	// int	fd;

	// fd = open_file("infile", 0);
	// printf("child %d\n", fd);
	printf("hello from second child\n");
	// dup2(fd, 0);
	if (cmd_args->pipe_c > 0)
	{
		dup2(p_fd[1], 1);
		close(p_fd[0]);
	}
	printf("child cmd %d\n", cmd_args->which_cmd);
	process_child(cmd_args);
}

void	parent(t_cmd *cmd_args, int *p_fd)
{
	// int	fd;

	// fd = open_file("outfile", 1);
	// printf("parent %d\n", fd);
	printf("hello from second parent\n");
	// dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	cmd_args->which_cmd++;
	printf("parent cmd %d\n", cmd_args->which_cmd);
	process_child(cmd_args);
}

void	another_child(t_cmd *cmd_args)
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
		printf("hello from first child\n");
		child(cmd_args, p_fd);
	}
	else if (pid > 0)
	{
		signal_ignore();
		terminated_pid = wait(&status);
		signal_interruped(status);
		if (terminated_pid == pid)
		{
			printf("hello from frist parent\n");
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

	cmd_by_pipe(rl, cmd_args);
	create_fork(&pid);
	if (pid == 0)
	{
		// Create a grandchild
		if (cmd_args->pipe_c > 0)
			another_child(cmd_args);
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
				process_parent(rl, cmd_args, status);
				free(rl);
			}
		}
		else
			perror("pid error\n");
	}
	free_all_cmd(cmd_args);
	init_signal();
}
