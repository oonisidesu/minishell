/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:37:32 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/15 10:32:05 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/heredoc.h"
#include "parser/parser.h"
#include "utils/minishell_error.h"

static bool	check_syntax(t_minishell *minish)
{
	if (!no_error(minish))
		return (false);
	if (at_pipe(minish->cur_token) && (at_pipe(minish->cur_token->next)
			|| at_eof(minish->cur_token->next)))
	{
		occurred_syntax_error(minish, minish->cur_token->str,
			minish->cur_token->len);
		return (false);
	}
	return (true);
}

int	parse(t_minishell *minish)
{
	t_node	head;
	t_node	*cur;
	t_node	*node;

	minish->cur_token = minish->token;
	head.next = NULL;
	cur = &head;
	if (at_pipe(minish->cur_token))
		occurred_syntax_error(minish, minish->cur_token->str,
			minish->cur_token->len);
	while (!at_eof(minish->cur_token) && no_error(minish))
	{
		node = command(minish);
		if (!node)
			break ;
		cur->next = node;
		cur = node;
		if (!check_syntax(minish))
			break ;
		consume(minish, "|");
	}
	minish->node = head.next;
	input_heredoc(minish);
	return (!no_error(minish));
}
