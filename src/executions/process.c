/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:08:23 by jaeshin           #+#    #+#             */
/*   Updated: 2023/09/06 18:17:13 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// handles ctrl+c during operations
void	wait_child(int status)
{
	int	signal;

	if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGINT)
			ft_putendl_fd("^C", 2);
		else if (signal == SIGQUIT)
			ft_putendl_fd("^\\minishell: quit ", 2);
	}
}

int	count_cmd(char **split_cmd)
{
	int	i;

	i = 0;
	while (split_cmd[i] && ft_strncmp(split_cmd[i], "|", 2) != 0)
		i++;
	return (i);
}

int	separate_pipe_cmd(char **split_cmd, t_cmd *cmd_args, int i, int cmd_nbr)
{
	int	j;

	j = 0;
	if (cmd_nbr == 1)
	{
		cmd_args->cmd_one = malloc(sizeof(char *) * (count_cmd(split_cmd) + 1));
		while (split_cmd[i] && ft_strncmp(split_cmd[i], "|", 2) != 0)
		{
			cmd_args->cmd_one[j] = ft_strdup(split_cmd[i]);
			i++;
			j++;
		}
		cmd_args->cmd_one[j] = NULL;
	}
	else if (cmd_nbr == 2)
	{
		i++;
		cmd_args->cmd_two = malloc(sizeof(char *) * (count_cmd(split_cmd) + 1));
		while (split_cmd[i] && ft_strncmp(split_cmd[i], "|", 2) != 0)
		{
			cmd_args->cmd_two[j] = ft_strdup(split_cmd[i]);
			i++;
			j++;
		}
		cmd_args->cmd_two[j] = NULL;
	}
	else if (cmd_nbr == 3)
	{
		i++;
		cmd_args->cmd_three = malloc(sizeof(char *) * (count_cmd(split_cmd) + 1));
		while (split_cmd[i] && ft_strncmp(split_cmd[i], "|", 2) != 0)
		{
			cmd_args->cmd_three[j] = ft_strdup(split_cmd[i]);
			i++;
			j++;
		}
		cmd_args->cmd_three[j] = NULL;
	}
	return (i);
}

void	cmd_by_pipe(char *rl, t_cmd *cmd_args)
{
	char	**split_cmd;
	int		i;
	int		cmd_nbr;

	split_cmd = space_quotes_split(rl);
	i = 0;
	cmd_nbr = 1;
	cmd_args->pipe_c = count_pipe(rl);
	while (cmd_args->pipe_c >= 0)
	{
		i += separate_pipe_cmd(split_cmd, cmd_args, i, cmd_nbr);
		cmd_nbr++;
		cmd_args->pipe_c--;
	}
	cmd_args->pipe_c = count_pipe(rl);
}

int	open_file(char *file, int in_out)
{
	int	fd;

	fd = 0;
	if (in_out == 0)
		fd = open(file, O_RDONLY, 0777);
	else if (in_out == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		exit(1);
	return (fd);
}

void	child(t_cmd *cmd_args, int *p_fd)
{
	int	fd;

	fd = open_file("infile", 0);
	printf("child %d\n", fd);
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	printf("hello from child\n");
	execute(cmd_args, p_fd);
}

void	parent(t_cmd *cmd_args, int *p_fd)
{
	int	fd;

	fd = open_file("outfile", 1);
	printf("parent %d\n", fd);
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	printf("hello from parent\n");
	execute(cmd_args, p_fd);
}

void	handle_pipe(t_cmd *cmd_args)
{
	int		p_fd[2];
	pid_t	pid;
	int		status;
	pid_t	terminated_pid;

	if (pipe(p_fd) == -1)
		exit(1);
	pid = fork();
	fork_error(pid);
	if (pid == 0)
	{
		printf("hello from child 1\n");
		child(cmd_args, p_fd);
	}
	else if (pid > 0)
	{
		terminated_pid = wait(&status);
		if (terminated_pid == pid)
		{
			printf("hello from parent 1\n");
			if (WIFEXITED(status))
				parent(cmd_args, p_fd);
		}
		else
			perror("pid error\n");
	}
}

void	handle_process(char *rl, t_cmd *cmd_args)
{
	pid_t	pid;
	pid_t	terminated_pid;
	int		status;
	int		fd[2];
	char	buffer[100];
	int 	i;

	i = 0;
	while (i < 100)
	{
		buffer[i] = '\0';
		i++;
	}
	if (pipe(fd) == -1)
		perror("pipe");
	cmd_by_pipe(rl, cmd_args);
	pid = fork();
	fork_error(pid);
	if (pid == 0)
	{
		handle_pipe(cmd_args);
	}
	else if (pid > 0)
	{
		signal_ignore();
		terminated_pid = wait(&status);
		wait_child(status);
		if (terminated_pid == pid)
		{
			if (WIFEXITED(status))
				free(rl);
		}
		else
			perror("pid error\n");
		close(fd[1]);
		read(fd[0], buffer, 100);
		close(fd[0]);
		if (ft_strncmp(buffer, "null", 4) != 0)
		{
			if (ft_strncmp(buffer, "path", 4) == 0)
			{
				if (ft_strncmp(buffer, "pathkeep", 7) != 0)
				{
					char *tem = ft_strjoin(cmd_args->abs_path, "");
					free(cmd_args->abs_path);
					if (ft_strncmp(buffer, "pathpre", 7) == 0)
						cmd_args->abs_path = ft_strjoin(cmd_args->pre_path, "");
					else if (ft_strncmp(buffer, "path/", 5) == 0)
						cmd_args->abs_path = ft_strjoin(buffer + 4, "");
					cmd_args->pre_path = ft_strjoin(tem, "");
					free(tem);
				}
			}
			else if (ft_strncmp(buffer, "envp", 4) == 0)
				cmd_args->envp = NULL;
		}
		printf("hello from main parent\n");
	}
	init_signal();
}
