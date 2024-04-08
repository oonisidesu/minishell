/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:06:41 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/08 19:42:56 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"
#include "exec/ft_strsignal.h"
#include "libft.h"
#include "message/message.h"
#include "minishell.h"
#include "utils/exit_status.h"
#include "utils/minishell_error.h"
#include <sys/wait.h>

static void	wait_signal(t_node *node)
{
	if (node->next == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %d\n",
			ft_strsignal(WTERMSIG(node->wait_status)),
			WTERMSIG(node->wait_status));
	}
	node->wait_status |= 128;
	g_signal = 0;
}

void	wait_prosesses(t_minishell *minish)
{
	t_node	*node;

	node = minish->node;
	if (node->pid == RUN_PARENT)
		return ;
	while (node)
	{
		waitpid(node->pid, &node->wait_status, 0);
		if (WIFEXITED(node->wait_status))
		{
			node->wait_status = WEXITSTATUS(node->wait_status);
		}
		else if (WIFSIGNALED(node->wait_status))
		{
			wait_signal(node);
		}
		else if (WIFSTOPPED(node->wait_status))
		{
		}
		else
			perror("abnormal exit");
		node = node->next;
	}
}

void	set_status_code(t_minishell *minish)
{
	t_node	*node;

	node = minish->node;
	while (node->next != NULL)
	{
		node = node->next;
	}
	if (minish->error_kind == ERR_RESOURCE)
	{
		minish->status_code = EXIT_FAILURE;
		return ;
	}
	minish->status_code = node->wait_status;
}
