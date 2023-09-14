/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:16:35 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/14 16:25:57 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redirection(t_cmd *cmd_args)
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
}

// > a needs to be handled
void	overwrite(t_cmd *cmd_args)
{
	char 	buffer[BUFFER_SIZE];
	int		bytes;
	int 	fd;

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
	char 	buffer[BUFFER_SIZE];
	int		bytes;
	int 	fd;

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
	char 	buffer[BUFFER_SIZE];
	int		bytes;
	int 	fd;

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
	char 	buffer[BUFFER_SIZE];
	int		bytes;

	bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		if ((ft_strncmp(buffer, cmd_args->cur_cmd[1], ft_strlen(cmd_args->cur_cmd[1])) == 0)
			&& (buffer[ft_strlen(cmd_args->cur_cmd[1])] == '\n'))
			break ;
		write(STDOUT_FILENO, buffer, bytes);
		bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
	}
	if (bytes == -1)
		perror("read bytes\n");
	exit(0);
}

// void	edit_cmd(char **cmd)
// {
// 	int	i;
// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if ((ft_strncmp(cmd[i], ">", 2) == 0)
// 			|| (ft_strncmp(cmd[i], "<", 2) == 0)
// 			|| (ft_strncmp(cmd[i], ">>", 3) == 0)
// 			|| (ft_strncmp(cmd[i], "<<", 3) == 0))
// 			cmd[i] = NULL;
// 		i++;
// 	}
// }