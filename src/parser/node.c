/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:09:54 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/01 17:57:50 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/node.h"
#include "utils/utils.h"
#include <stdlib.h>

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
