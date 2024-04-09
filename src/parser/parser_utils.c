/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:37:32 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/09 12:57:25 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utils/minishell_error.h"

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
	occurred_syntax_error(minish, minish->cur_token->str,
		minish->cur_token->len);
	return (false);
}

bool	at_eof(t_token *tok)
{
	return (tok->kind == TK_EOF);
}

bool	at_pipe(t_token *tok)
{
	return (tok->kind == TK_RESERVED && tok->len == 1 && tok->str[0] == '|');
}
