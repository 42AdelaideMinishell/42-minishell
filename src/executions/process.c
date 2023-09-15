/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:08:23 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/15 17:01:12 by jaeshin          ###   ########.fr       */
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
void	handle_pipe_redirection(t_cmd *cmd_args)
{
	int		p_fd[2];
	int		p_fd_2[2];
	pid_t	pid;
	int		status;
	pid_t	terminated_pid;

	create_pipe(p_fd);
	create_pipe(p_fd_2);
	if (cmd_args->p_re_count == 0)
		cmd_process(cmd_args);
	while (cmd_args->cur_cmd && *(cmd_args->cmd_order) < cmd_args->p_re_count)
	{
		cmd_args->cur_cmd = choose_cur_cmd(cmd_args->cmd, cmd_args->cmd_order);
		cmd_args->cmd_order++;
		printf("order - %d\n", *(cmd_args->cmd_order));
		create_fork(&pid);
		if (pid == 0)
		{
			if ((cmd_args->cmd_order - 1) == 0)
			{
				close(p_fd[0]);
				dup2(p_fd[1], STDOUT_FILENO);
				cmd_process(cmd_args);
			}
			else if (*(cmd_args->cmd_order) < cmd_args->p_re_count)
			{
				close(p_fd_2[0]);
				dup2(p_fd_2[1], STDOUT_FILENO);
				cmd_process(cmd_args);
			}
			else
				exit(0);
		}
		else if (pid > 0)
		{
			cmd_args->cur_cmd = choose_cur_cmd(cmd_args->cmd, cmd_args->cmd_order);
			ignore_signal();
			terminated_pid = wait(&status);
			signal_interruped(status);
			if (terminated_pid == pid)
			{
				if (WIFEXITED(status))
				{
					if (cmd_args->p_re_count == 1)
					{
						printf("parent order - %d\n", *(cmd_args->cmd_order));
						printf("last cmd1 - %s\n", cmd_args->cur_cmd[0]);
						close(p_fd[1]);
						dup2(p_fd[0], STDIN_FILENO);
					}
					else if (*(cmd_args->cmd_order) == cmd_args->p_re_count)
					{
						printf("parent order - %d\n", *(cmd_args->cmd_order));
						printf("last cmd2 - %s\n", cmd_args->cur_cmd[0]);
						close(p_fd_2[1]);
						dup2(p_fd_2[0], STDIN_FILENO);
					}
					else
					{
						printf("parent order - %d\n", *(cmd_args->cmd_order));
						printf("last cmd3 - %s\n", cmd_args->cur_cmd[0]);
						close(p_fd[1]);
						dup2(p_fd[0], STDIN_FILENO);
						close(p_fd_2[0]);
						dup2(p_fd_2[1], STDOUT_FILENO);
					}
					cmd_process(cmd_args);
				}
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
