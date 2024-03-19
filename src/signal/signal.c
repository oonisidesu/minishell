/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:15:51 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/03/18 17:09:44 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "signal/signal.h"
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
	rl_on_new_line();
	ft_printf_fd(STDOUT_FILENO, "\n");
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = CTRL_C;
}

void	ctrl_c_clean_handler(t_minishell *minish)
{
	t_node	*node;

	node = minish->node;
	g_signal = 0;
	if (node == NULL)
		minish->status_code = 1;
	else
	{
		node_kill(node);
		minish->status_code = 130;
		free_minishell(minish);
	}
}

void	ctrl_d_clean_handler(t_minishell *minish)
{
	t_node	*node;

	node = minish->node;
	node_kill(node);
	die_minishell(minish);
	exit(minish->status_code);
}
