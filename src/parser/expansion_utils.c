/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:45:27 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/10 12:16:20 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser/expansion.h"

int	init_expansion(t_expansion *exp, t_token *tok)
{
	exp->ret = (char *)ft_calloc(1, sizeof(char));
	if (!exp->ret)
		return (1);
	exp->str = tok->str;
	exp->len = tok->len;
	exp->i = 0;
	exp->n = 0;
	exp->in_status = IN_NONE;
	return (0);
}

int	expansion_done(t_expansion *exp)
{
	return (exp->i >= exp->len);
}

bool	is_special_param(t_expansion *exp)
{
	if (exp->str[exp->i] != '$')
		return (false);
	if (ft_isdigit(exp->str[exp->i + 1]) || exp->str[exp->i + 1] == '#'
		|| exp->str[exp->i + 1] == '$' || exp->str[exp->i + 1] == '*'
		|| exp->str[exp->i + 1] == '@' || exp->str[exp->i + 1] == '?'
		|| exp->str[exp->i + 1] == '-' || exp->str[exp->i + 1] == '!')
	{
		return (true);
	}
	return (false);
}

bool	has_quotes(t_token *tok)
{
	bool	has_s_quote;
	bool	has_d_quote;

	has_s_quote = ft_memchr(tok->str, '\'', tok->len) != NULL;
	has_d_quote = ft_memchr(tok->str, '\"', tok->len) != NULL;
	return (has_s_quote || has_d_quote);
}

void	update_inside_status(t_expansion *exp)
{
	if (exp->str[exp->i] == '\'')
	{
		if (exp->in_status == IN_NONE)
			exp->in_status = IN_QUOTE;
		else if (exp->in_status == IN_QUOTE)
			exp->in_status = IN_NONE;
		exp->i++;
		exp->n++;
	}
	else if (exp->str[exp->i] == '\"')
	{
		if (exp->in_status == IN_NONE)
			exp->in_status = IN_D_QUOTE;
		else if (exp->in_status == IN_D_QUOTE)
			exp->in_status = IN_NONE;
		exp->i++;
		exp->n++;
	}
}
