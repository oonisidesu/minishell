/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:43:15 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/12 17:31:03 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "message/message.h"
#include "parser/expansion.h"
#include "readline.h"
#include "signal/signal.h"
#include "utils/minishell_error.h"
#include <stdio.h>
#include <stdlib.h>

static char	*expand_line(t_minishell *minish, char *line, char *doc, int idx)
{
	char	*ret;

	if (minish->heredoc.need_expansion[idx])
	{
		ret = expand_heredoc(minish, line);
		if (!ret)
		{
			free(line);
			free(doc);
			return (NULL);
		}
		free(line);
	}
	else
	{
		ret = line;
	}
	return (ret);
}

static char	*join_line(t_minishell *minish, char *doc, char *line)
{
	char	*ret;

	ret = ft_join_words(3, doc, line, "\n");
	if (!ret)
	{
		free(doc);
		free(line);
		occurred_malloc_error_return_null(minish);
		return (NULL);
	}
	free(doc);
	free(line);
	return (ret);
}

static bool	is_break_readline(t_minishell *minish, char **doc, char *line,
		int idx)
{
	if (line == NULL)
		return (true);
	if (ft_strlen(line) == 0 && g_signal == CTRL_C)
	{
		free(*doc);
		free(line);
		*doc = NULL;
		g_signal = 0;
		return (true);
	}
	if (ft_strcmp(line, minish->heredoc.delimiters[idx]) == 0)
	{
		free(line);
		return (true);
	}
	return (false);
}

static int	read_heredoc(t_minishell *minish, int idx)
{
	char	*line;
	char	*doc;

	doc = (char *)ft_calloc(1, sizeof(char));
	if (!doc)
	{
		occurred_malloc_error_return_null(minish);
		return (1);
	}
	while (1)
	{
		line = readline(HEREDOC_PROMPT);
		if (is_break_readline(minish, &doc, line, idx))
			break ;
		line = expand_line(minish, line, doc, idx);
		if (!line)
			return (1);
		doc = join_line(minish, doc, line);
		if (!doc)
			return (1);
	}
	minish->heredoc.docs[idx] = doc;
	return (0);
}

void	input_heredoc(t_minishell *minish)
{
	size_t	i;

	if (!no_error(minish))
		return ;
	i = 0;
	while (i < minish->heredoc.num)
	{
		if (read_heredoc(minish, i))
			return ;
		if (minish->heredoc.docs[i] == NULL)
		{
			minish->error_kind = INTERRUPT;
			minish->status_code = 1;
			return ;
		}
		i++;
	}
}
