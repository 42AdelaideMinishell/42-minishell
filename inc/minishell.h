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
	char	**cmd_one;
	char	**cmd_two;
	char	**cmd_three;
}	t_cmd;

// Terminal control attributes
# define GET 1
# define SET 2

// Path
char	*find_path(char *name, char **envp);
char	*get_path(char *cmd, char **envp);
// void	execute(char *cmd, t_cmd *cmd_args, int *fd);


// Process
void	handle_process(char *rl, t_cmd *cmd_args);

// Pipe
int		count_pipe(char *rl);
int		separate_pipe_cmd(char **split_cmd, t_cmd *cmd_args, int i, int order);
void	pipe_handle(char *rl, t_cmd *cmd_args);

// Handle builtins
int		handle_cd(char **split_cmd, t_cmd *cmd_args);
int		handle_else(t_cmd *cmd_args);

// Execute
void	execute(char *rl, t_cmd *cmd_args, int *fd);

// Initial command
t_cmd	*initial_cmd(char **envp);

// Memory
void	free_container(char **temp);

// Error
void	argc_error(int argc);
void	fork_error(pid_t pid);
void	result_error(int result, char **split_cmd);

// Terminal input output setting
void	new_term(void);
void	old_term(int get_set, struct termios *old_term);

// Signal
void	signal_handler(int signum);
void	init_signal(void);
void	signal_ignore(void);

// Utiles
char	**space_quotes_split(char const *s);

#endif
