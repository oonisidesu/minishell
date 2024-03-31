/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:45:27 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/31 16:31:53 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser/expansion.h"
#include "utils/minishell_error.h"
#include "variable/env.h"
#include <parser/token.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool	is_special_param(t_expansion *exp)
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

static int	done(t_expansion *exp)
{
	return (exp->i >= exp->len);
}

static char	*extract_key(t_minishell *minish, t_expansion *exp)
{
	size_t	len;
	char	*key;

	if (exp->str[exp->i] != '$')
	{
		return (NULL);
	}
	if (!(exp->str[exp->i + 1] == '_' || ft_isalpha(exp->str[exp->i + 1])))
	{
		return (NULL);
	}
	exp->i += 2;
	while (!done(exp) && (ft_isalnum(exp->str[exp->i])
			|| exp->str[exp->i] == '_'))
	{
		exp->i++;
	}
	len = exp->i - (exp->n + 1);
	key = ft_substr(exp->str, exp->n + 1, len);
	if (!key)
	{
		return (occurred_malloc_error_return_null(minish));
	}
	exp->n = exp->i;
	return (key);
}

static int	join_var(t_expansion *exp, const char *var, size_t var_len)
{
	char	*tmp;

	if (var != NULL && ft_strlen(var) > 0)
	{
		tmp = exp->ret;
		exp->ret = ft_strjoin(exp->ret, var);
		if (!exp->ret)
		{
			return (1);
		}
		free(tmp);
	}
	exp->i += var_len;
	exp->n += var_len;
	return (0);
}

static int	join_str(t_expansion *exp)
{
	char	*word;
	char	*tmp;
	size_t	num;

	num = exp->i - exp->n;
	if (num == 0)
	{
		return (0);
	}
	word = ft_substr(exp->str, exp->n, num);
	if (!word)
	{
		return (1);
	}
	tmp = exp->ret;
	exp->ret = ft_strjoin(exp->ret, word);
	if (!exp->ret)
	{
		free(word);
		return (1);
	}
	free(word);
	free(tmp);
	exp->n += num;
	return (0);
}

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

static int	expand_special_param(t_minishell *minish, t_expansion *exp)
{
	int		ret;
	char	*str;

	if (exp->str[exp->i] != '$')
	{
		return (0);
	}
	if (exp->str[exp->i + 1] == '0')
	{
		// $0
		return (join_var(exp, minish->argv[0], 2));
	}
	else if (ft_isdigit(exp->str[exp->i + 1]))
	{
		// $1 ~ $9
		return (join_var(exp, "", 2));
	}
	else if (exp->str[exp->i + 1] == '#')
	{
		// $#
		// 引数の数 minishellは引数を受け付けないため、0固定
		return (join_var(exp, "0", 2));
	}
	else if (exp->str[exp->i + 1] == '$')
	{
		// $$ : getpid()が使えないため、$出力
		return (join_var(exp, "$", 1));
	}
	else if (exp->str[exp->i + 1] == '*')
	{
		// $* : 0以外のコマンドライン引数
		return (join_var(exp, "", 2));
	}
	else if (exp->str[exp->i + 1] == '@')
	{
		// $@ : $*と同じ
		return (join_var(exp, "", 2));
	}
	else if (exp->str[exp->i + 1] == '?')
	{
		// $? : ステータスを返す
		str = ft_itoa(minish->status_code);
		ret = join_var(exp, str, 2);
		free(str);
		return (ret);
	}
	else if (exp->str[exp->i + 1] == '-')
	{
		// $- : // シェルにセットされているオプションを保持している
		return (join_var(exp, "", 2));
	}
	else if (exp->str[exp->i + 1] == '!')
	{
		// $! : バックグラウンドで実行された直前のプロセスのプロセス番号を保持しています
		return (join_var(exp, "0", 2));
	}
	return (0);
}

static int	consume_and_join_dollar(t_expansion *exp)
{
	if (exp->str[exp->i] == '$')
	{
		return (join_var(exp, "$", 1));
	}
	return (0);
}

static int	expand_variable(t_minishell *minish, t_expansion *exp)
{
	int		ret;
	char	*key;

	if (!(exp->in_status == IN_NONE || exp->in_status == IN_D_QUOTE))
	{
		return (0);
	}
	if (is_special_param(exp))
	{
		return (0);
	}
	key = extract_key(minish, exp);
	if (!no_error(minish))
	{
		return (1);
	}
	if (!key)
	{
		return (consume_and_join_dollar(exp));
	}
	ret = join_var(exp, get_var(minish, key), 0);
	free(key);
	return (ret);
}

static void	count_str_none(t_expansion *exp)
{
	if (exp->in_status != IN_NONE)
		return ;
	while (!done(exp))
	{
		if (exp->str[exp->i] == '\'' || exp->str[exp->i] == '\"'
			|| exp->str[exp->i] == '$')
		{
			break ;
		}
		exp->i++;
	}
}

static void	count_str_until_dollar(t_expansion *exp)
{
	while (!done(exp))
	{
		if (exp->str[exp->i] == '$')
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
	while (!done(exp))
	{
		if (exp->str[exp->i] == '\'')
		{
			break ;
		}
		exp->i++;
	}
	return ;
}

static void	count_str_d_quote(t_expansion *exp)
{
	if (exp->in_status != IN_D_QUOTE)
		return ;
	while (!done(exp))
	{
		if (exp->str[exp->i] == '\"' || exp->str[exp->i] == '$')
		{
			break ;
		}
		exp->i++;
	}
	return ;
}

static int	join_str_none(t_expansion *exp)
{
	count_str_none(exp);
	return (join_str(exp));
}

static int	join_str_until_dollar(t_expansion *exp)
{
	count_str_until_dollar(exp);
	return (join_str(exp));
}

static int	join_str_quote(t_expansion *exp)
{
	count_str_quote(exp);
	return (join_str(exp));
}

static int	join_str_d_quote(t_expansion *exp)
{
	count_str_d_quote(exp);
	return (join_str(exp));
}

static void	update_inside_status(t_expansion *exp)
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

char	*expand(t_minishell *minish, t_token *tok)
{
	t_expansion	exp;

	if (init_expansion(&exp, tok))
	{
		return (NULL);
	}
	while (!done(&exp))
	{
		update_inside_status(&exp);
		if (expand_special_param(minish, &exp))
			return (NULL);
		if (expand_variable(minish, &exp))
			return (NULL);
		if (join_str_none(&exp))
			return (NULL);
		if (join_str_quote(&exp))
			return (NULL);
		if (join_str_d_quote(&exp))
			return (NULL);
	}
	return (exp.ret);
}

static bool	has_quotes(t_token *tok)
{
	bool	has_s_quote;
	bool	has_d_quote;

	has_s_quote = ft_memchr(tok->str, '\'', tok->len) != NULL;
	has_d_quote = ft_memchr(tok->str, '\"', tok->len) != NULL;
	return (has_s_quote || has_d_quote);
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
	while (!done(&exp))
	{
		update_inside_status(&exp);
		if (join_str_none(&exp))
			return (occurred_malloc_error_return_null(minish));
		if (consume_and_join_dollar(&exp))
			return (occurred_malloc_error_return_null(minish));
		if (join_str_quote(&exp))
			return (occurred_malloc_error_return_null(minish));
		if (join_str_d_quote(&exp))
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
	while (!done(&exp))
	{
		if (expand_special_param(minish, &exp))
			return (occurred_malloc_error_return_null(minish));
		if (expand_variable(minish, &exp))
			return (occurred_malloc_error_return_null(minish));
		if (join_str_until_dollar(&exp))
			return (occurred_malloc_error_return_null(minish));
	}
	return (exp.ret);
}
