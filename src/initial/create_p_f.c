/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_p_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:00:10 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/16 18:44:08 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	create_pipe(int *p_fd)
{
	if (pipe(p_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

void	create_fork(pid_t *pid)
{
	*pid = fork();
	fork_error(*pid);
}
