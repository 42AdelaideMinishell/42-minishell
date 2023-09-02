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

void	init_signal(void)
{
	// ctrl+c
	signal(SIGINT, signal_handler);
	// "ctrl+\"
	signal(SIGQUIT, SIG_IGN);
}
