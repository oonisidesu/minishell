/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:23:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/07 14:05:07 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin/builtin.h"
#include <stdlib.h>
// TODO 後で消す
#include <stdio.h>

int	builtin_pwd(t_minishell *minish, t_node *node)
{
	char *pathname;
	(void)node;

	if (minish->pwd == NULL)
	{
		pathname = getcwd(NULL, MAXPATHLEN);
		if (pathname == NULL)
		{
			node->wait_status = 1;
			return (node->wait_status);
		}
	}
	printf("%s\n", minish->pwd);
	return (node->wait_status);
}
