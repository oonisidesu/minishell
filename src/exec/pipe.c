/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:06:41 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/02 17:01:07 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"
#include "exec/process.h"
#include "exec/redirect.h"
#include "message/message.h"
#include "minishell.h"
#include "utils/minishell_error.h"
#include "variable/env.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	init_fds(int *prev_fds, int *fds)
{
	prev_fds[0] = -1;
	prev_fds[1] = -1;
	fds[0] = -1;
	fds[1] = -1;
}

static void	connect_io(t_minishell *minish, t_node *node, int prev_fds[],
		int fds[])
{
	if (node->pid == RUN_PARENT)
	{
		return ;
	}
	if (node != minish->node)
	{
		close(STDIN_FILENO);
		dup2(prev_fds[0], STDIN_FILENO);
		close(prev_fds[0]);
		close(prev_fds[1]);
	}
	if (node->next != NULL)
	{
		close(fds[0]);
		close(STDOUT_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
	}
}

void	exec_pipe(t_minishell *minish)
{
	int		prev_fds[2];
	int		fds[2];
	t_node	*node;

	init_fds(prev_fds, fds);
	node = minish->node;
	while (node)
	{
		prev_fds[0] = fds[0];
		prev_fds[1] = fds[1];
		if (node->next != NULL)
		{
			if (pipe(fds) < 0)
			{
				return (occurred_resource_error(minish, "pipe"));
			}
		}
		node->in_pipe = is_in_pipe(minish);
		if (is_builtin(node) && !node->in_pipe)
		{
			node->pid = RUN_PARENT;
		}
		else
		{
			node->pid = fork();
			if (node->pid < 0)
			{
				return (occurred_resource_error(minish, "fork"));
			}
			if (node->pid > 0)
			{
				node = parent_process(node, prev_fds);
				continue ;
			}
		}
		connect_io(minish, node, prev_fds, fds);
		if (redirect(minish, node))
		{
			if (is_builtin(node) && !node->in_pipe)
				return ;
			die_minishell_and_exit(minish, EXIT_FAILURE);
		}
		if (is_builtin(node))
		{
			lookup_builtin_func(node)(minish, node);
			if (node->in_pipe)
			{
				die_minishell_and_exit(minish, node->wait_status);
			}
			node = node->next;
		}
		else
		{
			exec_cmd(minish, node);
		}
	}
}
