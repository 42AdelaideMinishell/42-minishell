/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:08:20 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/18 16:23:09 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	open_error(int fd)
{
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
}

void	argc_error(int argc)
{
	if (argc != 1)
		exit(1);
}

void	cmd_init_error(t_cmd *cmd_args)
{
	if (cmd_args == NULL)
	{
		perror("malloc");
		exit(1);
	}
}

void	fork_error(pid_t pid)
{
	if (pid == -1)
		perror("fork error\n");
}

void	result_error(int result, t_cmd *cmd_args)
{
	if (result == -1)
	{
		ft_putstr_fd("🔴  4️⃣ 2️⃣ minishell: command not found: ", 2);
		ft_putendl_fd(cmd_args->cur_cmd[0], 2);
		exit(1);
	}
}
