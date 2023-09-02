#include "../inc/minishell.h"

void	handle_process(char *rl, char **envp)
{
	pid_t	pid;
	pid_t	terminated_pid;
	int		status;

	pid = fork();
	if (pid == -1)
		perror("fork error\n");
	if (pid == 0)
		execute(rl, envp);
	else if (pid > 0)
	{
		terminated_pid = wait(&status);
		if (terminated_pid == pid)
		{
			if (WIFEXITED(status))
				free(rl);
		}
		else
			perror("pid error\n");
	}
}
