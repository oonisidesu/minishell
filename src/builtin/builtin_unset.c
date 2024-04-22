/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:23:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/18 17:05:09 by ootsuboyosh      ###   ########.fr       */
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
	int		i;
	bool	identifier_err_flag;

	i = 1;
	identifier_err_flag = false;
	while (i < node->argc)
	{
		if (is_var_dec_exclude_equal(node->argv[i], ft_strlen(node->argv[i])))
		{
			if (identifier_err_flag == false)
				node->wait_status = 0;
			del_var(minish, node->argv[i]);
		}
		else
		{
			ft_printf_fd(STDERR_FILENO, IDENTIFIER_ERROR, "unset",
				node->argv[i]);
			identifier_err_flag = true;
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
