/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:26:12 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/19 13:51:26 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utils/minishell_error.h"
#include "utils/utils.h"
#include "variable/env.h"
#include <stdlib.h>

static int	find_path(t_node *node, char **path_array)
{
	size_t	i;

	if (!path_array)
		return (0);
	if (ft_strlen(node->argv[0]) == 0)
		return (0);
	i = 0;
	while (path_array[i])
	{
		node->path = ft_join_words(3, path_array[i], "/", node->argv[0]);
		if (!node->path)
			return (1);
		node->has_x = (access(node->path, X_OK) == 0);
		node->exist_cmd |= (access(node->path, F_OK) == 0);
		if (node->has_x)
			return (0);
		free(node->path);
		node->path = NULL;
		i++;
	}
	return (0);
}

static int	set_path(t_minishell *minish, char **path_array, t_node *cur)
{
	if (cur->kind == ND_COMMAND && cur->argc > 0)
	{
		if (ft_strchr(cur->argv[0], '/'))
		{
			cur->path = ft_strdup(cur->argv[0]);
			if (!cur->path)
			{
				occurred_malloc_error_return_null(minish);
				return (1);
			}
			cur->has_x = (access(cur->path, X_OK) == 0);
			cur->exist_cmd |= (access(cur->path, F_OK) == 0);
		}
		else
		{
			if (find_path(cur, path_array))
			{
				occurred_malloc_error_return_null(minish);
				return (1);
			}
		}
	}
	return (0);
}

int	set_cmd_path(t_minishell *minish)
{
	t_node	*cur;
	char	**path_array;
	char	*var_path;

	var_path = get_var(minish, "PATH");
	if (var_path == NULL)
		return (0);
	path_array = ft_split(var_path, ':');
	if (!path_array)
	{
		occurred_malloc_error_return_null(minish);
		return (1);
	}
	cur = minish->node;
	while (cur)
	{
		if (set_path(minish, path_array, cur))
			break ;
		cur = cur->next;
	}
	free_array((void **)path_array);
	return (!no_error(minish));
}
