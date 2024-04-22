/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_special.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:45:27 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/11 17:49:14 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser/expansion.h"
#include <stdlib.h>

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

int	expand_special_param(t_minishell *minish, t_expansion *exp)
{
	int		ret;
	char	*str;

	if (exp->str[exp->i] != '$')
		return (0);
	if (exp->str[exp->i + 1] == '0')
		return (join_var(exp, minish->argv[0], 2));
	else if (ft_isdigit(exp->str[exp->i + 1]) || exp->str[exp->i + 1] == '*'
		|| exp->str[exp->i + 1] == '@' || exp->str[exp->i + 1] == '-')
		return (join_var(exp, "", 2));
	else if (exp->str[exp->i + 1] == '#' || exp->str[exp->i + 1] == '!')
		return (join_var(exp, "0", 2));
	else if (exp->str[exp->i + 1] == '$')
		return (join_var(exp, "$", 1));
	else if (exp->str[exp->i + 1] == '?')
	{
		str = ft_itoa(minish->status_code);
		ret = join_var(exp, str, 2);
		free(str);
		return (ret);
	}
	return (0);
}
