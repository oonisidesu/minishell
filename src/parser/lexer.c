/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:20:20 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/17 16:27:07 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser/token.h"
#include <stdbool.h>
#include <stdlib.h>

/////////////// debug /////////////////////////////////////////////////
#include <stdio.h>

static void	print_tokens(t_token *tok)
{
	char	c;

	while (tok)
	{
		c = '0' + tok->kind;
		write(STDOUT_FILENO, &c, 1);
		write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, tok->str, tok->len);
		write(STDOUT_FILENO, "\n", 1);
		tok = tok->next;
	}
}
////////////////////////////////////////////////////////////////

// generate new token and connect to the current token
static t_token	*new_token(e_token_kind kind, t_token *cur, char *str,
		size_t len)
{
	t_token	*tok;

	tok = (t_token *)malloc(sizeof(t_token));
	// TODO エラー処理
	tok->kind = kind;
	tok->str = str;
	tok->len = len;
	cur->next = tok;
	return (tok);
}

static bool	is_starts_with(char *s1, char *s2, int len)
{
	return (ft_strncmp(s1, s2, len) == 0);
}

static bool	is_word_char_begin(char p)
{
	return (ft_isalpha(p) || p == '_' || p == '-');
}

static bool	is_word_char(char p)
{
	// TODO 一旦、全て空白で区切られていることを仮定。
	// 後で書き直す必要あり
	return (!ft_isspace(p) && p != '\n' && p != '\0');
}

static size_t	count_word_len(char *p)
{
	char	*q;

	q = p;
	if (is_word_char_begin(*p))
	{
		while (is_word_char(*p))
			p++;
	}
	return (p - q);
}

void	free_tokens(t_token *cur)
{
	t_token	*next;

	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
}

static int	error_at(t_token *head)
{
	ft_putstr_fd(CANNOT_TOKENIZE, STDERR_FILENO);
	free_tokens(head->next);
	return (EXIT_FAILURE);
}

int	tokenize(t_minishell *minish)
{
	char	*p;
	t_token	head;
	t_token	*cur;
	size_t	word_len;

	head.next = NULL;
	cur = &head;
	p = minish->line;
	while (*p)
	{
		if (ft_isspace(*p))
		{
			p++;
			continue ;
		}
		word_len = count_word_len(p);
		if (word_len)
		{
			cur = new_token(TK_WORD, cur, p, word_len);
			p += word_len;
			continue ;
		}
		if (is_starts_with("<<", p, 2) || is_starts_with(">>", p, 2))
		{
			cur = new_token(TK_RESERVED, cur, p, 2);
			p += 2;
			continue ;
		}
		if (ft_ispunct(*p))
		{
			cur = new_token(TK_RESERVED, cur, p, 1);
			p++;
			continue ;
		}
		return (error_at(&head));
	}
	new_token(TK_EOF, cur, p, 0);
	minish->token = head.next;
	///////////////////////////////////////
	// TODO 後で消す
	print_tokens(minish->token);
	///////////////////////////////////////
	return (EXIT_SUCCESS);
}
