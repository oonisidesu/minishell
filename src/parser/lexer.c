/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:20:20 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/19 17:17:43 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "message/message.h"
#include "minishell.h"
#include "parser/token.h"
#include <stdbool.h>
#include <stdlib.h>

/////////////// debug /////////////////////////////////////////////////
// #include <stdio.h>

// static void	print_tokens(t_token *tok)
// {
// 	char	c;

// 	printf("=== token ==================================\n");
// 	while (tok)
// 	{
// 		c = '0' + tok->kind;
// 		write(STDOUT_FILENO, &c, 1);
// 		write(STDOUT_FILENO, " ", 1);
// 		write(STDOUT_FILENO, tok->str, tok->len);
// 		write(STDOUT_FILENO, "\n", 1);
// 		tok = tok->next;
// 	}
// }
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
	tok->next = NULL;
	cur->next = tok;
	return (tok);
}

static bool	is_starts_with(char *s1, char *s2, int len)
{
	return (ft_strncmp(s1, s2, len) == 0);
}

static bool	is_reserved(char p)
{
	return (p == '<' || p == '>' || p == '|' || p == ';');
}

static e_inside_status	update_in_status(char p, e_inside_status in_status)
{
	if (p == '\'')
	{
		if (in_status == IN_QUOTE)
			return (IN_NONE);
		else if (in_status == IN_NONE)
			return (IN_QUOTE);
	}
	else if (p == '\"')
	{
		if (in_status == IN_D_QUOTE)
			return (IN_NONE);
		else if (in_status == IN_NONE)
			return (IN_D_QUOTE);
	}
	return (in_status);
}

static bool	is_word_char(char p, e_inside_status in_status)
{
	if (in_status == IN_QUOTE)
	{
		return (true);
	}
	else if (in_status == IN_D_QUOTE)
	{
		return (true);
	}
	return (!ft_isspace(p) && !is_reserved(p));
}

static ssize_t	count_word_len(char *p)
{
	char			*q;
	e_inside_status	in_status;

	bool is_continue ;
	in_status = IN_NONE;
	q = p;
	while (*p != '\n' && *p != '\0')
	{
		is_continue = is_word_char(*p, in_status);
		in_status = update_in_status(*p, in_status);
		if (!is_continue)
			break ;
		p++;
	}
	if (in_status != IN_NONE)
	{
		// "、'が閉じられていない
		return (-1);
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
	ft_printf_fd(STDERR_FILENO, CANNOT_TOKENIZE);
	free_tokens(head->next);
	return (EXIT_FAILURE);
}

int	tokenize(t_minishell *minish)
{
	char	*p;
	t_token	head;
	t_token	*cur;
	ssize_t	word_len;

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
		if (is_starts_with("<<", p, 2) || is_starts_with(">>", p, 2))
		{
			cur = new_token(TK_RESERVED, cur, p, 2);
			p += 2;
			continue ;
		}
		if (is_reserved(*p))
		{
			cur = new_token(TK_RESERVED, cur, p, 1);
			p++;
			continue ;
		}
		word_len = count_word_len(p);
		if (word_len > 0)
		{
			cur = new_token(TK_WORD, cur, p, word_len);
			p += word_len;
			continue ;
		}
		return (error_at(&head));
	}
	new_token(TK_EOF, cur, p, 0);
	minish->token = head.next;
	///////////////////////////////////////
	// TODO 後で消す
	// print_tokens(minish->token);
	///////////////////////////////////////
	return (EXIT_SUCCESS);
}
