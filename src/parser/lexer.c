/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:20:20 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/08 16:17:43 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "message/message.h"
#include "minishell.h"
#include "parser/token.h"
#include "utils/minishell_error.h"
#include <stdbool.h>
#include <stdlib.h>

static void	new_token(t_minishell *minish, t_token_kind kind, char *str,
		size_t len)
{
	t_token	*tok;

	tok = (t_token *)malloc(sizeof(t_token));
	if (!tok)
	{
		occurred_malloc_error_return_null(minish);
		return ;
	}
	tok->kind = kind;
	tok->str = str;
	tok->len = len;
	tok->next = NULL;
	minish->cur_token->next = tok;
	minish->cur_token = tok;
}

static bool	is_starts_with(char *s1, char *s2, int len)
{
	return (ft_strncmp(s1, s2, len) == 0);
}

static int	error_at(t_minishell *minish, t_token *head, char *p)
{
	char	*space;
	char	*tab;
	size_t	len;

	tab = ft_strchr(p, '\t');
	space = ft_strchr(p, ' ');
	len = ft_strlen(p);
	if (tab - p > 0 && (space == 0 || tab < space))
		len = tab - p;
	if (space - p > 0 && (tab == 0 || space < tab))
		len = space - p;
	occurred_syntax_error(minish, p, len);
	free_tokens(head->next);
	return (EXIT_FAILURE);
}

static int	add_token(t_minishell *minish, char **p)
{
	ssize_t	word_len;

	if (is_starts_with("<<", *p, 2) || is_starts_with(">>", *p, 2))
	{
		new_token(minish, TK_RESERVED, *p, 2);
		*p += 2;
		return (1);
	}
	if (is_reserved(**p))
	{
		new_token(minish, TK_RESERVED, *p, 1);
		(*p)++;
		return (1);
	}
	word_len = count_token_word_len(*p);
	if (word_len > 0)
	{
		new_token(minish, TK_WORD, *p, word_len);
		*p += word_len;
		return (1);
	}
	return (0);
}

int	tokenize(t_minishell *minish)
{
	char	*p;
	t_token	head;

	head.next = NULL;
	minish->cur_token = &head;
	p = minish->line;
	while (*p && no_error(minish))
	{
		if (ft_isspace(*p))
		{
			p++;
			continue ;
		}
		if (add_token(minish, &p))
			continue ;
		return (error_at(minish, &head, p));
	}
	if (no_error(minish))
		new_token(minish, TK_EOF, p, 0);
	minish->token = head.next;
	return (!no_error(minish));
}
