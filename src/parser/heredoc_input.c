/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:43:15 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/08 12:08:20 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "message/message.h"
#include "parser/expansion.h"
#include "readline.h"
#include "utils/minishell_error.h"
#include <stdio.h>
#include <stdlib.h>

static int	read_heredoc(t_minishell *minish, int idx)
{
	char	*line;
	char	*tmp;
	char	*doc;

	// char	*tmp;
	doc = (char *)ft_calloc(1, sizeof(char));
	if (!doc)
	{
		occurred_malloc_error_return_null(minish);
		return (1);
	}
	while (1)
	{
		line = readline(HEREDOC_PROMPT);
		if (line == NULL)
			break ;
		// ctrl + Cの場合
		if (ft_strlen(line) == 0)
		{
			free(doc);
			free(line);
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
			line = expand_heredoc(minish, line);
			if (!line)
			{
				free(tmp);
				free(doc);
				return (1);
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
			occurred_malloc_error_return_null(minish);
			return (1);
		}
		free(tmp);
		free(line);
	}
	minish->heredoc.docs[idx] = doc;
	return (0);
}

void	input_heredoc(t_minishell *minish)
{
	size_t	i;

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
