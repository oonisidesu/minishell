/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:06:41 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/12 14:09:43 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "message/message.h"
#include "minishell.h"
#include "utils/exit_status.h"
#include "utils/minishell_error.h"
#include "variable/env.h"
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

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

static void	check_permission(t_minishell *minish, t_node *node)
{
	if (!node->has_x)
	{
		ft_printf_fd(STDERR_FILENO, MINISHELL_ERROR, node->argv[0],
			PERMISSION_DENIED);
		die_minishell_and_exit(minish, EXIT_CANNOT_EXECUTE_COMMAND);
	}
}

void	check_dir(t_minishell *minish, t_node *node)
{
	struct stat	statbuf;

	if (stat(node->path, &statbuf) != 0)
	{
		ft_printf_fd(STDERR_FILENO, MINISHELL_ERROR, node->path,
			strerror(errno));
		die_minishell_and_exit(minish, EXIT_CANNOT_EXECUTE_COMMAND);
	}
	if (S_ISDIR(statbuf.st_mode))
	{
		ft_printf_fd(STDERR_FILENO, MINISHELL_ERROR, node->path,
			IS_A_DIRECTORY);
		die_minishell_and_exit(minish, EXIT_CANNOT_EXECUTE_COMMAND);
	}
}

void	exec_cmd(t_minishell *minish, t_node *node)
{
	char	**envp;

	if (node->argv[0] == NULL)
		die_minishell_and_exit(minish, EXIT_SUCCESS);
	if (!node->exist_cmd)
		not_found(minish, node);
	else
	{
		check_dir(minish, node);
		check_permission(minish, node);
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

void	parent_process(int prev_fds[])
{
	if (prev_fds[0] != -1)
		close(prev_fds[0]);
	if (prev_fds[1] != -1)
		close(prev_fds[1]);
}
