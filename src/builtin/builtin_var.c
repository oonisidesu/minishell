/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:17:12 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/13 15:04:19 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_var(t_minishell *minish, t_node *node)
{
	printf("builtin_var\n");
	(void)minish;
	node->wait_status = 0;
	return (node->wait_status);
}
