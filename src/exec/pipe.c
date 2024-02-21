/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:06:41 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/21 22:10:10 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cmd.h"
#include "exec/process.h"
#include "exec/redirect.h"
#include "minishell.h"
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

static void	connect_io(t_node *node, t_node *head, int prev_fds[], int fds[])
{
	if (!(node == head))
	{
		close(STDIN_FILENO);
		dup2(prev_fds[0], STDIN_FILENO);
		close(prev_fds[0]);
		close(prev_fds[1]);
	}
	if (!(node->next == NULL))
	{
		close(fds[0]);
		close(STDOUT_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
	}
}

static void	pipe_and_fork(t_node *node, int fds[])
{
	if (!(node->next == NULL))
	{
		if (pipe(fds) < 0)
		{
			perror("pipe");
			// TODO エラー処理
			exit(EXIT_FAILURE);
		}
	}
	node->pid = fork();
	if (node->pid < 0)
	{
		perror("fork");
		// TODO エラー処理
		exit(EXIT_FAILURE);
	}
}

void	exec_pipe(t_minishell *minish)
{
	int		prev_fds[2];
	int		fds[2];
	t_node	*node;
	char	**envp;

	envp = get_envp(minish);
	init_fds(prev_fds, fds);
	node = minish->node;
	while (node)
	{
		prev_fds[0] = fds[0];
		prev_fds[1] = fds[1];
		pipe_and_fork(node, fds);
		if (node->pid > 0)
		{
			node = parent_process(node, prev_fds);
			continue ;
		}
		connect_io(node, minish->node, prev_fds, fds);
		redirect(node);
		exec_cmd(node, envp);
	}
}