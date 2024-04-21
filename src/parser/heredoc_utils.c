/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootsubo <yootsubo@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:43:15 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/21 18:28:40 by yootsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "message/message.h"
#include "minishell.h"
#include "parser/expansion.h"
#include "utils/exit_status.h"
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

static bool	is_node_expansion(t_token *tok)
{
	char	*single_quote_p;
	char	*double_quote_p;
	bool	is_node_expansion;

	single_quote_p = ft_memchr(tok->str, '\'', tok->len);
	double_quote_p = ft_memchr(tok->str, '\"', tok->len);
	if ((single_quote_p == NULL) && (double_quote_p == NULL))
		is_node_expansion = true;
	else
		is_node_expansion = false;
	return (is_node_expansion);
}

int	set_heredoc_delimiter(t_minishell *minish, t_token *tok)
{
	int	idx;

	if (minish->heredoc.num >= MAX_HEREDOC)
	{
		ft_printf_fd(STDERR_FILENO, ERROR_MAX_HEREDOC);
		die_minishell_and_exit(minish, EXIT_MAX_HEREDOC);
	}
	idx = minish->heredoc.num;
	minish->heredoc.num++;
	minish->heredoc.delimiters[idx] = expand_delimiter(minish, tok);
	if (minish->heredoc.delimiters[idx] == NULL)
	{
		return (-1);
	}
	minish->heredoc.need_expansion[idx] = is_node_expansion(tok);
	return (idx);
}
