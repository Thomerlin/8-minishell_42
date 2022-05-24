/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 16:31:06 by tyago-ri          #+#    #+#             */
/*   Updated: 2022/05/21 16:31:06 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*g_data;

void	echo_built_in(char **cmd)
{
	int	i;

	i = 1;
	if (cmd[1] == NULL)
		write (1, "\n", 1);
	else
	{
		if (ft_str_check(cmd[1], "-n"))
			i++;
		while (cmd[i] != NULL)
		{
			if (cmd[i][0] != '\0')
				ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1] != NULL)
				write (1, " ", 1);
			i++;
		}
		if ((ft_str_check(cmd[1], "-n")) == 0)
			write (1, "\n", 1);
	}
	g_data->exit_code = 0;
	return ;
}

int main(int argc, char **argv)
{
	echo_built_in(argv);
}
