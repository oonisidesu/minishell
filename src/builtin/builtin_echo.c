/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:23:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/16 22:20:48 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static void	print_arg(t_node *node, int start)
{
	int	i;

	i = start;
	while (node->argv[i] != NULL)
	{
		ft_printf_fd(STDOUT_FILENO, "%s", node->argv[i]);
		if (i + 1 < node->argc)
			ft_printf_fd(STDOUT_FILENO, " ");
		i++;
	}
	if (start == 1)
		ft_printf_fd(STDOUT_FILENO, "\n");
}

static bool	is_option_n(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (i == 0 && str[i] != '-')
			return (false);
		if (i == 1 && str[i] != 'n')
			return (false);
		if (i > 1 && str[i] != 'n')
			return (false);
		i++;
	}
	if (i <= 1)
		return (false);
	return (true);
}

int	builtin_echo(t_minishell *minish, t_node *node)
{
	int	start;

	(void)minish;
	start = 1;
	node->wait_status = 0;
	if (node->argc == 1)
	{
		ft_printf_fd(STDOUT_FILENO, "\n");
		return (node->wait_status);
	}
	while (node->argc > start && is_option_n(node->argv[start]))
		start++;
	print_arg(node, start);
	return (node->wait_status);
}
