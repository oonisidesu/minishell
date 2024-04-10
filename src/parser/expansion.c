/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:45:27 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/10 12:18:09 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser/expansion.h"
#include "utils/minishell_error.h"
#include <stdlib.h>

char	*expand(t_minishell *minish, t_token *tok)
{
	t_expansion	exp;

	if (init_expansion(&exp, tok))
	{
		return (NULL);
	}
	while (!expansion_done(&exp))
	{
		update_inside_status(&exp);
		if (expand_special_param(minish, &exp))
			return (NULL);
		if (expand_variable(minish, &exp))
			return (NULL);
		if (join_up_to_terminator(&exp, IN_NONE, "\'\"$"))
			return (NULL);
		if (join_up_to_terminator(&exp, IN_QUOTE, "\'"))
			return (NULL);
		if (join_up_to_terminator(&exp, IN_D_QUOTE, "\"$"))
			return (NULL);
	}
	return (exp.ret);
}

char	**expand_argv(t_minishell *minish, t_token *tok)
{
	char	**ret;
	char	*expanded;

	expanded = expand(minish, tok);
	if (!expanded)
		return (occurred_malloc_error_return_null(minish));
	if (has_quotes(tok))
	{
		ret = (char **)ft_calloc(2, sizeof(char *));
		if (!ret)
		{
			free(expanded);
			return (occurred_malloc_error_return_null(minish));
		}
		ret[0] = expanded;
		return (ret);
	}
	ret = ft_split2(expanded, " \t");
	free(expanded);
	if (!ret)
	{
		return (occurred_malloc_error_return_null(minish));
	}
	return (ret);
}

char	*expand_redirect(t_minishell *minish, t_token *tok)
{
	char	*ret;
	char	*tmp;

	ret = expand(minish, tok);
	if (!ret)
		return (occurred_malloc_error_return_null(minish));
	if (has_quotes(tok))
		return (ret);
	tmp = ret;
	ret = ft_strtrim(ret, " \t");
	free(tmp);
	if (!ret)
	{
		return (occurred_malloc_error_return_null(minish));
	}
	if (ft_strchr(ret, ' ') != NULL || ft_strchr(ret, '\t') != NULL)
	{
		occurred_redirect_error(minish, tok);
		free(ret);
		return (NULL);
	}
	return (ret);
}

char	*expand_delimiter(t_minishell *minish, t_token *tok)
{
	t_expansion	exp;

	if (init_expansion(&exp, tok))
	{
		return (occurred_malloc_error_return_null(minish));
	}
	while (!expansion_done(&exp))
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
	return (exp.ret);
}

char	*expand_heredoc(t_minishell *minish, const char *str)
{
	t_expansion	exp;
	t_token		tok;

	tok.str = str;
	tok.len = ft_strlen(str);
	if (init_expansion(&exp, &tok))
	{
		return (occurred_malloc_error_return_null(minish));
	}
	while (!expansion_done(&exp))
	{
		if (expand_special_param(minish, &exp))
			return (occurred_malloc_error_return_null(minish));
		if (expand_variable(minish, &exp))
			return (occurred_malloc_error_return_null(minish));
		if (join_up_to_terminator(&exp, IN_ANY, "$"))
			return (occurred_malloc_error_return_null(minish));
	}
	return (exp.ret);
}
