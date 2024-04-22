/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:54:11 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/04/17 23:40:10 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"
#include "variable/env.h"
#include "variable/var.h"

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

void	set_or_update_env_var(t_minishell *minish, char **key_value)
{
	if (has_key(minish, key_value[0]))
		set_type(minish, key_value[0], VAR_ENV);
	else
		add_or_update_var(minish, key_value[0], key_value[1], VAR_ENV);
}
