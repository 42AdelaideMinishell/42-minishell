#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <stdio.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <termios.h>
# include <termcap.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

// Terminal control attributes
# define GET 1
# define SET 2

// Memory
void	free_container(char **temp);

// Error
void	argc_error(int argc);
void	fork_error(pid_t pid);

// Path
char	*find_path(char *name, char **envp);
char	*get_path(char *cmd, char **envp);
void	execute(char *cmd, char **envp);

// Terminal input output setting
void	new_term(void);
void	old_term(int get_set, struct termios *old_term);

// Signal
void	signal_handler(int signum);
void	init_signal(void);
void	signal_ignore(void);

// Process
void	handle_process(char *rl, char **envp);

#endif
