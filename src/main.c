#include "../inc/minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// init term control to not show ^C
void	new_term_init(void)
{
	struct termios	new_term;

	tcgetattr(STDIN_FILENO, &new_term);
	new_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

int main(void)
{
	char			*rl;
	struct termios	old_term;
	// pid_t			pid;

	// ctrl+c
	signal(SIGINT, signal_handler);
	// "ctrl+\"
	signal(SIGQUIT, SIG_IGN);

	// termios
	tcgetattr(STDIN_FILENO, &old_term);
	new_term_init();
	while (1)
	{
		rl = readline("✅ minishell $ ");
		// ctrl+d
		if (!rl)
			break ;
		if (rl[0] == '\0')
			continue ;
		add_history(rl);
		printf("You entered: %s\n", rl);
		free(rl);
	}
	// Gets back to original terminal setting
	tcsetattr(STDERR_FILENO, TCSANOW, &old_term);
	return (0);
}
