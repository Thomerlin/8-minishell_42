/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 16:57:22 by tyago-ri          #+#    #+#             */
/*   Updated: 2022/05/21 16:57:22 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_built_in(t_main *cmd)
{
	if (ft_str_check(g_data->cmd->commands[0], "echo"))
		return (1);
	else if (ft_str_check(g_data->cmd->commands[0], "pwd"))
		return (1);
	else
		return (0);
}

void	exec_built_in(t_main *cmd)
{
	if (g_data->cmd->file_out == NULL && g_data->cmd->next != NULL)
		dup2(g_data->cmd->pipefd[1], STDOUT);
	if (ft_str_check(g_data->cmd->commands[0], "echo"))
		echo_built_in(g_data->cmd->commands);
	else if (ft_str_check(g_data->cmd->commands[0], "pwd"))
		pwd_built_in();
	dup2(g_data->cmd->pipefd[0], STDIN);
	dup2(g_data->cmd->save_stdout, STDOUT);
	close(g_data->cmd->pipefd[0]);
	close(g_data->cmd->pipefd[1]);
}

void	child_command(t_main *cmd, char **env)
{
	close(g_data->cmd->pipefd[0]);
	if (g_data->cmd->file_out == NULL && g_data->cmd->next != NULL)
		dup2(g_data->cmd->pipefd[1], STDOUT);
	g_data->cmd->path = get_path(cmd);
	if (g_data->cmd->file_in != NULL)
	{
		dup2(g_data->cmd->fd_in, STDIN);
		close (g_data->cmd->fd_in);
	}
	close(g_data->cmd->pipefd[1]);
	close(g_data->cmd->save_stdin);
	close(g_data->cmd->save_stdout);
	execve(g_data->cmd->path, g_data->cmd->commands, env);
	ft_putstr_fd("Error while executing\n", STDERR);
	free_all();
	exit (1);
}

void	parent_command(t_main *cmd)
{
	int	status;

	close(g_data->cmd->pipefd[1]);
	if (g_data->cmd->next != NULL)
	{
		dup2(g_data->cmd->pipefd[0], STDIN);
		waitpid(g_data->mns.exec_pid, &status, 0);
		g_data->mns.exit_code = WEXITSTATUS(status);
	}
	else
	{
		waitpid(g_data->mns.exec_pid, &status, 0);
		g_data->mns.exit_code = WEXITSTATUS(status);
	}
	close (g_data->cmd->pipefd[0]);
}

void	exec_command(t_main *cmd, char **env)
{
	if (pipe(g_data->cmd->pipefd) == -1)
		exit (-1);
	if (check_if_built_in(cmd))
		exec_built_in(cmd);
	else
	{
		g_data->mns.exec_pid = fork();
		if (g_data->mns.exec_pid == 0)
			child_command(cmd, env);
		else
			parent_command(cmd);
	}
}
