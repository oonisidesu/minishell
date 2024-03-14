/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:23:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/15 01:11:35 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"
#include "libft.h"
#include "minishell.h"
#include "utils/utils.h"
#include "variable/env.h"
#include "variable/var.h"
#include <stdlib.h>
#include <unistd.h>
// TODO 後で消す
#include <stdio.h>

static void	print_env(t_minishell *minish)
{
	char	**envp;
	int		i;

	envp = get_envp_double_quote(minish);
	i = 0;
	while (envp[i] != NULL)
	{
		ft_printf_fd(STDOUT_FILENO, DECLARE, envp[i]);
		i++;
	}
	free_array((void **)envp);
}

static void	set_env(t_minishell *minish, t_node *node)
{
	int		i;
	char	**key_value;

	i = 1;
	while (i < node->argc)
	{
		key_value = divide_key_val(node->argv[i]);
		if (key_value == NULL)
		{
			key_value = (char **)ft_calloc(2, sizeof(char *));
			if (key_value == NULL)
			{
				minish->error_kind = ERR_MALLOC;
				return;
			}
			key_value[0] = ft_substr(node->argv[i], 0, ft_strlen(node->argv[i]));
		}
		if (is_var_declaration(node->argv[i], ft_strlen(node->argv[i])))
			add_or_update_var(minish, key_value[0], key_value[1], VAR_ENV);
		else if (is_var_dec_exclude_equal(node->argv[i],
				ft_strlen(node->argv[i])))
		{
			if (has_key(minish, key_value[0]))
				set_type(minish, key_value[0], VAR_ENV);
		}
		else
		{
			ft_printf_fd(STDERR_FILENO, EXPORT_ERROR, node->argv[i]);
			node->wait_status = 1;
		}
		free_array((void **)key_value);
		i++;
	}
}

int	builtin_export(t_minishell *minish, t_node *node)
{
	if (node->argc == 1 || ft_strncmp(node->argv[1], "#", 1) == 0)
	{
		print_env(minish);
		node->wait_status = 0;
		return (node->wait_status);
	}
	else
		set_env(minish, node);
	return (node->wait_status);
}
