/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:37:32 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/12 17:23:20 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser/expansion.h"
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/minishell_error.h"
#include "utils/utils.h"
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

static int	push_argv(t_minishell *minish, t_node *node, char *str)
{
	char	**tmp;

	if (node->argc + 1 >= node->capa)
	{
		tmp = node->argv;
		node->capa += ARGV_BLOCK;
		node->argv = (char **)ft_calloc(node->capa, sizeof(char *));
		if (!node->argv)
		{
			free_array((void **)tmp);
			occurred_malloc_error_return_null(minish);
			return (1);
		}
		copy_array((void **)tmp, (void **)node->argv);
		free(tmp);
	}
	node->argv[node->argc] = str;
	node->argc++;
	return (0);
}

static void	expand_and_set_argv(t_node *node, t_minishell *minish)
{
	char	**argv;
	int		i;

	argv = expand_argv(minish, minish->cur_token);
	if (!argv)
	{
		return ;
	}
	i = 0;
	while (argv[i])
	{
		if (push_argv(minish, node, argv[i]))
		{
			return ;
		}
		i++;
	}
	free(argv);
	minish->cur_token = minish->cur_token->next;
}

static void	parse_token(t_minishell *minish, t_node *node,
		t_node **redirect_cur, t_node **declare_cur)
{
	if (redirection(minish, redirect_cur))
		return ;
	if (node->argc == 0 && is_var_declaration(minish->cur_token->str,
			minish->cur_token->len))
	{
		declaration(minish, declare_cur);
		return ;
	}
	if (minish->cur_token->kind == TK_WORD)
	{
		expand_and_set_argv(node, minish);
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
