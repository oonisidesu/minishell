/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:23:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/02 15:38:24 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
// TODO 後で消す
#include <stdio.h>

void	builtin_pwd(t_minishell *minish, t_node *node)
{
	// TODO 後で実装する
	(void)minish;
	node->wait_status = EXIT_SUCCESS;
	printf("builtin_pwd\n");
	if (node->in_pipe)
	{
		exit(node->wait_status);
	}
}
