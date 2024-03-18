/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:23:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/18 14:18:19 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"
#include "libft.h"
#include "minishell.h"
#include "variable/env.h"
#include "variable/var.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
// TODO 後で消す
#include <stdio.h>

static bool	check_node_argv(t_minishell *minish, t_node *node)
{
	// cdのみ
	if (node->argv[1] == NULL)
	{
		if (get_var(minish, "HOME") != NULL)
		{
			node->argv[1] = ft_strdup(get_var(minish, "HOME"));
			if (node->argv[1] == NULL)
			{
				minish->error_kind = ERR_MALLOC;
				node->wait_status = 1;
				return (true);
			}
		}
		else
		{
			ft_printf_fd(STDERR_FILENO, HOME_NOT_SET);
			node->wait_status = 1;
			return (true);
		}
	}
	// cd ""の場合
	if (ft_strcmp(node->argv[1], "") == 0)
	{
		node->wait_status = 0;
		return (true);
	}
	return (false);
}

int	builtin_cd(t_minishell *minish, t_node *node)
{
	(void)minish;
	node->wait_status = 0;
	if (check_node_argv(minish, node))
		return (node->wait_status);
	if (chdir(node->argv[1]) < 0)
	{
		ft_printf_fd(STDERR_FILENO, BUILTIN_ERROR, "cd", node->argv[1],
			strerror(errno));
		node->wait_status = 1;
		return (node->wait_status);
	}
	if (minish->pwd != NULL)
		free(minish->pwd);
	minish->pwd = getcwd(NULL, MAXPATHLEN);
	return (node->wait_status);
}
