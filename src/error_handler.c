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

void	result_error(int result, char **split_cmd)
{
	if (result == -1)
	{
		ft_putstr_fd("🔴  4️⃣ 2️⃣ minishell: command not found: ", 2);
		ft_putendl_fd(split_cmd[0], 2);
		free_container(split_cmd);
		exit(1);
	}
}