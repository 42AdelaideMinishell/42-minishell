/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:24:20 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/19 11:04:15 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_up_cmd(t_cmd *cmd_args, char *rl)
{
	cmd_args->cmd = split_cmd(rl);
	cmd_args->p_re_count = count_pipe_redirection(cmd_args->cmd);
	cmd_args->cmd_order = 0;
	cmd_args->cur_cmd = choose_cur_cmd(cmd_args->cmd, cmd_args->cmd_order);
}

static char	*get_instruction(t_cmd *cmd_args)
{
	char	**path;
	int		size;
	char	*instruction;
	char	*tem;

	path = ft_split(cmd_args->abs_path, '/');
	size = 0;
	while (path[size])
		size++;
	if (size == 0)
		instruction = ft_strjoin("🟢  4️⃣ 2️⃣ minishell / % ", "");
	else
	{
		tem = ft_strjoin("🟢  4️⃣ 2️⃣ minishell ", path[size - 1]);
		instruction = ft_strjoin(tem, " % ");
		free(tem);
	}
	free_container(path);
	return (instruction);
}

static void	run_shell(t_cmd *cmd_args)
{
	char	*rl;
	char	*instruction;

	while (cmd_args->exit_flag)
	{
		instruction = get_instruction(cmd_args);
		rl = readline(instruction);
		free(instruction);
		if (!rl)
			break ;
		if (rl[0] == '\0')
			continue ;
		add_history(rl);
		set_up_cmd(cmd_args, rl);
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
	old_term(GET, &o_term);
	new_term();
	cmd_args = initial_cmd(envp);
	cmd_init_error(cmd_args);
	run_shell(cmd_args);
	old_term(SET, &o_term);
	free_container(cmd_args->envp);
	free(cmd_args);
	return (0);
}
