/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utiles.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:36:17 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/16 20:45:47 by jaeshin          ###   ########.fr       */
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
		else if (ft_strncmp(cmd[i], "<", 2) == 0)
			return (SEND);
		else if (ft_strncmp(cmd[i], "<<", 3) == 0)
			return (SEND_DOC);
		i++;
	}
	return (0);
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

	fd = -1;
	if (condition == OVERWRITE)
		fd = open(get_filename(cmd), O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (condition == APPEND)
		fd = open(get_filename(cmd), O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (condition == SEND)
		fd = open(get_filename(cmd), O_RDONLY);
	open_error(fd);
	return (fd);
}
