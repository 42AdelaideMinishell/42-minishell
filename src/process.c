#include "../inc/minishell.h"

// handles ctrl+c during operations
void	wait_child(int status)
{
	int	signal;

	if (WIFSIGNALED(status))
	{
		// WTERMSIG to figure out which signal has been received
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

	pid = fork();
	fork_error(pid);
	if (pid == 0)
		execute(rl, cmd_args);
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
	}
	init_signal();
}
