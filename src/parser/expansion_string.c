/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:45:27 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/17 14:31:41 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser/expansion.h"
#include "utils/utils.h"
#include <stdlib.h>

int	push_exp_string(t_expansion *exp, const char *str, size_t len)
{
	char	*tmp;

	if (exp->size + len + 1 > exp->capa)
	{
		while (exp->size + len + 1 > exp->capa)
			exp->capa *= 2;
		tmp = exp->ret;
		exp->ret = (char *)ft_calloc(exp->capa, sizeof(char));
		if (!exp->ret)
		{
			free(tmp);
			return (free_expansion_and_return_error(exp));
		}
		ft_memcpy(exp->ret, tmp, exp->size);
		free(tmp);
		exp->arr_ret[exp->arr_size - 1] = exp->ret;
	}
	ft_strlcpy(exp->ret + exp->size, str, len + 1);
	exp->size += len;
	return (0);
}

int	add_exp_array(t_expansion *exp)
{
	char	**tmp;

	if (exp->arr_size + 1 >= exp->arr_capa)
	{
		exp->arr_capa *= 2;
		tmp = exp->arr_ret;
		exp->arr_ret = (char **)ft_calloc(exp->arr_capa, sizeof(char *));
		if (!exp->arr_ret)
		{
			free_array((void **)tmp);
			return (free_expansion_and_return_error(exp));
		}
		copy_array((void **)tmp, (void **)exp->arr_ret);
		free(tmp);
	}
	exp->ret = (char *)ft_calloc(EXP_INIT_SIZE, sizeof(char));
	if (!exp->ret)
		return (free_expansion_and_return_error(exp));
	exp->capa = EXP_INIT_SIZE;
	exp->size = 0;
	exp->arr_ret[exp->arr_size] = exp->ret;
	exp->arr_size += 1;
	return (0);
}
