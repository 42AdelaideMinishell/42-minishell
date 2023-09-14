/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:08:23 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/14 12:27:57 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//void	child(t_cmd *cmd_args, int *pipe_one)
//{
//	close(pipe_one[0]);
//	dup2(pipe_one[1], STDOUT_FILENO);
//	close(pipe_one[1]);
//	one_cmd_process(cmd_args);
//}

//void	parent(t_cmd *cmd_args, int *pipe_one, int *pipe_two)
//{
//	//(void)pipe_two;
//	if (cmd_args->pipe_c == 1)
//	{
//		close(pipe_one[1]);
//		dup2(pipe_one[0], STDIN_FILENO);
//		close(pipe_one[0]);
//	}
//	else
//	{
//		close(pipe_one[1]);
//		dup2(pipe_one[0], STDIN_FILENO);
//		close(pipe_one[0]);
//		close(pipe_two[0]);
//		dup2(pipe_two[1], STDOUT_FILENO);
//		close(pipe_two[1]);
//	}
//	one_cmd_process(cmd_args);
//}

//void	two_cmd_process(t_cmd *cmd_args, int *pipe_two)
//{
//	int		pipe_one[2];
//	pid_t	pid;
//	int		status;
//	pid_t	terminated_pid;

//	create_pipe(pipe_one);
//	create_fork(&pid);
//	if (pid == 0)
//		child(cmd_args, pipe_one);
//	else if (pid > 0)
//	{
//		ignore_signal();
//		terminated_pid = wait(&status);
//		signal_interruped(status);
//		if (terminated_pid == pid)
//		{
//			cmd_args->which_cmd = 1;
//			if (WIFEXITED(status))
//				parent(cmd_args, pipe_one, pipe_two);
//		}
//		else
//			perror("pid error\n");
//	}
//	exit(0);
//}

//void	three_cmd_process(t_cmd *cmd_args)
//{
//	int		pipe[2];
//	pid_t	pid;
//	int		status;
//	pid_t	terminated_pid;

//	create_pipe(pipe);
//	create_fork(&pid);
//	if (pid == 0)
//		two_cmd_process(cmd_args, pipe);
//	else if (pid > 0)
//	{
//		ignore_signal();
//		terminated_pid = wait(&status);
//		signal_interruped(status);
//		if (terminated_pid == pid)
//		{
//			cmd_args->which_cmd = 2;
//			cmd_args->pipe_c = 1;
//			if (WIFEXITED(status))
//				parent(cmd_args, pipe, NULL);
//		}
//		else
//			perror("pid error\n");
//	}
//	exit(0);
//}

// handles redirections and pipes
// TODO - find a better way to handle pipes and redirection
void	handle_pipe_redirection(t_cmd *cmd_args)
{
	int		pipe[2];
	pid_t	pid;
	int		status;
	pid_t	terminated_pid;

	if (cmd_args->p_re_count == 0)
		cmd_process(cmd_args);
	else if (cmd_args->cmd_order < cmd_args->p_re_count)
	{
		cmd_args->cmd_order++;
		create_pipe(pipe);
		create_fork(&pid);
		if (pid == 0)
			cmd_process(cmd_args);
		else if (pid > 0)
		{
			ignore_signal();
			terminated_pid = wait(&status);
			signal_interruped(status);
			if (terminated_pid == pid)
			{
				if (WIFEXITED(status))
					cmd_process(cmd_args);
			}
			else
				perror("pid error\n");
		}
	}
	exit(0);
}

// ----------------------------------------------------------

void	handle_process(char *rl, t_cmd *cmd_args)
{
	pid_t	pid;
	pid_t	terminated_pid;
	int		status;

	create_fork(&pid);
	if (pid == 0)
		if (cmd_args->p_re_count > 0)
			redirection(cmd_args);
		else
			cmd_process(cmd_args);
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
