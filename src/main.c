/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:22:07 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/21 17:39:45 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser/prompt.h"
#include "readline.h"
#include "variable/env.h"

int	check_state(void)
{
	// TODO
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minish;

	(void)argv;
	rl_event_hook = check_state;
	if (argc > 1)
	{
		ft_putstr_fd(TOO_MANY_ARGS, STDERR_FILENO);
		return (1);
	}
	set_envp(&minish, envp);
	while (1)
	{
		prompt(&minish);
	}
	return (0);
}
