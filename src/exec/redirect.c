/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:06:41 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/18 12:42:58 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/heredoc.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	redirect_stdin(char *path)
{
	int	fd;

	close(STDIN_FILENO);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror(path);
		// TODO exitしちゃだめ
		exit(EXIT_FAILURE);
	}
	if (fd != STDIN_FILENO)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	redirect_stdout(char *path)
{
	int	fd;

	close(STDOUT_FILENO);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		perror(path);
		// TODO exitしちゃだめ
		exit(EXIT_FAILURE);
	}
	if (fd != STDOUT_FILENO)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	redirect(t_minishell *minish, t_node *node)
{
	t_node	*redirect_node;

	redirect_node = node->redirect;
	while (redirect_node)
	{
		if (redirect_node->kind == ND_REDIRECT_IN)
			redirect_stdin(redirect_node->path);
		else if (redirect_node->kind == ND_REDIRECT_OUT)
			redirect_stdout(redirect_node->path);
		else if (redirect_node->kind == ND_HEREDOC)
			write_heredoc(minish, node->heredoc_idx);
		redirect_node = redirect_node->next;
	}
}
