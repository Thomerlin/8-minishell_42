/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:36:53 by tyago-ri          #+#    #+#             */
/*   Updated: 2022/05/23 23:36:53 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error_path(char **check, t_main *cmd)
{
	if (check != NULL)
		free_split(check);
	write (STDERR, g_data->cmd->commands[0], ft_strlen(g_data->cmd->commands[0]));
	write (STDERR, ": command not found\n", 20);
	close (g_data->cmd->pipefd[1]);
	// free_all();
	exit (127);
}

void	check_directory_error(char *file)
{
	int		exit_code;
	int		error;
	if (file == NULL)
		return ;
	if (check_dir(file) == 1 && error == 0)
	{
		ft_putstr_fd(file, STDERR);
		ft_putstr_fd(": Is a directory\n", STDERR);
		error = 1;
		exit_code = 1;
	}
}
