/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:06:41 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/19 16:33:07 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"
#include "libft.h"
#include "message/message.h"
#include "minishell.h"
#include "parser/heredoc.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int	redirect_stdin(char *path)
{
	int	fd;

	close(STDIN_FILENO);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf_fd(STDERR_FILENO, MINISHELL_ERROR, path, strerror(errno));
		return (1);
	}
	if (fd != STDIN_FILENO)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

static int	redirect_stdout(char *path)
{
	int	fd;

	close(STDOUT_FILENO);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		ft_printf_fd(STDERR_FILENO, MINISHELL_ERROR, path, strerror(errno));
		return (1);
	}
	if (fd != STDOUT_FILENO)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

static int	redirect_append(char *path)
{
	int	fd;

	close(STDOUT_FILENO);
	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
	{
		ft_printf_fd(STDERR_FILENO, MINISHELL_ERROR, path, strerror(errno));
		return (1);
	}
	if (fd != STDOUT_FILENO)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

int	redirect(t_minishell *minish, t_node *node)
{
	t_node	*redirect_node;
	int		is_error;

	is_error = 0;
	redirect_node = node->redirect;
	while (redirect_node)
	{
		if (redirect_node->kind == ND_REDIRECT_IN)
			is_error = redirect_stdin(redirect_node->path);
		else if (redirect_node->kind == ND_REDIRECT_OUT)
			is_error = redirect_stdout(redirect_node->path);
		else if (redirect_node->kind == ND_REDIRECT_APPEND)
			is_error = redirect_append(redirect_node->path);
		else if (redirect_node->kind == ND_HEREDOC)
		{
			if (!(is_builtin(node) && !node->in_pipe))
				is_error = write_heredoc(minish, redirect_node->heredoc_idx);
		}
		if (is_error)
			return (1);
		redirect_node = redirect_node->next;
	}
	return (0);
}
