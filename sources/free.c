/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:20:50 by tyago-ri          #+#    #+#             */
/*   Updated: 2022/05/30 22:20:50 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_main *cmd)
{
	t_main	*temp;

	while (cmd != NULL)
	{
		temp = g_data->cmd->next;
		free(g_data->cmd->file_in);
		free(g_data->cmd->file_out);
		if (g_data->cmd->fd_in != 0)
			close (g_data->cmd->fd_in);
		if (g_data->cmd->fd_out != 0)
			close (g_data->cmd->fd_out);
		if (g_data->cmd != NULL)
			free_split(g_data->cmd);
		free(g_data->cmd->path);
		free (cmd);
		cmd = temp;
	}
}

void	free_all(void)
{
	if (g_data->cmd != NULL)
		free_list(g_data->cmd);
	if (g_data->mns.line != NULL)
		free (g_data->mns.line);
	free_split(g_data->list.env);
	rl_clear_history();
	close(g_data->cmd->save_stdin);
	close(g_data->cmd->save_stdout);
	free (g_data);
}
