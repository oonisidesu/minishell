/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:23:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/10 00:53:18 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"
#include "libft.h"
#include "message/message.h"
#include "minishell.h"
#include "utils/exit_status.h"
#include "utils/utils.h"
#include "variable/env.h"
#include "variable/var.h"
#include <stdlib.h>
#include <unistd.h>

static void	print_env(t_minishell *minish)
{
	char	**key_list;
	int		i;

	key_list = get_key_list(minish);
	sort_key_list(key_list);
	i = 0;
	while (key_list[i] != NULL)
	{
		if (get_type_from_key(minish, key_list[i]) == VAR_EXPORT)
			ft_printf_fd(STDOUT_FILENO, DECLARE_ONLY_KEY, key_list[i]);
		else if (get_type_from_key(minish, key_list[i]) == VAR_ENV)
		{
			ft_printf_fd(STDOUT_FILENO, DECLARE, key_list[i], get_var(minish,
					key_list[i]));
		}
		i++;
	}
	free_array((void **)key_list);
}

static char	**set_key_value(t_minishell *minish, t_node *node, int i)
{
	char	**key_value;

	key_value = divide_key_val(node->argv[i]);
	if (key_value == NULL)
	{
		key_value = (char **)ft_calloc(2, sizeof(char *));
		if (key_value == NULL)
		{
			node->wait_status = EXIT_FAILURE;
			minish->error_kind = ERR_MALLOC;
			return (NULL);
		}
		key_value[0] = ft_substr(node->argv[i], 0, ft_strlen(node->argv[i]));
	}
	return (key_value);
}

static void	print_identifier_err(t_node *node, int i)
{
	ft_printf_fd(STDERR_FILENO, IDENTIFIER_ERROR, "export", node->argv[i]);
	node->wait_status = EXIT_FAILURE;
}

static void	set_env(t_minishell *minish, t_node *node)
{
	int		i;
	char	**key_value;

	i = 1;
	node->wait_status = EXIT_SUCCESS;
	while (i < node->argc)
	{
		key_value = set_key_value(minish, node, i);
		if (key_value == NULL)
			return ;
		if (is_var_declaration(node->argv[i], ft_strlen(node->argv[i])))
			add_or_update_var(minish, key_value[0], key_value[1], VAR_ENV);
		else if (is_var_dec_exclude_equal(node->argv[i],
				ft_strlen(node->argv[i])))
		{
			if (has_key(minish, key_value[0]))
				set_type(minish, key_value[0], VAR_ENV);
			else if (key_value[1] == NULL)
				add_or_update_var(minish, key_value[0], "", VAR_EXPORT);
		}
		else
			print_identifier_err(node, i);
		free_array((void **)key_value);
		i++;
	}
}

int	builtin_export(t_minishell *minish, t_node *node)
{
	if (node->argc == 1)
	{
		print_env(minish);
		node->wait_status = 0;
		return (node->wait_status);
	}
	else
		set_env(minish, node);
	return (node->wait_status);
}
