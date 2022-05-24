#ifndef MINISHELL_H
# define MINISHELL_H

# include "../librarie/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_link
{

	struct s_link	*next;
}	t_link;

typedef struct s_data
{
	int		exit_code;
	int		exit;
	int		error;
	int		in_exec;
	int		exec_pid;
	int		here_doc;
	t_link	*list;
}	t_data;

extern t_data *g_data;

int		ft_str_check(const char *s1, const char *s2);

void	pwd_built_in(void);
void	echo_built_in(char **cmd);

void	kill_loop(int signum);
void	quit_core(int signum);

#endif
