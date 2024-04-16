/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:45:27 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/16 16:23:40 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser/expansion.h"
#include <stdlib.h>

int	push_string(t_expansion *exp, const char *str, size_t len)
{
	char	*tmp;

	if (exp->size + len + 1 > exp->capa)
	{
		while (exp->size + len + 1 > exp->capa)
			exp->capa *= 2;
		tmp = exp->ret;
		exp->ret = ft_calloc(exp->capa, sizeof(char));
		if (!exp->ret)
		{
			free(tmp);
			return (free_expansion_and_return_error(exp));
		}
		ft_memcpy(exp->ret, tmp, exp->size);
		free(tmp);
	}
	ft_strlcpy(exp->ret + exp->size, str, len + 1);
	exp->size += len;
	return (0);
}
