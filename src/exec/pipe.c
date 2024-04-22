/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:06:41 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/21 19:17:10 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"
#include "exec/process.h"
#include "exec/redirect.h"
#include "message/message.h"
#include "minishell.h"
#include "utils/minishell_error.h"
#include <stdlib.h>
#include <unistd.h>

static void	init_pipe(t_minishell *minish, t_node **node, int *prev_fds,
		int *fds)
{
	*node = minish->node;
	prev_fds[0] = -1;
	prev_fds[1] = -1;
	fds[0] = -1;
	fds[1] = -1;
}

static int	connect_io(t_minishell *minish, t_node *node, int prev_fds[],
		int fds[])
{
	if (node->pid != RUN_PARENT)
	{
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
	if (redirect(minish, node))
	{
		if (is_builtin(node) && !node->in_pipe)
			return (1);
		die_minishell_and_exit(minish, EXIT_FAILURE);
	}
	return (0);
}

static int	create_pipe_and_fork(t_minishell *minish, t_node *node, int fds[])
{
	if (node->next != NULL)
	{
		if (pipe(fds) < 0)
		{
			occurred_resource_error(minish, "pipe");
			return (1);
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
			occurred_resource_error(minish, "fork");
			return (1);
		}
	}
	return (0);
}

static void	exec_builtin_or_cmd(t_minishell *minish, t_node *node)
{
	if (is_builtin(node))
	{
		(lookup_builtin_func(node))(minish, node);
		if (node->in_pipe)
		{
			die_minishell_and_exit(minish, node->wait_status);
		}
	}
	else
	{
		exec_cmd(minish, node);
	}
}

void	exec_pipe(t_minishell *minish)
{
	int		prev_fds[2];
	int		fds[2];
	t_node	*node;

	init_pipe(minish, &node, prev_fds, fds);
	while (node)
	{
		prev_fds[0] = fds[0];
		prev_fds[1] = fds[1];
		if (create_pipe_and_fork(minish, node, fds))
			return ;
		if (node->pid > 0)
		{
			parent_process(prev_fds);
			node = node->next;
			continue ;
		}
		if (connect_io(minish, node, prev_fds, fds))
			return ;
		exec_builtin_or_cmd(minish, node);
		node = node->next;
	}
}
