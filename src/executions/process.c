/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:08:23 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/18 16:06:58 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	single_cmd_redirection(t_cmd *cmd_args)
{
	if (cmd_args->p_re_count == 0)
		cmd_process(cmd_args);
	else if (get_redirection(cmd_args->cur_cmd))
	{
		if ((cmd_args->p_re_count - 1) == 0)
			cmd_process(cmd_args);
	}
}

void	run_child(t_cmd *cmd_args, int *p_fd)
{
	if (cmd_args->cmd_order < cmd_args->p_re_count)
	{
		close(p_fd[0]);
		dup2(p_fd[1], STDOUT_FILENO);
	}
	cmd_process(cmd_args);
}

void	run_parent(t_cmd *cmd_args, int *p_fd)
{
	cmd_args->cmd_order++;
	if (cmd_args->cmd_order <= cmd_args->p_re_count)
	{
		close(p_fd[1]);
		dup2(p_fd[0], STDIN_FILENO);
	}
	if (get_redirection(cmd_args->cur_cmd))
		cmd_args->p_re_count--;
}

// handles redirections and pipes
void	handle_pipe_redirection(t_cmd *cmd_args)
{
	int		p_fd[2];
	pid_t	pid;
	int		status;

	single_cmd_redirection(cmd_args);
	while (cmd_args->cur_cmd && cmd_args->cmd_order <= cmd_args->p_re_count)
	{
		cmd_args->cur_cmd = choose_cur_cmd(cmd_args->cmd, cmd_args->cmd_order);
		create_pipe(p_fd);
		create_fork(&pid);
		if (pid == 0)
			run_child(cmd_args, p_fd);
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			run_parent(cmd_args, p_fd);
		}
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
		handle_pipe_redirection(cmd_args);
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
	}
	init_signal();
}
