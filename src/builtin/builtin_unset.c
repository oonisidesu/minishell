/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:23:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/19 17:13:18 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"
#include "libft.h"
#include "message/message.h"
#include "minishell.h"
#include "variable/env.h"
#include "variable/var.h"
#include <stdlib.h>
#include <unistd.h>

static void	unset_env(t_minishell *minish, t_node *node)
{
	int	i;

	i = 1;
	while (i < node->argc)
	{
		if (is_var_dec_exclude_equal(node->argv[i], ft_strlen(node->argv[i])))
		{
			node->wait_status = 0;
			del_var(minish, node->argv[i]);
		}
		else
		{
			ft_printf_fd(STDERR_FILENO, IDENTIFIER_ERROR, "unset",
				node->argv[i]);
			node->wait_status = 1;
		}
		i++;
	}
}

int	builtin_unset(t_minishell *minish, t_node *node)
{
	if (node->argc == 1)
	{
		node->wait_status = 0;
		return (node->wait_status);
	}
	else
		unset_env(minish, node);
	return (node->wait_status);
}
