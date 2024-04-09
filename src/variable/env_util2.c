/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:54:11 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/04/09 13:14:49 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"
#include "variable/env.h"
#include "variable/var.h"

void	set_err_kind(t_minishell *minish, e_error_kind kind)
{
	minish->error_kind = kind;
}

void	set_err_kind_free(t_minishell *minish, e_error_kind kind, char **s)
{
	set_err_kind(minish, kind);
	free_array((void **)s);
}

void	swap_if_greater(char **key_list, int i, int cmp_len, bool *sort_flag)
{
	if (ft_strncmp(key_list[i], key_list[i + 1], cmp_len) > 0)
	{
		ft_swap(&key_list[i], &key_list[i + 1]);
		*sort_flag = true;
	}
}
