/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:09:54 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/09 12:56:14 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser/node.h"
#include "utils/utils.h"
#include <stdlib.h>

t_node	*malloc_and_init_node(t_node_kind kind)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
	{
		return (NULL);
	}
	// TODO 固定長になっているので、後で可変にする
	node->argv = (char **)ft_calloc(100, sizeof(char *));
	if (node->argv == NULL)
	{
		free(node);
		return (NULL);
	}
	node->kind = kind;
	node->argc = 0;
	node->wait_status = -1;
	node->pid = -1;
	node->path = NULL;
	node->has_x = false;
	node->exist_cmd = false;
	node->redirect = NULL;
	node->declare = NULL;
	node->next = NULL;
	return (node);
}

void	free_nodes(t_node *node)
{
	t_node	*tmp;

	while (node)
	{
		tmp = node->next;
		free_nodes(node->redirect);
		free_nodes(node->declare);
		free_array((void **)node->argv);
		free(node->path);
		free(node);
		node = tmp;
	}
}
