/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:22:07 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/22 13:02:50 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser/prompt.h"
#include "signal/signal.h"
#include "variable/env.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minish;

	(void)argv;
	// TODO
	// t_minishellの初期化したい
	signal(SIGINT, ctrl_c_handler);
	rl_initialize();
	rl_event_hook = signal_monitor;
	if (argc > 1)
	{
		ft_printf_fd(STDERR_FILENO, TOO_MANY_ARGS);
		return (1);
	}
	set_envp(&minish, envp);
	while (1)
	{
		prompt(&minish);
	}
	return (0);
}
