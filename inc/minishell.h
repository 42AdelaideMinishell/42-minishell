/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:33:08 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/13 14:46:40 by jaeshin          ###   ########.fr       */
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
	int		p_re_count;
	int		cmd_order;
	char	**cmd;
	char	**cur_cmd;
	int		exit_flag;
}	t_cmd;

#define BUFFER_SIZE 1025

// Terminal control attributes
# define GET 1
# define SET 2

// Commands by pipes
# define SPACE ' '
# define SINGLE_Q '\''
# define DOUBLE_Q '\"'

// Redirection
# define OVERWRITE 0
# define APPEND 1

/* ------------------------------------------------------------ */

// Path
char	*find_path(char *name, char **envp);
char	*get_path(char *cmd, char **envp);

// Process
void	handle_process(char *rl, t_cmd *cmd_args);
void	cmd_process(t_cmd *cmd_args);
void	process_parent(t_cmd *cmd_args, int status);

// Builtins
void	process_cd(char **split_cmd, t_cmd *cmd_args);
void	process_unset(char **split_cmd, t_cmd *cmd_args);
void	process_export(char **split_cmd, t_cmd *cmd_args);
void	process_echo(char **split_cmd, t_cmd *cmd_args);

// Redirections
void	overwrite_append(t_cmd *cmd_args);

// Terminal input output setting
void	new_term(void);
void	old_term(int get_set, struct termios *old_term);

// Signal
void	init_signal(void);
void	ignore_signal(void);
void	signal_handler(int signum);
void	signal_interruped(int status);

// Initial command
t_cmd	*initial_cmd(char **envp);

// Pipe
void	create_pipe(int *fd);
int		count_pipe_redirection(char **split_cmd);

// Utiles
char	**split_cmd(char const *s);
int		count_cmd(char **split_cmd);
char	**choose_cur_cmd(char **cmd, int cmd_order);
int		get_size_helper(char const *s, int i);
int		move_index(char const *s);
char const	*copy_helper(char const *s);

// Fork
void	create_fork(pid_t *pid);

// Memory
void	free_container(char **temp);

// Error
void	argc_error(int argc);
void	fork_error(pid_t pid);
void	result_error(int result, t_cmd *cmd_args);
void	cmd_init_error(t_cmd *cmd_args);
void	open_error(int fd);

/* ------------------------------------------------------------ */

#endif
