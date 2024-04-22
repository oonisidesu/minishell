/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:22:07 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/15 18:22:56 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "message/message.h"
#include "minishell.h"
#include "parser/prompt.h"
#include "signal/signal.h"
#include "variable/env.h"

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q minishell");
// }

volatile sig_atomic_t	g_signal = 0;

int	event(void)
{
	return (0);
}

int	main(int argc, const char **argv, const char **envp)
{
	t_minishell	minish;

	init_minishell(&minish);
	minish.argc = argc;
	minish.argv = argv;
	rl_catch_signals = 0;
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, ctrl_backslash_handler);
	rl_event_hook = event;
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
