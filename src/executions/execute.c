#include "../../inc/minishell.h"

// tries to run the command, if it doesn't work, returns the error message.
void	execute(char *cmd, t_cmd *cmd_args, int *fd)
{
	char	**split_cmd;
	int		result;
	char	*tem;

	split_cmd = space_quotes_split(rl);
	result = 0;
	if (ft_strncmp(split_cmd[0], "cd", sizeof(split_cmd[0])) == 0)
	{
		result = handle_cd(split_cmd, cmd_args);
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
	if (ft_strncmp(split_cmd[0], "unset", sizeof(split_cmd[0])) == 0
		&& ft_strncmp(split_cmd[1], "PATH", sizeof(split_cmd[0])) == 0)
	{
//<<<<<<< jlyu
		tem = ft_strjoin("envp", "");
		close(fd[0]);
		write(fd[1], tem, ft_strlen(tem));
		close(fd[1]);
		free(tem);
		exit(0);
//=======
		//printf("%s\n", cmd_args->envp[0]);
//		result = handle_else(cmd_args);
//>>>>>>> main
	}
	close(fd[0]);
	write(fd[1], "null", 4);
	close(fd[1]);
	if (ft_strncmp(split_cmd[0], "pwd", sizeof(split_cmd[0])) == 0)
		printf("%s\n", cmd_args->abs_path);
	else
		result = handle_else(split_cmd, cmd_args);
	result_error(result, split_cmd);
	// exit(0);
}
