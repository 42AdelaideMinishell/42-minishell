/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:16:35 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/18 16:27:05 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	redirection(t_cmd *cmd_args)
{
	int	condition;

	condition = get_redirection(cmd_args->cur_cmd);
	if (condition == OVERWRITE)
		overwrite(cmd_args);
	else if (condition == APPEND)
		append(cmd_args);
	else if (condition == SEND)
		send(cmd_args);
	else if (condition == SEND_DOC)
		send_doc(cmd_args);
	return (condition);
}

void	overwrite(t_cmd *cmd_args)
{
	char	buffer[BUFFER_SIZE];
	int		bytes;
	int		fd;

	fd = open_helper(cmd_args->cur_cmd, OVERWRITE);
	bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		write(fd, buffer, bytes);
		bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
	}
	close(fd);
	exit(0);
}

void	append(t_cmd *cmd_args)
{
	char	buffer[BUFFER_SIZE];
	int		bytes;
	int		fd;

	fd = open_helper(cmd_args->cur_cmd, APPEND);
	bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		write(fd, buffer, bytes);
		bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
	}
	close(fd);
	exit(0);
}

void	send(t_cmd *cmd_args)
{
	char	buffer[BUFFER_SIZE];
	int		bytes;
	int		fd;

	fd = open_helper(cmd_args->cur_cmd, SEND);
	bytes = read(fd, buffer, BUFFER_SIZE - 1);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		write(STDOUT_FILENO, buffer, bytes);
		bytes = read(fd, buffer, BUFFER_SIZE - 1);
	}
	close(fd);
	exit(0);
}

void	send_doc(t_cmd *cmd_args)
{
	char	buffer[BUFFER_SIZE];
	char	*chunk;
	int		bytes;

	bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
	chunk = malloc(1);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		if ((ft_strncmp(buffer, cmd_args->cur_cmd[1], \
			ft_strlen(cmd_args->cur_cmd[1])) == 0)
			&& (buffer[ft_strlen(cmd_args->cur_cmd[1])] == '\n'))
			break ;
		chunk = ft_strjoin(chunk, buffer);
		bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
	}
	if (bytes == -1)
		perror("read bytes\n");
	if (cmd_args->cmd_order == cmd_args->p_re_count)
		write(STDIN_FILENO, chunk, BUFFER_SIZE);
	else
		write(STDOUT_FILENO, chunk, BUFFER_SIZE);
	exit(0);
}
