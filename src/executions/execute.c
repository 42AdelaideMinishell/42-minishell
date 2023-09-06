#include "../../inc/minishell.h"

char	**get_cmd(t_cmd *cmd_args)
{
	if (cmd_args->which_cmd == 0)
	{
		cmd_args->which_cmd++;
		return (cmd_args->cmd_one);
	}
	else if (cmd_args->which_cmd == 1)
	{
		cmd_args->which_cmd++;
		return (cmd_args->cmd_two);
	}
	else if (cmd_args->which_cmd == 2)
	{
		cmd_args->which_cmd++;
		return (cmd_args->cmd_three);
	}
	return (NULL);
}

// tries to run the command, if it doesn't work, returns the error message.
void	execute(t_cmd *cmd_args, int *fd)
{
	char	**cmd;
	int		result;
	char	*tem;

	cmd = get_cmd(cmd_args);
	int i = 0;
	while (cmd[i])
	{
		printf("%s\n", cmd[i]);
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
		close(fd[0]);
		write(fd[1], tem, ft_strlen(tem));
		close(fd[1]);
		free(tem);
		exit(0);
	}
	if (ft_strncmp(cmd[0], "unset", sizeof(cmd[0])) == 0
		&& ft_strncmp(cmd[1], "PATH", sizeof(cmd[0])) == 0)
	{
		tem = ft_strjoin("envp", "");
		close(fd[0]);
		write(fd[1], tem, ft_strlen(tem));
		close(fd[1]);
		free(tem);
		exit(0);
	}
	close(fd[0]);
	write(fd[1], "null", 4);
	close(fd[1]);
	if (ft_strncmp(cmd[0], "pwd", sizeof(cmd[0])) == 0)
		printf("%s\n", cmd_args->abs_path);
	else
		result = handle_else(cmd, cmd_args);
	result_error(result, cmd_args);
	exit(0);
}
