/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:24:20 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/07 16:37:56 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	run_shell(t_cmd *cmd_args)
{
	char	*rl;

	while (1)
	{
		rl = readline("🟢  4️⃣ 2️⃣ minishell % ");
		if (!rl)
			break ;
		if (rl[0] == '\0')
			continue ;
		add_history(rl);
		cmd_by_pipe(rl, cmd_args);
		// creates child pid to run the command and exits after wait
		handle_process(rl, cmd_args);
	}
}

int	main(int argc, char **argv, char **envp)
{
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
	run_shell(cmd_args);
	// Gets back to original terminal setting
	old_term(SET, &o_term);
	free(cmd_args);
	return (0);
}
