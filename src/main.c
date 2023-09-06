#include "../inc/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char			*rl;
	struct termios	o_term;
	t_cmd			*cmd_args;

	argc_error(argc);
	(void)argv;
	init_signal();
	// termios
	old_term(GET, &o_term);
	new_term();
	// Initial current working directory
	cmd_args = initial_cmd(envp);
	if (cmd_args == NULL)
	{
		perror("malloc");
		exit(1);
	}
	while (1)
	{
		rl = readline("🟢  4️⃣ 2️⃣ minishell % ");
		if (!rl)
			break ;
		if (rl[0] == '\0')
			continue ;
		add_history(rl);
		// creates child pid to run the command and exits after wait
		handle_process(rl, cmd_args);
	}
	// Gets back to original terminal setting
	old_term(SET, &o_term);
	free(cmd_args);
	return (0);
}
