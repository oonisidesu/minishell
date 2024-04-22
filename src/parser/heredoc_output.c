/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_output.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:43:15 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/08 11:58:45 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "message/message.h"
#include "utils/exit_status.h"
#include "utils/minishell_error.h"
#include <stdlib.h>
#include <unistd.h>

static void	heredoc_child(char *buf, int fds[2])
{
	close(fds[0]);
	write(fds[1], buf, ft_strlen(buf));
	close(fds[1]);
	exit(EXIT_SUCCESS);
}

static void	heredoc_parent(int fds[2])
{
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
}

int	write_heredoc(t_minishell *minish, int idx)
{
	int		fds[2];
	pid_t	pid;
	char	*buf;

	buf = minish->heredoc.docs[idx];
	if (pipe(fds) < 0)
	{
		occurred_resource_error(minish, "pipe");
		return (1);
	}
	pid = fork();
	if (pid < 0)
	{
		occurred_resource_error(minish, "fork");
		return (1);
	}
	if (pid == 0)
	{
		heredoc_child(buf, fds);
		return (0);
	}
	heredoc_parent(fds);
	return (0);
}
