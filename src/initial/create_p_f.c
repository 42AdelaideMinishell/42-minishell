/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_p_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:00:10 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/06 16:03:54 by jlyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	create_pipe(int *fd)
{
	if (pipe(fd) == -1)
		perror("pipe");
}

void	create_fork(pid_t *pid)
{
	*pid = fork();
	fork_error(*pid);
}
