/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:45:27 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/19 17:25:59 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser/expansion.h"
#include "utils/minishell_error.h"
#include "utils/utils.h"
#include <stdlib.h>

char	*expand(t_minishell *minish, t_token *tok)
{
	t_expansion	exp;

	if (init_expansion(&exp, tok->str, tok->len))
	{
		return (NULL);
	}
	while (!done_expansion(&exp))
	{
		update_inside_status(&exp);
		if (expand_special_param(minish, &exp))
			return (NULL);
		if (expand_variable(minish, &exp, false))
			return (NULL);
		if (join_up_to_terminator(&exp, IN_NONE, "\'\"$"))
			return (NULL);
		if (join_up_to_terminator(&exp, IN_QUOTE, "\'"))
			return (NULL);
		if (join_up_to_terminator(&exp, IN_D_QUOTE, "\"$"))
			return (NULL);
	}
	free(exp.arr_ret);
	return (exp.ret);
}

char	**expand_split(t_minishell *minish, t_token *tok)
{
	t_expansion	exp;

	if (init_expansion(&exp, tok->str, tok->len))
	{
		return (NULL);
	}
	while (!done_expansion(&exp))
	{
		update_inside_status(&exp);
		if (expand_special_param(minish, &exp))
			return (NULL);
		if (expand_variable(minish, &exp, exp.in_status == IN_NONE))
			return (NULL);
		if (join_up_to_terminator(&exp, IN_NONE, "\'\"$"))
			return (NULL);
		if (join_up_to_terminator(&exp, IN_QUOTE, "\'"))
			return (NULL);
		if (join_up_to_terminator(&exp, IN_D_QUOTE, "\"$"))
			return (NULL);
	}
	return (exp.arr_ret);
}

char	*expand_redirect(t_minishell *minish, t_token *tok)
{
	char	*ret;
	char	**arr;
	size_t	count;

	arr = expand_split(minish, tok);
	if (!arr)
		return (occurred_malloc_error_return_null(minish));
	count = 0;
	while (arr[count])
		count++;
	if (count != 1)
	{
		occurred_redirect_error(minish, tok);
		free_array((void **)arr);
		return (NULL);
	}
	ret = arr[0];
	free(arr);
	return (ret);
}

char	*expand_delimiter(t_minishell *minish, t_token *tok)
{
	t_expansion	exp;

	if (init_expansion(&exp, tok->str, tok->len))
	{
		return (occurred_malloc_error_return_null(minish));
	}
	while (!done_expansion(&exp))
	{
		update_inside_status(&exp);
		if (join_up_to_terminator(&exp, IN_NONE, "\'\"$"))
			return (occurred_malloc_error_return_null(minish));
		if (consume_and_join_dollar(&exp))
			return (occurred_malloc_error_return_null(minish));
		if (join_up_to_terminator(&exp, IN_QUOTE, "\'"))
			return (occurred_malloc_error_return_null(minish));
		if (join_up_to_terminator(&exp, IN_D_QUOTE, "\"$"))
			return (occurred_malloc_error_return_null(minish));
	}
	free(exp.arr_ret);
	return (exp.ret);
}

char	*expand_heredoc(t_minishell *minish, const char *str)
{
	t_expansion	exp;

	if (init_expansion(&exp, str, ft_strlen(str)))
	{
		return (occurred_malloc_error_return_null(minish));
	}
	exp.in_heredoc = true;
	while (!done_expansion(&exp))
	{
		if (expand_special_param(minish, &exp))
			return (occurred_malloc_error_return_null(minish));
		if (expand_variable(minish, &exp, false))
			return (occurred_malloc_error_return_null(minish));
		if (join_up_to_terminator(&exp, IN_ANY, "$"))
			return (occurred_malloc_error_return_null(minish));
	}
	free(exp.arr_ret);
	return (exp.ret);
}
