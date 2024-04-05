/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:23:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/04 15:11:05 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"
#include "libft.h"
#include "message/message.h"
#include "minishell.h"
#include "utils/exit_status.h"
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

static char	*skip_space(char *str)
{
	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		str++;
	return (str);
}

static int	occer_overflow(char *str, long sign, long ret)
{
	if (sign == 1)
	{
		if (LONG_MAX / 10 < ret)
			return (1);
		if (LONG_MAX - ret * 10 < sign * (*str - '0'))
			return (1);
	}
	else if (sign == -1)
	{
		if (LONG_MIN / 10 > ret)
			return (1);
		if (LONG_MIN - ret * 10 > sign * (*str - '0'))
			return (1);
	}
	return (0);
}

static bool	is_numeric(char *str)
{
	str = skip_space(str);
	if (*str == '+' || *str == '-')
		str++;
	if (ft_isdigit(*str) == 0)
		return (false);
	while (*str != '\0' && '0' <= *str && *str <= '9')
		str++;
	if (*str != '\0' && ft_isdigit(*str) == 0)
		return (false);
	return (true);
}

static bool	is_long_range(char *str)
{
	long	sign;
	long	ret;

	str = skip_space(str);
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	ret = 0;
	while (*str != '\0' && '0' <= *str && *str <= '9')
	{
		if (occer_overflow(str, sign, ret))
			return (false);
		ret = ret * 10 + sign * (*str - '0');
		str++;
	}
	return (true);
}

int	builtin_exit(t_minishell *minish, t_node *node)
{
	if (node->argc == 1)
		minish->status_code = 0;
	else if (is_numeric(node->argv[1]) && is_long_range(node->argv[1]))
	{
		if (node->argc == 2)
			minish->status_code = (unsigned char)ft_atoi(node->argv[1]);
		else if (node->argc > 2)
		{
			if (!node->in_pipe)
				ft_printf_fd(STDERR_FILENO, "exit\n");
			ft_printf_fd(STDERR_FILENO, MINISHELL_ERROR, "exit",
				B_TOO_MANY_ARGS);
			node->wait_status = EXIT_FAILURE;
			minish->status_code = EXIT_FAILURE;
			return (minish->status_code);
		}
	}
	else
	{
		if (!node->in_pipe)
			ft_printf_fd(STDERR_FILENO, "exit\n");
		ft_printf_fd(STDERR_FILENO, BUILTIN_ERROR, "exit", node->argv[1],
			NUM_ARG_REQUIRED);
		node->wait_status = EXIT_OUT_OF_RANGE_STATUS;
		minish->status_code = EXIT_OUT_OF_RANGE_STATUS;
		die_minishell_and_exit(minish, minish->status_code);
	}
	if (!node->in_pipe)
		ft_printf_fd(STDOUT_FILENO, "exit\n");
	die_minishell_and_exit(minish, minish->status_code);
	return (0);
}
