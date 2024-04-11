/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:54:11 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/04/10 18:11:51 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"
#include "variable/env.h"
#include "variable/var.h"

void	set_err_kind(t_minishell *minish, t_error_kind kind)
{
	minish->error_kind = kind;
}

void	set_err_kind_free(t_minishell *minish, t_error_kind kind, char **s)
{
	set_err_kind(minish, kind);
	free_array((void **)s);
}

bool	swap_if_greater(char **key_list, size_t i, size_t *cmp_len,
		bool *sort_flag)
{
	if (ft_strncmp(key_list[i], key_list[i + 1], *cmp_len) > 0)
	{
		ft_swap(&key_list[i], &key_list[i + 1]);
		*sort_flag = true;
	}
	else if (ft_strncmp(key_list[i], key_list[i + 1], *cmp_len) == 0)
	{
		(*cmp_len)++;
		return (false);
	}
	return (true);
}

char	*join_three_word(char *s1, char *s2, char *s3)
{
	char	*s1_s2;
	char	*result;

	s1_s2 = ft_strjoin(s1, s2);
	if (s1_s2 == NULL)
		return (NULL);
	result = ft_strjoin(s1_s2, s3);
	if (result == NULL)
	{
		free(s1_s2);
		return (NULL);
	}
	free(s1_s2);
	return (result);
}

char	*join_key_val(t_var *current)
{
	char	*key_val;

	if (current->val == NULL)
		key_val = ft_strjoin(current->key, "=");
	else
		key_val = join_three_word(current->key, "=", current->val);
	return (key_val);
}
