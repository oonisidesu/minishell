/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:11:18 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/31 16:23:04 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"
#include "libft.h"

t_builtin_func	lookup_builtin_func(t_node *node)
{
	const char	*name;

	if (node->argc == 0)
	{
		if (node->declare != NULL)
			return (builtin_var);
		return (NULL);
	}
	name = node->argv[0];
	if (ft_strcmp("echo", name) == 0)
		return (builtin_echo);
	if (ft_strcmp("cd", name) == 0)
		return (builtin_cd);
	if (ft_strcmp("pwd", name) == 0)
		return (builtin_pwd);
	if (ft_strcmp("export", name) == 0)
		return (builtin_export);
	if (ft_strcmp("unset", name) == 0)
		return (builtin_unset);
	if (ft_strcmp("env", name) == 0)
		return (builtin_env);
	if (ft_strcmp("exit", name) == 0)
		return (builtin_exit);
	return (NULL);
}

bool	is_builtin(t_node *node)
{
	return (lookup_builtin_func(node) != NULL);
}

bool	is_in_pipe(t_minishell *minish)
{
	return (minish->node->next != NULL);
}
