/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:23:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/16 15:52:17 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"
#include "libft.h"
#include "minishell.h"
#include "variable/env.h"
#include "variable/var.h"
#include <stdlib.h>
#include <unistd.h>
// TODO 後で消す
#include <stdio.h>

static void	unset_env(t_minishell *minish, t_node *node)
{
	int		i;
	char	*key;

	i = 1;
	node->wait_status = 0;
	while (i < node->argc)
	{
		key = ft_strdup(node->argv[i]);
		if (key == NULL)
		{
			minish->error_kind = ERR_MALLOC;
			node->wait_status = 1;
			return ;
		}
		if (ft_strncmp(node->argv[i], "#", 1) == 0)
			break ;
		else if (is_var_dec_exclude_equal(node->argv[i],
				ft_strlen(node->argv[i])))
			del_var(minish, key);
		else
		{
			ft_printf_fd(STDERR_FILENO, IDENTIFIER_ERROR, "unset",
				node->argv[i]);
			node->wait_status = 1;
		}
		free(key);
		i++;
	}
}

int	builtin_unset(t_minishell *minish, t_node *node)
{
	if (node->argc == 1 || ft_strncmp(node->argv[1], "#", 1) == 0)
	{
		node->wait_status = 0;
		return (node->wait_status);
	}
	else
		unset_env(minish, node);
	return (node->wait_status);
}
