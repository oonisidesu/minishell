/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:22:07 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/20 16:42:19 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser/prompt.h"
#include "variable/env.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minish;

	(void)argv;
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
