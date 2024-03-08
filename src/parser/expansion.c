/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:45:27 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/08 17:20:24 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser/expansion.h"
#include <parser/token.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// char	*extract_key(char *str)
// {
// }

// char	*special_param(char *s)
// {
// 	if (s[0] == '$')
// 	{
// 		if (ft_isdigit(s[1]))
// 		{
// 			// $0 ~ $9
// 		}
// 		else if (s[1] == '#')
// 		{
// 			// $#
// 			// 引数の数
// 		}
// 		else if (s[1] == '$')
// 		{
// 			// $$
// 		}
// 		else if (s[1] == '*')
// 		{
// 			// $*
// 			// 0以外のコマンドライン引数
// 		}
// 		else if (s[1] == '@')
// 		{
// 			// $@
// 			// $*と同じ
// 		}
// 		else if (s[1] == '?')
// 		{
// 			// $?
// 			// ステータスを返す
// 		}
// 		else if (s[1] == '-')
// 		{
// 			// $-
// 			// シェルにセットされているオプションを保持している
// 		}
// 		else if (s[1] == '!')
// 		{
// 			// $!
// 			// バックグラウンドで実行された直前のプロセスのプロセス番号を保持しています
// 		}
// 	}
// 	return (NULL);
// }

static int	init_expansion(t_expansion *exp, t_token *tok)
{
	exp->ret = (char *)ft_calloc(1, sizeof(char));
	if (!exp->ret)
		return (1);
	exp->str = tok->str;
	exp->len = tok->len;
	exp->i = 0;
	exp->n = 0;
	exp->in_status = IN_NONE;
	return (0);
}

int	done(t_expansion *exp)
{
	return (exp->i >= exp->len);
}

int	expand_special_param(t_minishell *minish, t_expansion *exp)
{
	(void)minish;
	(void)exp;
	return (0);
}

int	expand_variable(t_minishell *minish, t_expansion *exp)
{
	(void)minish;
	(void)exp;
	return (0);
}

// else if (s[i + 1] == '_' || ft_isalnum(s[i + 1]))
// char	*tmp;
// char	*sparam;
// if (exp->p[0] == '$' && exp->i + 1 < exp->len)
// {
// 	if (exp->p[1] == '_' || ft_isalnum(exp->p[1]))
// 	{
// 		// 変数
// 	}
// 	else
// 	{
// 		// $?
// 		// ステータスを返す
// 	}
// }

// $ ' "

static void	count_str_none(t_expansion *exp)
{
	if (exp->in_status != IN_NONE)
		return ;
	while (exp->i < exp->len)
	{
		if (exp->str[exp->i] == '\'' || exp->str[exp->i] == '\"'
			|| exp->str[exp->i] == '$')
		{
			break ;
		}
		exp->i++;
	}
}

static void	count_str_quote(t_expansion *exp)
{
	if (exp->in_status != IN_QUOTE)
		return ;
	while (exp->i < exp->len)
	{
		if (exp->str[exp->i] == '\'')
		{
			break ;
		}
		exp->i++;
	}
	return ;
}

int	join_str(t_minishell *minish, t_expansion *exp)
{
	char	*word;
	char	*tmp;
	size_t	num;

	num = exp->i - exp->n;
	if (num > 0)
	{
		word = ft_substr(exp->str, exp->n, num);
		if (!word)
		{
			minish->error_kind = ERR_MALLOC;
			return (1);
		}
		tmp = exp->ret;
		exp->ret = ft_strjoin(exp->ret, word);
		if (!exp->ret)
		{
			minish->error_kind = ERR_MALLOC;
			free(word);
			return (1);
		}
		exp->n += num;
		free(tmp);
	}
	return (0);
}

int	join_str_none(t_minishell *minish, t_expansion *exp)
{
	count_str_none(exp);
	return (join_str(minish, exp));
}

int	join_str_quote(t_minishell *minish, t_expansion *exp)
{
	count_str_quote(exp);
	return (join_str(minish, exp));
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

char	*expand_str(t_minishell *minish, t_token *tok)
{
	t_expansion	exp;

	if (init_expansion(&exp, tok))
	{
		minish->error_kind = ERR_MALLOC;
		return (NULL);
	}
	while (!done(&exp))
	{
		update_inside_status(&exp);
		if (expand_special_param(minish, &exp))
			return (NULL);
		if (expand_variable(minish, &exp))
			return (NULL);
		if (join_str_none(minish, &exp))
			return (NULL);
		if (join_str_quote(minish, &exp))
			return (NULL);
	}
	return (exp.ret);
}
