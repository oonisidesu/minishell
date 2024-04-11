/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:45:27 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/11 17:54:23 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser/expansion.h"
#include <stdlib.h>

static void	count_up_to_terminator(t_expansion *exp, t_inside_status in_status,
		char *terminator)
{
	if (in_status != IN_ANY && exp->in_status != in_status)
		return ;
	while (!expansion_done(exp))
	{
		if (ft_strchr(terminator, exp->str[exp->i]) != NULL)
		{
			break ;
		}
		exp->i++;
	}
}

int	join_up_to_terminator(t_expansion *exp, t_inside_status in_status,
		char *terminator)
{
	char	*word;
	char	*tmp;
	size_t	num;

	count_up_to_terminator(exp, in_status, terminator);
	num = exp->i - exp->n;
	if (num == 0)
		return (0);
	word = ft_substr(exp->str, exp->n, num);
	if (!word)
		return (free_expansion_and_return_error(exp));
	tmp = exp->ret;
	exp->ret = ft_strjoin(exp->ret, word);
	if (!exp->ret)
	{
		free(word);
		free(tmp);
		return (free_expansion_and_return_error(exp));
	}
	free(word);
	free(tmp);
	exp->n += num;
	return (0);
}

int	join_var(t_expansion *exp, const char *var, size_t var_len)
{
	char	*tmp;

	if (var != NULL && ft_strlen(var) > 0)
	{
		tmp = exp->ret;
		exp->ret = ft_strjoin(exp->ret, var);
		if (!exp->ret)
		{
			return (free_expansion_and_return_error(exp));
		}
		free(tmp);
	}
	exp->i += var_len;
	exp->n += var_len;
	return (0);
}
