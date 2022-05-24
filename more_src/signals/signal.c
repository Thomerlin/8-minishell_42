/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 16:29:57 by tyago-ri          #+#    #+#             */
/*   Updated: 2022/05/21 16:29:57 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data *global_data;
void	kill_loop(int signum)
{
	(void)signum;
	if (global_data->here_doc == 1)
	{
		close (STDIN);
		global_data->error = 1;
	}
	if (global_data->exec_pid != 0 && global_data->in_exec == 1)
	{
		kill(global_data->exec_pid, SIGKILL);
		write (1, "\n", 1);
	}
	if (global_data->in_exec == 0)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	global_data->exit_code = 130;
}

void	quit_core(int signum)
{
	(void)signum;
	if (global_data->exec_pid != 0 && global_data->in_exec == 1)
	{
		kill(global_data->exec_pid, SIGKILL);
		ft_putstr_fd("Quit (Core dumped)\n", 1);
	}
}
