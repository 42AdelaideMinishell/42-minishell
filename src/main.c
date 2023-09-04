#include "../inc/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*rl;
	struct termios	o_term;

	argc_error(argc);
	(void)argv;
	init_signal();
	// termios
	old_term(GET, &o_term);
	new_term();
	while (1)
	{
		rl = readline("🟢  4️⃣ 2️⃣ minishell % ");
		// ctrl+d
		if (!rl)
			break ;
		if (rl[0] == '\0')
			continue ;
		add_history(rl);
		// creates child pid to run the command and exits after wait
		handle_process(rl, envp);
	}
	// Gets back to original terminal setting
	old_term(SET, &o_term);
	return (0);
}
