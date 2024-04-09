/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_declare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:37:32 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/09 13:05:25 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/expansion.h"
#include "parser/parser.h"
#include "utils/minishell_error.h"
#include <stdlib.h>

static t_node	*new_declare_node(t_node_kind kind, t_minishell *minish)
{
	t_node	*node;
	t_token	*tok;
	char	*key_val;

	tok = minish->cur_token;
	node = malloc_and_init_node(kind);
	if (!node)
	{
		return (occurred_malloc_error_return_null(minish));
	}
	key_val = expand(minish, tok);
	if (!key_val)
	{
		free(node);
		return (occurred_malloc_error_return_null(minish));
	}
	free(node->argv);
	node->argv = divide_key_val(key_val);
	if (!node->argv)
	{
		free(node);
		free(key_val);
		return (occurred_malloc_error_return_null(minish));
	}
	free(key_val);
	minish->cur_token = tok->next;
	return (node);
}

void	declaration(t_minishell *minish, t_node **declare_cur)
{
	t_node	*node;

	node = new_declare_node(ND_DECLARE, minish);
	if (node)
	{
		(*declare_cur)->next = node;
		*declare_cur = node;
	}
}
