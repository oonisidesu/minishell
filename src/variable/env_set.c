/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:14:50 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/04/17 23:49:21 by ootsuboyosh      ###   ########.fr       */
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

void	set_err_kind_status(t_minishell *minish, t_node *node,
		t_error_kind kind)
{
	minish->error_kind = kind;
	node->wait_status = EXIT_FAILURE;
}

void	set_err_kind_status_free(t_minishell *minish, t_node *node,
		t_error_kind kind, char **s)
{
	set_err_kind_status(minish, node, kind);
	free_array((void **)s);
}

char	*check_malloc_and_set_err_kind(char *s, t_minishell *minish,
		t_error_kind kind)
{
	if (s == NULL)
		set_err_kind(minish, kind);
	return (s);
}
