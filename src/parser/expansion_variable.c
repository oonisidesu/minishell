/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:45:27 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/16 13:52:13 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser/expansion.h"
#include "utils/minishell_error.h"
#include "variable/env.h"
#include <stdlib.h>

static char	*extract_key(t_minishell *minish, t_expansion *exp)
{
	size_t	len;
	char	*key;

	if (exp->str[exp->i] != '$')
	{
		return (NULL);
	}
	if (!(exp->str[exp->i + 1] == '_' || ft_isalpha(exp->str[exp->i + 1])))
	{
		return (NULL);
	}
	exp->i += 2;
	while (!done_expansion(exp) && (ft_isalnum(exp->str[exp->i])
			|| exp->str[exp->i] == '_'))
	{
		exp->i++;
	}
	len = exp->i - (exp->n + 1);
	key = ft_substr(exp->str, exp->n + 1, len);
	if (!key)
	{
		return (occurred_malloc_error_return_null(minish));
	}
	exp->n = exp->i;
	return (key);
}

int	consume_and_join_dollar(t_expansion *exp)
{
	if (exp->str[exp->i] == '$')
	{
		return (join_var(exp, "$", 1));
	}
	return (0);
}

int	expand_variable(t_minishell *minish, t_expansion *exp)
{
	int		ret;
	char	*key;

	if (!(exp->in_status == IN_NONE || exp->in_status == IN_D_QUOTE))
	{
		return (0);
	}
	if (is_special_param(exp))
	{
		return (0);
	}
	key = extract_key(minish, exp);
	if (!no_error(minish))
	{
		free(key);
		return (free_expansion_and_return_error(exp));
	}
	if (!key)
	{
		return (consume_and_join_dollar(exp));
	}
	ret = join_var(exp, get_var(minish, key), 0);
	free(key);
	return (ret);
}
