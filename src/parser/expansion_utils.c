/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:45:27 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/16 15:34:07 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser/expansion.h"
#include <stdlib.h>

int	init_expansion(t_expansion *exp, const char *str, size_t len)
{
	exp->capa = EXP_STR_INIT_SIZE;
	exp->ret = (char *)ft_calloc(exp->capa, sizeof(char));
	if (!exp->ret)
		return (1);
	exp->size = 0;
	exp->str = str;
	exp->len = len;
	exp->i = 0;
	exp->n = 0;
	exp->in_status = IN_NONE;
	return (0);
}

int	free_expansion_and_return_error(t_expansion *exp)
{
	free(exp->ret);
	return (1);
}

int	done_expansion(t_expansion *exp)
{
	return (exp->i >= exp->len);
}
