/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:09:54 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/04 13:29:35 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/node.h"
#include <stdlib.h>

static void	free_argv(t_node *node)
{
	int	i;

	i = 0;
	while (i < node->argc)
	{
		free(node->argv[i]);
		i++;
	}
	free(node->argv);
}

static void	free_redirect(t_node *node)
{
	t_node	*tmp;

	while (node)
	{
		tmp = node->redirect;
		free(node->path);
		free(node);
		node = tmp;
	}
}

void	free_nodes(t_node *node)
{
	t_node	*tmp;

	while (node)
	{
		tmp = node->next;
		free_redirect(node->redirect);
		free_argv(node);
		free(node->path);
		free(node);
		node = tmp;
	}
}
