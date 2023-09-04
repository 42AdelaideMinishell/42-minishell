#include "../../inc/minishell.h"

// tries to run the command, if it doesn't work, returns the error message.
void	execute(char *cmd, t_cmd *cmd_args)
{
	char	**split_cmd;
	int		result;

	split_cmd = space_quotes_split(cmd);
	result = 0;
	if (ft_strncmp(split_cmd[0], "cd", sizeof(split_cmd[0])) == 0)
		result = handle_cd(split_cmd, cmd_args);
	// PWD edit can be here
	else if (ft_strncmp(split_cmd[0], "pwd", sizeof(split_cmd[0])) == 0)
		printf("%s\n", cmd_args->abs_path);
	else if (ft_strncmp(split_cmd[0], "unset", sizeof(split_cmd[0])) == 0
		&& ft_strncmp(split_cmd[1], "PATH", sizeof(split_cmd[0])) == 0)
		cmd_args->envp = NULL;
	else
	{
		//printf("%s\n", cmd_args->envp[0]);
		result = handle_else(split_cmd, cmd_args);
	}
	result_error(result, split_cmd);
	exit(0);
}
