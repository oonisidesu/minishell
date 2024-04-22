/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:17:12 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/13 17:35:24 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/expansion.h"
#include "variable/env.h"

int	builtin_var(t_minishell *minish, t_node *node)
{
	t_node	*cur;

	cur = node->declare;
	while (cur)
	{
		add_or_update_var(minish, cur->argv[0], cur->argv[1], VAR_SHELL);
		cur = cur->next;
	}
	node->wait_status = 0;
	return (node->wait_status);
}
