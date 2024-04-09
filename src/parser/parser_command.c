/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:37:32 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/09 14:04:48 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/expansion.h"
#include "parser/parser.h"
#include "utils/minishell_error.h"
#include <stdlib.h>

static t_node	*new_command_node(t_minishell *minish)
{
	t_node	*node;

	node = malloc_and_init_node(ND_COMMAND);
	if (!node)
	{
		return (occurred_malloc_error_return_null(minish));
	}
	return (node);
}

static void	put_argv(t_node *node, t_minishell *minish)
{
	char	**argv;
	int		i;

	argv = expand_argv(minish, minish->cur_token);
	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		node->argv[node->argc] = argv[i];
		node->argc++;
		i++;
	}
	free(argv);
	minish->cur_token = minish->cur_token->next;
}

static void	parse_token(t_minishell *minish, t_node *node,
		t_node **redirect_cur, t_node **declare_cur)
{
	redirection(minish, redirect_cur);
	if (node->argc == 0 && is_var_declaration(minish->cur_token->str,
			minish->cur_token->len))
	{
		declaration(minish, declare_cur);
		return ;
	}
	if (minish->cur_token->kind == TK_WORD)
	{
		put_argv(node, minish);
	}
}

t_node	*command(t_minishell *minish)
{
	t_node	*node;
	t_node	redirect_head;
	t_node	*redirect_cur;
	t_node	declare_head;
	t_node	*declare_cur;

	node = new_command_node(minish);
	if (!node)
		return (NULL);
	redirect_head.next = NULL;
	redirect_cur = &redirect_head;
	declare_head.next = NULL;
	declare_cur = &declare_head;
	while (!at_eof(minish->cur_token) && !at_pipe(minish->cur_token)
		&& no_error(minish))
	{
		parse_token(minish, node, &redirect_cur, &declare_cur);
	}
	node->redirect = redirect_head.next;
	node->declare = declare_head.next;
	return (node);
}
