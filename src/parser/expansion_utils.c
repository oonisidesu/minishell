/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:45:27 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/09 15:32:03 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser/expansion.h"
#include "utils/minishell_error.h"
#include "variable/env.h"
#include <parser/token.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

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

int	done(t_expansion *exp)
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
