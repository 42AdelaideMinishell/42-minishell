#include "../../inc/minishell.h"

// tries to run the command, if it doesn't work, returns the error message.
void	execute(t_cmd *cmd_args, int *p_fd)
{
	char	**cmd;
	int		result;
	char	*tem;

	cmd = get_cmd(cmd_args);
	int i = 0;
	while (cmd[i])
	{
		printf("inside execute %s\n", cmd[i]);
		i++;
	}
	result = 0;
	if (ft_strncmp(cmd[0], "cd", sizeof(cmd[0])) == 0)
	{
		result = handle_cd(cmd, cmd_args);
		if (result == 1)
			exit(1);
		if (result == 0)
			tem = ft_strjoin("path", cmd_args->abs_path);
		else if (result == 2)
			tem = ft_strjoin("pathpre", "");
		else
			tem = ft_strjoin("pathkeep", "");
		close(p_fd[0]);
		write(p_fd[1], tem, ft_strlen(tem));
		close(p_fd[1]);
		free(tem);
		exit(0);
	}
	if (ft_strncmp(cmd[0], "unset", sizeof(cmd[0])) == 0
		&& ft_strncmp(cmd[1], "PATH", sizeof(cmd[0])) == 0)
	{
		tem = ft_strjoin("envp", "");
		close(p_fd[0]);
		write(p_fd[1], tem, ft_strlen(tem));
		close(p_fd[1]);
		free(tem);
		exit(0);
	}
	// close(p_fd[0]);
	// write(p_fd[1], "null", 4);
	// close(p_fd[1]);
	if (ft_strncmp(cmd[0], "pwd", sizeof(cmd[0])) == 0)
		printf("%s\n", cmd_args->abs_path);
	else
	{
		printf("hello from handling\n");
		result = handle_else(cmd, cmd_args);
	}
	result_error(result, cmd_args);
	exit(0);
}
