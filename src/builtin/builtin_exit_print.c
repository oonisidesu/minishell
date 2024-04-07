/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:22:38 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/03/30 17:20:56 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin_exit.h"
#include "libft.h"
#include "message/message.h"
#include <stdlib.h>

int	print_minishell_err(t_minishell *minish, t_node *node)
{
	if (!node->in_pipe)
		ft_printf_fd(STDERR_FILENO, "exit\n");
	ft_printf_fd(STDERR_FILENO, MINISHELL_ERROR, "exit", B_TOO_MANY_ARGS);
	minish->status_code = 1;
	return (minish->status_code);
}

void	print_builtin_err(t_minishell *minish, t_node *node)
{
	if (!node->in_pipe)
		ft_printf_fd(STDERR_FILENO, "exit\n");
	ft_printf_fd(STDERR_FILENO, BUILTIN_ERROR, "exit", node->argv[1],
		NUM_ARG_REQUIRED);
	minish->status_code = 255;
	die_minishell(minish);
	exit(minish->status_code);
}
