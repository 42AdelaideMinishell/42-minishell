#include "../inc/minishell.h"

int main(void)
{
	int i;
	char *input = readline("minishell > ");

	i = 0;
    printf("You entered: %s\n", input);
	add_history(input);
	while (i < 3)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		printf("\n");
		i++;
	}
    free(input);
	return (0);
}
