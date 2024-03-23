/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:23:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/23 19:53:51 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"
#include "libft.h"
#include "message/message.h"
#include "minishell.h"
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
			// TODO: pipeの時メッセージがうまく表示されない
			if (!node->in_pipe)
				ft_printf_fd(STDERR_FILENO, "exit\n");
			ft_printf_fd(STDERR_FILENO, MINISHELL_ERROR, "exit",
				B_TOO_MANY_ARGS);
			minish->status_code = 1;
			return (minish->status_code);
		}
	}
	else
	{
		// TODO: pipeの時メッセージがうまく表示されない
		if (!node->in_pipe)
			ft_printf_fd(STDERR_FILENO, "exit\n");
		ft_printf_fd(STDERR_FILENO, BUILTIN_ERROR, "exit", node->argv[1],
			NUM_ARG_REQUIRED);
		minish->status_code = 255;
		die_minishell(minish);
		exit(minish->status_code);
	}
	die_minishell(minish);
	if (!node->in_pipe)
		ft_printf_fd(STDOUT_FILENO, "exit\n");
	exit(minish->status_code);
	return (0);
}
