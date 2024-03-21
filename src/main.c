/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:22:07 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/21 19:18:02 by ootsuboyosh      ###   ########.fr       */
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
	signal(SIGINT, ctrl_c_handler);
	// hookを設定することでrl_doneが効くようになったのでreadlineから抜けることができる
	// hookはwebに上がっているminishellでも使っているので使っても良いかも使える理由を探し中
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
