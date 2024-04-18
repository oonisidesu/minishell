/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:23:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/17 23:41:03 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"
#include "libft.h"
#include "message/message.h"
#include "minishell.h"
#include "utils/exit_status.h"
#include "utils/utils.h"
#include "variable/env.h"
#include "variable/env_util.h"
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
		if (get_var(minish, key_list[i]) == NULL)
			ft_printf_fd(STDOUT_FILENO, DECLARE_VAL_NULL, key_list[i]);
		else
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
	char	*tmp;

	key_value = divide_key_val(node->argv[i]);
	if (key_value == NULL)
	{
		key_value = (char **)ft_calloc(2, sizeof(char *));
		if (key_value == NULL)
			return (set_err_kind_status(minish, node, ERR_MALLOC), NULL);
		key_value[0] = ft_substr(node->argv[i], 0, ft_strlen(node->argv[i]));
	}
	if (ft_strchr(key_value[0], '+'))
	{
		tmp = ft_strdup(key_value[0]);
		if (tmp == NULL)
			return (set_err_kind_status_free(minish, node, ERR_MALLOC,
					key_value), NULL);
		free(key_value[0]);
		key_value[0] = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
		free(tmp);
		if (key_value[0] == NULL)
			return (set_err_kind_status_free(minish, node, ERR_MALLOC,
					key_value), NULL);
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
			set_or_update_env_var(minish, key_value);
		else if (is_var_dec_exclude_plus(node->argv[i],
				ft_strlen(node->argv[i])))
			append_val(minish, key_value[0], key_value[1], VAR_ENV);
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
