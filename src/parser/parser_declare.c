/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_declare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:37:32 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/09 14:13:49 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/expansion.h"
#include "parser/parser.h"
#include "utils/minishell_error.h"
#include <stdlib.h>

static int	set_key_val(t_minishell *minish, t_node *node, t_token *tok)
{
	char	*key_val;

	key_val = expand(minish, tok);
	if (!key_val)
	{
		free(node);
		return (1);
	}
	free(node->argv);
	node->argv = divide_key_val(key_val);
	if (!node->argv)
	{
		free(node);
		free(key_val);
		return (1);
	}
	free(key_val);
	return (0);
}

static t_node	*new_declare_node(t_node_kind kind, t_minishell *minish)
{
	t_node	*node;

	node = malloc_and_init_node(kind);
	if (!node)
	{
		return (occurred_malloc_error_return_null(minish));
	}
	if (set_key_val(minish, node, minish->cur_token))
	{
		return (occurred_malloc_error_return_null(minish));
	}
	minish->cur_token = minish->cur_token->next;
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
