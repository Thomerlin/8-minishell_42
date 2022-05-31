/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:26:21 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/30 23:00:29 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef ENV_LIST_H
#define ENV_LIST_H

#include "libft.h"

typedef struct s_env_list
{
	char	*key;
	char	*value;
	char	**env;
	struct	s_env_list *next;
}	t_env_list;

typedef struct s_hash
{
	t_env_list **list;
	size_t	size;
	size_t	count;
}	t_hash;

#endif
