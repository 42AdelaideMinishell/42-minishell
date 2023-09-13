/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:24:20 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/13 14:41:26 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	run_shell(t_cmd *cmd_args)
{
	char	*rl;

	while (cmd_args->exit_flag)
	{
		rl = readline("🟢  4️⃣ 2️⃣ minishell % ");
		if (!rl)
			break ;
		if (rl[0] == '\0')
			continue ;
		add_history(rl);
		cmd_args->cmd = split_cmd(rl);
		cmd_args->p_re_count = count_pipe_redirection(cmd_args->cmd);
		cmd_args->cur_cmd = choose_cur_cmd(cmd_args->cmd, cmd_args->cmd_order);
		handle_process(rl, cmd_args);
		free_container(cmd_args->cmd);
		free_container(cmd_args->cur_cmd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	struct termios	o_term;
	t_cmd			*cmd_args;

	(void)argv;
	argc_error(argc);
	init_signal();
	// termios
	old_term(GET, &o_term);
	new_term();
	// Initial current working directory
	cmd_args = initial_cmd(envp);
	cmd_init_error(cmd_args);
	run_shell(cmd_args);
	// Gets back to original terminal setting
	old_term(SET, &o_term);
	free_container(cmd_args->envp);
	free(cmd_args);
	return (0);
}
