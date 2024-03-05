/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:23:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/05 13:52:32 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
// TODO 後で消す
#include <stdio.h>

int	builtin_pwd(t_minishell *minish, t_node *node)
{
	// TODO 後で実装する
	(void)minish;
	node->wait_status = EXIT_SUCCESS;
	printf("builtin_pwd\n");
	if (node->in_pipe)
	{
		exit(node->wait_status);
	}
	return 0;
}
