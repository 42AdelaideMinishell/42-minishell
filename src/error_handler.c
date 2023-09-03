#include "../inc/minishell.h"

void	argc_error(int argc)
{
	if (argc != 1)
		exit(1);
}

void	fork_error(pid_t pid)
{
	if (pid == -1)
		perror("fork error\n");
}
