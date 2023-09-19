/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlyu <jlyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:33:08 by jlyu              #+#    #+#             */
/*   Updated: 2023/09/19 11:08:34 by jlyu             ###   ########.fr       */
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
	int		envp_size;
	int		p_re_count;
	int		cmd_order;
	char	**cmd;
	char	**cur_cmd;
	int		exit_flag;
}	t_cmd;

# define BUFFER_SIZE 1025

// Terminal control attributes
# define GET 1
# define SET 2

// Commands by pipes
# define SPACE ' '
# define SINGLE_Q '\''
# define DOUBLE_Q '\"'

// Redirection
# define OVERWRITE 1
# define APPEND 2
# define SEND 3
# define SEND_DOC 4

/* ------------------------------------------------------------ */

// Initial command
t_cmd		*initial_cmd(char **envp);

// Path
char		*find_path(char *name, char **envp);
char		*get_path(char *cmd, char **envp);

// Process
void		handle_process(char *rl, t_cmd *cmd_args);
void		cmd_process(t_cmd *cmd_args);
void		process_parent(t_cmd *cmd_args, int status);

// Builtins
void		process_cd(char **split_cmd, t_cmd *cmd_args);
void		process_unset(char **split_cmd, t_cmd *cmd_args);
void		process_export(char **split_cmd, t_cmd *cmd_args);
void		process_echo(char **split_cmd, t_cmd *cmd_args);

// Redirections
int			redirection(t_cmd *cmd_args);
void		overwrite(t_cmd *cmd_args);
void		append(t_cmd *cmd_args);
void		send(t_cmd *cmd_args);
void		send_doc(t_cmd *cmd_args);

// Redirection utiles
char		*get_filename(char **cmd);
int			open_helper(char **cmd, int condition);
int			get_redirection(char **cmd);

// Terminal input output setting
void		new_term(void);
void		old_term(int get_set, struct termios *old_term);

// Signal
void		init_signal(void);
void		ignore_signal(void);
void		signal_handler(int signum);
void		signal_interruped(int status);

// Pipe
void		create_pipe(int *fd);
void		create_two_pipes(int *p_fd_a, int *p_fd_b);
int			count_pipe(char **split_cmd);
int			count_pipe_redirection(char **split_cmd);

// Fork
void		create_fork(pid_t *pid);

// Utiles
char		**split_cmd(char const *s);
int			count_cmd(char **split_cmd);
char		**choose_cur_cmd(char **cmd, int cmd_order);
int			get_size_helper(char const *s, int i);
int			move_index(char const *s);
char const	*copy_helper(char const *s);

// Memory
void		free_container(char **temp);

// Error
void		argc_error(int argc);
void		fork_error(pid_t pid);
void		result_error(int result, t_cmd *cmd_args);
void		cmd_init_error(t_cmd *cmd_args);
void		open_error(int fd);

/* ------------------------------------------------------------ */

#endif
