/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:33:08 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/07 13:45:15 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <termios.h>
# include <termcap.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd {
	char	*home_path;
	char	*abs_path;
	char	*pre_path;
	char	**envp;
	int		pipe_c;
	int		which_cmd;
	char	**cmd_one;
	char	**cmd_two;
	char	**cmd_three;
}	t_cmd;

// Terminal control attributes
# define GET 1
# define SET 2

// Commands by pipes
# define FIRST 1
# define SECOND 2
# define THIRD 3

/* ------------------------------------------------------------ */

// Initial command
t_cmd	*initial_cmd(char **envp);

// Path
char	*find_path(char *name, char **envp);
char	*get_path(char *cmd, char **envp);

// Process
void	handle_process(char *rl, t_cmd *cmd_args);
void	process_parent(char *rl, t_cmd *cmd_args, int status);
void	process_child(t_cmd *cmd_args);

// Handle builtins
int		handle_cd(char **split_cmd, t_cmd *cmd_args);
int		handle_else(char **cmd, t_cmd *cmd_args);

// Execute
void	execute(t_cmd *cmd_args, int *fd);

// Pipe
void	create_pipe(int *fd);
int		count_pipe(char *rl);
int		separate_pipe_cmd(char **split_cmd, t_cmd *cmd_args, int i, int order);
void	cmd_by_pipe(char *rl, t_cmd *cmd_args);

// Fork
void	create_fork(pid_t *pid);

// Handle builtins
void	process_cd(char **split_cmd, t_cmd *cmd_args);

// Initial command
t_cmd	*initial_cmd(char **envp);

// Memory
void	free_container(char **temp);

/* ------------------------------------------------------------ */

// Terminal input output setting
void	new_term(void);
void	old_term(int get_set, struct termios *old_term);

// Signal
void	signal_handler(int signum);
void	init_signal(void);
void	signal_ignore(void);
void	signal_interruped(int status);

/* ------------------------------------------------------------ */

// Pipe
int		count_pipe(char *rl);
int		separate_pipe_cmd(char **split_cmd, t_cmd *cmd_args, int i, int order);
void	cmd_by_pipe(char *rl, t_cmd *cmd_args);

// Utiles
char	**space_quotes_split(char const *s);
int		count_cmd(char **split_cmd);
int		separate_pipe_cmd(char **split_cmd, t_cmd *cmd_args, int i, int cmd_nbr);
void	cmd_by_pipe(char *rl, t_cmd *cmd_args);
char	**get_cmd(t_cmd *cmd_args);

// Memory
void	free_cmd1(t_cmd *cmd_args);
void	free_cmd2(t_cmd *cmd_args);
void	free_cmd3(t_cmd *cmd_args);
void	free_all_cmd(t_cmd *cmd_args);
void	free_container(char **temp);

// Error
void	argc_error(int argc);
void	fork_error(pid_t pid);
void	result_error(int result, t_cmd *cmd_args);

/* ------------------------------------------------------------ */

#endif
