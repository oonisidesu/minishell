/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:06:41 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/08 18:18:30 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "message/message.h"
#include "minishell.h"
#include "utils/exit_status.h"
#include "utils/minishell_error.h"
#include "variable/env.h"

static void	not_found(t_minishell *minish, t_node *node)
{
	char	*path;

	path = get_var(minish, "PATH");
	if (ft_strchr(node->argv[0], '/') || path == NULL || ft_strlen(path) == 0)
	{
		ft_printf_fd(STDERR_FILENO, MINISHELL_ERROR, node->argv[0],
			NO_SUCH_FILE_OR_DIR);
	}
	else
	{
		ft_printf_fd(STDERR_FILENO, MINISHELL_ERROR, node->argv[0],
			COMMAND_NOT_FOUND);
	}
	die_minishell_and_exit(minish, EXIT_COMMAND_NOT_FOUND);
}

void	exec_cmd(t_minishell *minish, t_node *node)
{
	char	**envp;

	if (node->argv[0] == NULL)
		die_minishell_and_exit(minish, EXIT_SUCCESS);
	if (!node->exist_cmd)
		not_found(minish, node);
	else if (!node->has_x)
	{
		ft_printf_fd(STDERR_FILENO, MINISHELL_ERROR, node->argv[0],
			PERMISSION_DENIED);
		die_minishell_and_exit(minish, EXIT_CANNOT_EXECUTE_COMMAND);
	}
	envp = get_envp(minish);
	if (!envp)
	{
		occurred_malloc_error_return_null(minish);
		die_minishell_and_exit(minish, EXIT_FAILURE);
	}
	execve(node->path, node->argv, envp);
	perror(node->path);
	die_minishell_and_exit(minish, EXIT_FAILURE);
}

t_node	*parent_process(t_node *node, int prev_fds[])
{
	if (prev_fds[0] != -1)
		close(prev_fds[0]);
	if (prev_fds[1] != -1)
		close(prev_fds[1]);
	return (node->next);
}
