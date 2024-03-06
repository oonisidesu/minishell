/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:23:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/05 17:11:42 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin/builtin.h"
#include "variable/env.h"
#include "variable/var.h"
#include <stdlib.h>
// TODO 後で消す
#include <stdio.h>

int check_node_argv(t_minishell *minish, t_node *node)
{
	// cdのみ
	if (node->argv[1] == NULL)
	{
		node->argv[1] = get_var(minish, "HOME");
		if (node->argv[1] == NULL)
		{
			ft_printf_fd(2, MINISHEEL_FRONT HOME_NOT_SET "\n");
			node->wait_status = 1;
			return (node->wait_status);
		}
	}
	return (0);
}

int	builtin_cd(t_minishell *minish, t_node *node)
{
	char pathname[PATHNAME_MAX];

	(void)minish;
	node->wait_status = 0;
	ft_memset(pathname, 0, PATHNAME_MAX);
	if (check_node_argv(minish, node) != 0)
		return (node->wait_status);
	if (chdir(node->argv[1]) < 0 || !getcwd(pathname, PATHNAME_MAX)) 
	{
		ft_printf_fd(2, MINISHEEL_FRONT "cd: %s: %s\n", node->argv[1], strerror(errno));
		node->wait_status = 1;
		return (node->wait_status) ;
	}
	if (minish->pwd != NULL)
		free(minish->pwd);
	minish->pwd = (char *)malloc((ft_strlen(pathname) + 1) * sizeof(char));
	if (minish->pwd == NULL)
	{
		minish->error_kind = ERR_MALLOC;
		// malocエラーの時、同じようにreturnしていい？
		return (node->wait_status);
	}
	ft_strlcpy(minish->pwd, pathname, ft_strlen(pathname) + 1);
	return (node->wait_status);	
}
