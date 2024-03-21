/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:43:15 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/21 19:10:54 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "message/message.h"
#include "parser/expansion.h"
#include "parser/heredoc.h"
#include "readline.h"
#include <stdio.h>
#include <stdlib.h>

void	init_heredoc(t_heredoc *heredoc)
{
	int	i;

	heredoc->num = 0;
	i = 0;
	while (i < 16)
	{
		heredoc->delimiters[i] = NULL;
		heredoc->docs[i] = NULL;
		i++;
	}
}

void	free_heredoc(t_heredoc *heredoc)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (heredoc->delimiters[i])
			free(heredoc->delimiters[i]);
		if (heredoc->docs[i])
			free(heredoc->docs[i]);
		i++;
	}
}

int	set_heredoc_delimiter(t_minishell *minish, t_token *tok)
{
	int	idx;

	if (minish->heredoc.num >= MAX_HEREDOC)
	{
		ft_printf_fd(STDERR_FILENO, ERROR_MAX_HEREDOC);
		exit(2);
	}
	idx = minish->heredoc.num;
	minish->heredoc.num++;
	minish->heredoc.delimiters[idx] = expand_delimiter(minish, tok);
	if (minish->heredoc.delimiters[idx] == NULL)
	{
		return (-1);
	}
	minish->heredoc.need_expansion[idx] = (ft_memchr(tok->str, '\'',
				tok->len) == NULL) && (ft_memchr(tok->str, '\"',
				tok->len) == NULL);
	return (idx);
}

void	read_heredoc(t_minishell *minish, int idx)
{
	char	*line;
	char	*tmp;
	char	*doc;

	doc = (char *)ft_calloc(1, sizeof(char));
	if (!doc)
	{
		minish->error_kind = ERR_MALLOC;
		return ;
	}
	while (1)
	{
		line = readline(HEREDOC_PROMPT);
		// ctrl + Dの場合
		if (line == NULL || ft_strcmp(line, "") == 0)
		{
			break ;
		}
		// ctrl + Cの場合
		if (ft_strcmp(line, "") == 0)
		{
			doc = NULL;
			break ;
		}
		// 終端文字列の場合
		if (ft_strcmp(line, minish->heredoc.delimiters[idx]) == 0)
		{
			free(line);
			break ;
		}
		// 変数展開
		if (minish->heredoc.need_expansion[idx])
		{
			tmp = line;
			// TODO 変数展開にする。一旦strdupでコピーしているだけ
			line = expand_heredoc(minish, line);
			if (!line)
			{
				free(tmp);
				free(doc);
				minish->error_kind = ERR_MALLOC;
				return ;
			}
			free(tmp);
		}
		// lineを結合
		tmp = doc;
		doc = ft_join_words(3, doc, line, "\n");
		if (!doc)
		{
			free(line);
			free(tmp);
			minish->error_kind = ERR_MALLOC;
			return ;
		}
		free(tmp);
		free(line);
	}
	minish->heredoc.docs[idx] = doc;
}

void	input_heredoc(t_minishell *minish)
{
	size_t	i;

	i = 0;
	while (i < minish->heredoc.num)
	{
		read_heredoc(minish, i);
		i++;
	}
}

void	write_heredoc(t_minishell *minish, int idx)
{
	int		fds[2];
	pid_t	pid;
	char	*buf;

	buf = minish->heredoc.docs[idx];
	if (pipe(fds) < 0)
	{
		perror("pipe");
		// TODO exitしちゃだめ
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		// TODO exitしちゃだめ
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		// 子プロセス
		close(fds[0]);
		write(fds[1], buf, ft_strlen(buf));
		close(fds[1]);
		exit(EXIT_SUCCESS);
	}
	// 親プロセス
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	// TODO waitしていないので親で実行するとゾンビになる
	// catなどビルトインでなければ孫プロセスになるため問題なし
	// waitpid(pid, &status, 0);
}
