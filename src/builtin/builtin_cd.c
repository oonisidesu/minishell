/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:23:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/07 16:36:13 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"
#include "minishell.h"
#include "variable/env.h"
#include "variable/var.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/param.h>
#include <string.h>
// TODO 後で消す
#include <stdio.h>

int	check_node_argv(t_minishell *minish, t_node *node)
{
	// cdのみ
	if (node->argv[1] == NULL)
	{
		node->argv[1] = get_var(minish, "HOME");
		if (node->argv[1] == NULL)
		{
			ft_printf_fd(STDERR_FILENO, HOME_NOT_SET);
			node->wait_status = 1;
			return (node->wait_status);
		}
	}
	return (0);
}

int	builtin_cd(t_minishell *minish, t_node *node)
{
	(void)minish;
	node->wait_status = 0;
	if (check_node_argv(minish, node) != 0)
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
