/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overwrite_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:01:55 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/13 17:07:44 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_redirection(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], ">", 2) == 0)
			return (OVERWRITE);
		else if (ft_strncmp(cmd[i], ">>", 3) == 0)
			return (APPEND);
		i++;
	}
	perror("getting redirection\n");
	return (-1);
}

void	edit_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ((ft_strncmp(cmd[i], ">", 2) == 0)
			|| (ft_strncmp(cmd[i], "<", 2) == 0)
			|| (ft_strncmp(cmd[i], ">>", 3) == 0)
			|| (ft_strncmp(cmd[i], "<<", 3) == 0))
			cmd[i] = NULL;
		i++;
	}
}

char	*get_filename(char **cmd)
{
	char	*filename;
	int		i;

	i = 0;
	while (cmd[i])
	{
		if ((ft_strncmp(cmd[i], ">", 2) == 0)
			|| (ft_strncmp(cmd[i], "<", 2) == 0)
			|| (ft_strncmp(cmd[i], ">>", 3) == 0)
			|| (ft_strncmp(cmd[i], "<<", 3) == 0))
			filename = cmd[i + 1];
		i++;
	}
	return (filename);
}

int	open_helper(char **cmd, int condition)
{
	int	fd;

	if (condition == OVERWRITE)
	{
		fd = open(get_filename(cmd), O_CREAT | O_RDWR | O_TRUNC, 0644);
		open_error(fd);
	}
	else
	{
		fd = open(get_filename(cmd), O_CREAT | O_RDWR | O_APPEND, 0644);
		open_error(fd);
	}
	return (fd);
}

// > a needs to be handled
void	overwrite_append(t_cmd *cmd_args)
{
	pid_t	pid;
	int		p_fd[2];
	int		status;
	pid_t	terminated_pid;
	char 	buffer[BUFFER_SIZE];
	int		bytes;
	int 	fd;
	
	fd = open_helper(cmd_args->cur_cmd, get_redirection(cmd_args->cur_cmd));
	pipe(p_fd);
	pid = fork();
	if (pid == 0)
	{
		edit_cmd(cmd_args->cur_cmd);
		close(p_fd[0]);
		dup2(p_fd[1], STDOUT_FILENO);
		cmd_process(cmd_args);
	}
	else if (pid > 0)
	{
		ignore_signal();
		terminated_pid = wait(&status);
		signal_interruped(status);
		if (terminated_pid == pid)
		{
			close(p_fd[1]);
			dup2(p_fd[0], STDIN_FILENO);
			bytes = read(p_fd[0], buffer, BUFFER_SIZE - 1);
			while (bytes > 0)
			{
				buffer[bytes] = '\0';
				write(fd, buffer, bytes);
				bytes = read(p_fd[0], buffer, BUFFER_SIZE - 1);
			}
			close(fd);
		}
		else
			perror("pid error\n");
	}
	exit(0);
}
