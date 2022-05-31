/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:01:55 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/31 00:36:28 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "env_list.h"
# include "cmd_iterator.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include "./libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_mns
{
	char	*line;
	char	**lexical_line;
	char	**parsed_line;
	int		error_num;
	int		n_break;
	int		n;
	int		exit_code;
	int		error;
	int		exec_pid;
}	t_mns;

typedef struct s_cmd
{
	char 	**word;
	char 	**redirect;
	int		fd_in;
	int		fd_out;
	char	*file_out;
	char	*file_in;
	int		pipefd[2];
	int		save_stdout;
	int		save_stdin;
	char	*path;
	char	*var_name;
	char	*content;
	char	**commands;
	struct s_cmd *next;
} t_cmd;

typedef struct	s_main
{
	t_hash *hash[2];
	t_mns	mns;
	t_cmd	*cmd;
	t_env_list list;
}	t_main;

extern t_main *g_data;


char	*print_terminal_line(char *line);
int		token_analysis(t_mns *data);
int		lexical_analysis(t_mns *data);
int		syntax_analysis(char **lexical_line);
int		get_n_break(t_mns *data, int i);
int		len_subline(t_mns *data, int start, int len, int aux);
void	cmd_table(t_mns *data, t_cmd **cmd);
void	exec_cmds(t_cmd **cmd);
void	exec_here_doc(t_cmd *cmd_node, t_cmd **cmd, int i);
void	exec_redirect(t_cmd **cmd, t_cmd *cmd_node);
int		tild_expansion(t_cmd *cmd_node, int i);
void	quote_expansion(t_cmd *cmd_node, int i);
void	handle_s_quote(t_cmd *cmd_node, int i);
void	handle_d_quotes(t_cmd *cmd_node, int i);
char	*clean_quotes(char *content);
void	assignment_expansion(t_cmd *cmd_node, int i);
void	free_cmd_table(t_cmd **cmd);
void	free_lexical_line(t_mns *data);

// ENV
char	**copy_first_env(char **env);
char	**copy_env(char **env);
char	*find_env(char *var);
char	**get_sorted_env(void);
void	env_built_in(char **cmd);

// Commands
void	exec_command(t_main *cmd, char **env);
void	parent_command(t_main *cmd);
void	child_command(t_main *cmd, char **env);
void	exec_built_in(t_main *cmd);
int	check_if_built_in(t_main *cmd);

//PATH
char	*my_path_join(char const *s1, char const *s2);
int	check_dir(char *path);
void	check_directory_error(char *file);
char	*check_relative_absolute_paths(char *cmd);
char	*get_path(t_main *cmd);


//FREE
void	free_list(t_main *cmd);
void	free_all(void);

//Erro
void	exit_error_path(char **check, t_main *cmd);
void	check_directory_error(char *file);

//utils
int	ft_str_check(const char *s1, const char *s2);
void	free_split(char **s);

//Builtins
void	pwd_built_in(void);
void	echo_built_in(char **cmd);



#endif