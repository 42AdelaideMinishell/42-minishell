/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:08:20 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/04 15:08:21 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	argc_error(int argc)
{
	if (argc != 1)
		exit(1);
}

void	fork_error(pid_t pid)
{
	if (pid == -1)
		perror("fork error\n");
}
