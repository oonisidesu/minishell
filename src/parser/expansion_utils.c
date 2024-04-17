/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:45:27 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/17 15:00:25 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser/expansion.h"
#include "utils/utils.h"
#include <stdlib.h>

int	init_expansion(t_expansion *exp, const char *str, size_t len)
{
	exp->arr_ret = (char **)ft_calloc(EXP_INIT_SIZE, sizeof(char *));
	if (!exp->arr_ret)
		return (1);
	exp->ret = (char *)ft_calloc(EXP_INIT_SIZE, sizeof(char));
	if (!exp->ret)
		return (1);
	exp->capa = EXP_INIT_SIZE;
	exp->size = 0;
	exp->arr_capa = EXP_INIT_SIZE;
	exp->arr_size = 1;
	exp->arr_ret[0] = exp->ret;
	exp->str = str;
	exp->len = len;
	exp->i = 0;
	exp->n = 0;
	exp->in_status = IN_NONE;
	return (0);
}

int	free_expansion_and_return_error(t_expansion *exp)
{
	free_array((void **)exp->arr_ret);
	return (1);
}

int	done_expansion(t_expansion *exp)
{
	return (exp->i >= exp->len);
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
