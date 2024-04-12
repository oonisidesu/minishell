/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:37:32 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/12 17:23:13 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/expansion.h"
#include "parser/heredoc.h"
#include "parser/parser.h"
#include "utils/minishell_error.h"

static int	set_redirect_path(t_minishell *minish, t_node_kind kind,
		t_node *node, t_token *tok)
{
	if (kind == ND_HEREDOC)
	{
		node->heredoc_idx = set_heredoc_delimiter(minish, tok);
		if (node->heredoc_idx < 0)
		{
			return (1);
		}
	}
	else
	{
		node->path = expand_redirect(minish, tok);
		if (!node->path)
		{
			free_nodes(node);
			return (1);
		}
	}
	return (0);
}

static t_node	*new_redirect_node(t_node_kind kind, t_minishell *minish)
{
	t_node	*node;

	node = malloc_and_init_node(kind);
	if (!node)
	{
		return (occurred_malloc_error_return_null(minish));
	}
	if (set_redirect_path(minish, kind, node, minish->cur_token))
	{
		return (NULL);
	}
	minish->cur_token = minish->cur_token->next;
	return (node);
}

int	redirection(t_minishell *minish, t_node **redirect_cur)
{
	t_node	*node;

	node = NULL;
	if (consume(minish, ">") && expect_word(minish) && no_error(minish))
	{
		node = new_redirect_node(ND_REDIRECT_OUT, minish);
	}
	else if (consume(minish, ">>") && expect_word(minish) && no_error(minish))
	{
		node = new_redirect_node(ND_REDIRECT_APPEND, minish);
	}
	else if (consume(minish, "<") && expect_word(minish) && no_error(minish))
	{
		node = new_redirect_node(ND_REDIRECT_IN, minish);
	}
	else if (consume(minish, "<<") && expect_word(minish) && no_error(minish))
	{
		node = new_redirect_node(ND_HEREDOC, minish);
	}
	if (node)
	{
		(*redirect_cur)->next = node;
		*redirect_cur = node;
	}
	return (!no_error(minish));
}
