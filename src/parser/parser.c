/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:37:32 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/31 16:32:15 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "message/message.h"
#include "minishell.h"
#include "parser/expansion.h"
#include "parser/heredoc.h"
#include "parser/parser.h"
#include "utils/minishell_error.h"
#include <stdlib.h>
#include <unistd.h>

/////////////// debug /////////////////////////////////////////////////
// #include <stdio.h>

// static void	print_nodes(t_node *node)
// {
// 	int		i;
// 	t_node	*r;

// 	printf("=== node ==================================\n");
// 	while (node)
// 	{
// 		printf("--node(argc: %d)--------------\n", node->argc);
// 		for (int i = 0; i < node->argc; i++)
// 		{
// 			printf("argv[%d]: %s\n", i, node->argv[i]);
// 		}
// 		i = 0;
// 		r = node->redirect;
// 		while (r)
// 		{
// 			printf("redirect[%d]: [%d] %s\n", i, r->kind, r->path);
// 			i++;
// 			r = r->next;
// 		}
// 		printf("------------------------------\n");
// 		node = node->next;
// 	}
// }
////////////////////////////////////////////////////////////////

static t_node	*malloc_and_init_node(e_node_kind kind)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
	{
		return (NULL);
	}
	// TODO 固定長になっているので、後で可変にする
	node->argv = (char **)malloc(sizeof(char *) * 100);
	if (node->argv == NULL)
	{
		free(node);
		return (NULL);
	}
	node->kind = kind;
	node->argc = 0;
	node->wait_status = -1;
	node->pid = -1;
	node->path = NULL;
	node->has_x = false;
	node->exist_cmd = false;
	node->redirect = NULL;
	node->declare = NULL;
	node->next = NULL;
	return (node);
}

static t_node	*new_redirect_node(e_node_kind kind, t_minishell *minish)
{
	t_node	*node;
	t_token	*tok;

	tok = minish->cur_token;
	node = malloc_and_init_node(kind);
	if (!node)
	{
		return (occurred_malloc_error_return_null(minish));
	}
	if (kind == ND_HEREDOC)
	{
		node->heredoc_idx = set_heredoc_delimiter(minish, tok);
		if (node->heredoc_idx < 0)
		{
			return (NULL);
		}
	}
	else
	{
		node->path = expand_redirect(minish, tok);
		if (!node->path)
		{
			free_nodes(node);
			return (NULL);
		}
	}
	minish->cur_token = tok->next;
	return (node);
}

static t_node	*new_declare_node(e_node_kind kind, t_minishell *minish)
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

static bool	consume(t_minishell *minish, char *op)
{
	t_token	*token;

	token = minish->cur_token;
	if (token->kind != TK_RESERVED || ft_strlen(op) != token->len
		|| ft_strncmp(op, token->str, token->len))
		return (false);
	minish->cur_token = token->next;
	return (true);
}

static bool	expect_word(t_minishell *minish)
{
	if (minish->cur_token->kind == TK_WORD)
	{
		return (true);
	}
	occurred_syntax_error(minish, minish->cur_token->str,
		minish->cur_token->len);
	return (false);
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

static bool	at_eof(t_token *tok)
{
	return (tok->kind == TK_EOF);
}

static bool	at_pipe(t_token *tok)
{
	return (tok->kind == TK_RESERVED && tok->len == 1 && tok->str[0] == '|');
}

static void	redirection(t_minishell *minish, t_node **redirect_cur)
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
}

static void	declaration(t_minishell *minish, t_node **declare_cur)
{
	t_node	*node;

	node = new_declare_node(ND_DECLARE, minish);
	if (node)
	{
		(*declare_cur)->next = node;
		*declare_cur = node;
	}
}

static t_node	*command(t_minishell *minish)
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
		redirection(minish, &redirect_cur);
		if (node->argc == 0 && is_var_declaration(minish->cur_token->str,
				minish->cur_token->len))
		{
			declaration(minish, &declare_cur);
			continue ;
		}
		if (minish->cur_token->kind == TK_WORD)
		{
			put_argv(node, minish);
		}
	}
	node->redirect = redirect_head.next;
	node->declare = declare_head.next;
	return (node);
}

int	parse(t_minishell *minish)
{
	t_node	head;
	t_node	*cur;
	t_node	*node;

	minish->error_kind = ERR_NONE;
	minish->cur_token = minish->token;
	head.next = NULL;
	cur = &head;
	if (at_pipe(minish->cur_token))
	{
		occurred_syntax_error(minish, minish->cur_token->str,
			minish->cur_token->len);
	}
	while (!at_eof(minish->cur_token) && no_error(minish))
	{
		node = command(minish);
		if (!node)
			return (1);
		if (at_pipe(minish->cur_token) && (at_pipe(minish->cur_token->next)
				|| at_eof(minish->cur_token->next)))
		{
			occurred_syntax_error(minish, minish->cur_token->str,
				minish->cur_token->len);
			break ;
		}
		consume(minish, "|");
		cur->next = node;
		cur = node;
	}
	minish->node = head.next;
	input_heredoc(minish);
	///////////////////////////////////////
	// TODO 後で消す
	// print_nodes(minish->node);
	///////////////////////////////////////
	return (!no_error(minish));
}
