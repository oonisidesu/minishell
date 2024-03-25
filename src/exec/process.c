/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:06:41 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/25 13:52:43 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"
#include "exec/ft_strsignal.h"
#include "exec/process.h"
#include "libft.h"
#include "message/message.h"
#include "minishell.h"
#include "parser/node.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	exec_cmd(t_node *node, char **envp)
{
	if (!node->exist_cmd)
	{
		if (ft_strchr(node->argv[0], '/'))
		{
			ft_printf_fd(STDERR_FILENO, "pipex: %s: %s\n", node->argv[0],
				NO_SUCH_FILE_OR_DIR);
		}
		else
		{
			ft_printf_fd(STDERR_FILENO, "pipex: %s: %s\n", node->argv[0],
				COMMAND_NOT_FOUND);
		}
		exit(EXIT_FAILURE);
	}
	else if (!node->has_x)
	{
		ft_printf_fd(STDERR_FILENO, "pipex: %s: %s\n", node->argv[0],
			PERMISSION_DENIED);
		exit(EXIT_FAILURE);
	}
	execve(node->path, node->argv, envp);
	perror(node->path);
	exit(EXIT_FAILURE);
}

t_node	*parent_process(t_node *node, int prev_fds[])
{
	if (prev_fds[0] != -1)
		close(prev_fds[0]);
	if (prev_fds[1] != -1)
		close(prev_fds[1]);
	return (node->next);
}

void	wait_prosesses(t_minishell *minish)
{
	t_node	*node;

	node = minish->node;
	if (node->pid == RUN_PARENT)
	{
		return ;
	}
	while (node)
	{
		waitpid(node->pid, &node->wait_status, 0);
		if (WIFEXITED(node->wait_status))
		{
			node->wait_status = WEXITSTATUS(node->wait_status);
		}
		else if (WIFSIGNALED(node->wait_status))
		{
			if (node->next == NULL)
			{
				ft_printf_fd(STDERR_FILENO, "%s: %d\n",
					ft_strsignal(WTERMSIG(node->wait_status)),
					WTERMSIG(node->wait_status));
			}
			node->wait_status |= 128;
		}
		else if (WIFSTOPPED(node->wait_status))
		{
		}
		else
		{
			perror("abnormal exit");
		}
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
	minish->status_code = node->wait_status;
}
