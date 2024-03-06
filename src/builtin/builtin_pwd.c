/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:23:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/05 14:20:19 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin/builtin.h"
#include <stdlib.h>
// TODO 後で消す
#include <stdio.h>

int	builtin_pwd(t_minishell *minish, t_node *node)
{
	char pathname[PATHNAME_MAX];
	(void)node;

	ft_memset(pathname, 0, PATHNAME_MAX);
	if (!getcwd(pathname, PATHNAME_MAX))
	{
		printf("%s\n", minish->pwd);
		return (node->wait_status);
	}
	printf("%s\n", pathname);
	return (node->wait_status);
}
