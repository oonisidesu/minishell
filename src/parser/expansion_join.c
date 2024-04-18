/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:45:27 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/17 19:51:19 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser/expansion.h"
#include "utils/utils.h"
#include <stdlib.h>

static void	count_up_to_terminator(t_expansion *exp, t_inside_status in_status,
		char *terminator)
{
	if (in_status != IN_ANY && exp->in_status != in_status)
		return ;
	while (!done_expansion(exp))
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
	size_t	num;

	count_up_to_terminator(exp, in_status, terminator);
	num = exp->i - exp->n;
	if (exp->in_status == IN_NONE && num == 0)
		return (0);
	if (push_exp_string(exp, exp->str + exp->n, num))
		return (1);
	exp->n += num;
	return (0);
}

int	join_var(t_expansion *exp, const char *var, size_t var_len)
{
	if (var)
	{
		if (push_exp_string(exp, var, ft_strlen(var)))
			return (1);
	}
	exp->i += var_len;
	exp->n += var_len;
	return (0);
}

static int	push_arr_i(t_expansion *exp, const char *str, const char *next)
{
	if (push_exp_string(exp, str, ft_strlen(str)))
	{
		return (1);
	}
	if (next != NULL)
	{
		if (add_exp_array(exp))
		{
			return (1);
		}
	}
	return (0);
}

int	split_and_join_var(t_expansion *exp, const char *var, size_t var_len)
{
	size_t	i;
	char	**arr;

	if (var)
	{
		arr = ft_split2(var, " \t");
		if (arr == NULL)
			return (free_expansion_and_return_error(exp));
		i = 0;
		while (arr[i])
		{
			if (push_arr_i(exp, arr[i], arr[i + 1]))
			{
				free_array((void **)arr);
				return (1);
			}
			i++;
		}
		free_array((void **)arr);
	}
	exp->i += var_len;
	exp->n += var_len;
	return (0);
}
