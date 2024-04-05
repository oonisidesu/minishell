/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:15:51 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/04/02 16:46:21 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "signal/signal.h"
#include "utils/exit_status.h"
#include <stdlib.h>

void	node_kill(t_node *node)
{
	while (node)
	{
		if (node->pid > 0)
			kill(node->pid, SIGKILL);
		node = node->next;
	}
}

void	ctrl_c_handler(int sig)
{
	(void)sig;
	g_signal = CTRL_C;
	rl_replace_line("", 0);
	rl_done = 1;
}

void	ctrl_c_blank_line_handler(t_minishell *minish)
{
	if (g_signal == CTRL_C)
		minish->status_code = EXIT_FAILURE;
	g_signal = 0;
}

void	ctrl_d_clean_handler(t_minishell *minish)
{
	t_node	*node;

	node = minish->node;
	node_kill(node);
	die_minishell_and_exit(minish, minish->status_code);
}
