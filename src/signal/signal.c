/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:15:51 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/02/22 13:05:46 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "signal/signal.h"

void	ctrl_c_handler(int sig)
{
    (void)sig;
    g_signal = 1;
}

void	ctrl_c_clean_handler(t_minishell *minish)
{
    printf("===> ctrl_c_clean_handler\n");
    // TODO
    // segfaultするのでどうしようかな
    while (minish->node->pid)
    {
        kill(minish->node->pid, SIGKILL);
        minish->node = minish->node->next;
    }
    free_minishell(minish);
    minish->status_code = 130;
}

void    ctrl_d_clean_handler(t_minishell *minish)
{
    printf("===> ctrl_d_clean_handler\n");
    // TODO
    // segfaultするのでどうしようかな
    while (minish->node->pid)
    {
        kill(minish->node->pid, SIGKILL);
        minish->node = minish->node->next;
    }
    free_minishell(minish);
    minish->status_code = 1;
}

int	signal_monitor()
{
	if (g_signal)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = 0;
	}
	return (0);
}
