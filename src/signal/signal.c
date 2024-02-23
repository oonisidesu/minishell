/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:15:51 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/02/23 21:28:04 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "signal/signal.h"
#include <stdlib.h>

void    node_kill(t_node *node)
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
    g_signal = CTRL_C_ONE;
}

void	ctrl_c_clean_handler(t_minishell *minish)
{
    t_node *node;
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

void    ctrl_d_clean_handler(t_minishell *minish)
{
    t_node *node;
    node = minish->node;
    node_kill(node);
    free_minishell(minish);
    exit(minish->status_code);
}

int	signal_monitor()
{
	if (g_signal == CTRL_C_ONE)
	{
        rl_delete_text(0, rl_end);
        rl_done = 1;
        g_signal = CTRL_C_TWO;
	}
	return (0);
}
