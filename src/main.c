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

void	input_check(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == EOF)
			exit(0);
		i++;
	}
}

int main(void)
{
	// signal
	// ctrl+c
	signal(SIGINT, signal_handler);
	// ctrl+\""
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		g_input = readline("minishell > ");
		// ctrl+d
		if (!g_input)
			exit(0);
		printf("You entered: %s\n", g_input);
		add_history(g_input);
	}
	return (0);
}
