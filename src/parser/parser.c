/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:37:32 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/21 22:16:42 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser/parser.h"
#include <stdlib.h>
#include <unistd.h>

/////////////// debug /////////////////////////////////////////////////
#include <stdio.h>

static void	print_nodes(t_node *node)
{
	int		i;
	t_node	*r;

	printf("=== node ==================================\n");
	while (node)
	{
		printf("--node(argc: %d)--------------\n", node->argc);
		for (int i = 0; i < node->argc; i++)
		{
			printf("argv[%d]: %s\n", i, node->argv[i]);
		}
		i = 0;
		r = node->redirect;
		while (r)
		{
			printf("redirect[%d]: [%d] %s\n", i, r->kind, r->path);
			i++;
			r = r->next;
		}
		printf("------------------------------\n");
		node = node->next;
	}
}
////////////////////////////////////////////////////////////////

t_node	*malloc_and_init_node(e_node_kind kind)
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
	node->next = NULL;
	return (node);
}

t_node	*new_redirect_node(e_node_kind kind, t_minishell *minish)
{
	t_node	*node;
	t_token	*t;

	t = minish->cur_token;
	node = malloc_and_init_node(kind);
	// TODO エラー処理ちゃんと書く
	if (!node)
	{
		minish->error_kind = ERR_MALLOC;
		return (NULL);
	}
	node->path = ft_substr(t->str, 0, t->len);
	// TODO エラー処理 ft_substrの中でmalloc
	minish->cur_token = t->next;
	return (node);
}

t_node	*new_command_node(t_minishell *minish)
{
	t_node	*node;

	node = malloc_and_init_node(ND_COMMAND);
	// TODO エラー処理ちゃんと書く
	if (!node)
	{
		minish->error_kind = ERR_MALLOC;
		return (NULL);
	}
	return (node);
}

bool	consume(t_minishell *minish, char *op)
{
	t_token	*token;

	token = minish->cur_token;
	if (token->kind != TK_RESERVED || ft_strlen(op) != token->len
		|| ft_strncmp(op, token->str, token->len))
		return (false);
	minish->cur_token = token->next;
	return (true);
}

bool	expect_word(t_minishell *minish)
{
	if (minish->cur_token->kind == TK_WORD)
	{
		return (true);
	}
	// TODO syntax error
	minish->error_kind = ERR_SYNTAX;
	return (false);
}
bool	occurred_syntax_error(t_minishell *minish)
{
	if (minish->error_kind == ERR_SYNTAX)
	{
		ft_printf_fd(STDERR_FILENO, SYNTAX_ERROR);
		write(STDERR_FILENO, "`", 1);
		write(STDERR_FILENO, minish->cur_token->str, minish->cur_token->len);
		write(STDERR_FILENO, "'\n", 2);
		return (true);
	}
	return (false);
}

void	put_argv(t_node *node, t_minishell *minish)
{
	node->argv[node->argc] = ft_substr(minish->cur_token->str, 0,
			minish->cur_token->len);
	// TODO エラー処理
	node->argc++;
	minish->cur_token = minish->cur_token->next;
}

bool	at_eof(t_minishell *minish)
{
	return (minish->cur_token->kind == TK_EOF);
}

bool	at_pipe(t_minishell *minish)
{
	return (minish->cur_token->kind == TK_RESERVED
		&& minish->cur_token->len == 1 && minish->cur_token->str[0] == '|');
}

void	redirection(t_minishell *minish, t_node **redirect_cur)
{
	t_node	*node;

	node = NULL;
	if (consume(minish, ">") && expect_word(minish))
	{
		node = new_redirect_node(ND_REDIRECT_OUT, minish);
	}
	else if (consume(minish, ">>") && expect_word(minish))
	{
		node = new_redirect_node(ND_REDIRECT_APPEND, minish);
	}
	else if (consume(minish, "<") && expect_word(minish))
	{
		node = new_redirect_node(ND_REDIRECT_IN, minish);
	}
	else if (consume(minish, "<<") && expect_word(minish))
	{
		node = new_redirect_node(ND_HEREDOC, minish);
	}
	if (node)
	{
		(*redirect_cur)->next = node;
		*redirect_cur = node;
	}
}

t_node	*command(t_minishell *minish)
{
	t_node	*node;
	t_node	redirect_head;
	t_node	*redirect_cur;

	node = new_command_node(minish);
	redirect_head.next = NULL;
	redirect_cur = &redirect_head;
	while (!at_eof(minish) && !at_pipe(minish))
	{
		redirection(minish, &redirect_cur);
		if (minish->cur_token->kind == TK_WORD)
		{
			put_argv(node, minish);
		}
	}
	node->redirect = redirect_head.next;
	consume(minish, "|");
	return (node);
}

int	parse(t_minishell *minish)
{
	t_node	head;
	t_node	*cur;
	t_node	*node;
	int		i;

	minish->error_kind = ERR_NONE;
	minish->cur_token = minish->token;
	cur = &head;
	i = 0;
	while (!at_eof(minish) && !occurred_syntax_error(minish) && i < 5)
	{
		node = command(minish);
		cur->next = node;
		cur = node;
		i++;
	}
	minish->node = head.next;
	///////////////////////////////////////
	// TODO 後で消す
	print_nodes(minish->node);
	///////////////////////////////////////
	return (0);
}
