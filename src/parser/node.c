/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:09:54 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/27 13:13:10 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/node.h"
#include "utils/utils.h"
#include <stdlib.h>

static void	free_redirect(t_node *node)
{
	t_node	*tmp;

	while (node)
	{
		tmp = node->next;
		free_array((void **)node->argv);
		free(node->path);
		free(node);
		node = tmp;
	}
}

static void	free_declare(t_node *node)
{
	t_node	*tmp;

	while (node)
	{
		tmp = node->redirect;
		free_array((void **)node->argv);
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
		free_declare(node->declare);
		free_array((void **)node->argv);
		free(node->path);
		free(node);
		node = tmp;
	}
}
