/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:23:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/16 22:20:56 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utils/utils.h"
#include "variable/env.h"
#include "variable/var.h"
#include <stdlib.h>
#include <unistd.h>

int	builtin_env(t_minishell *minish, t_node *node)
{
	char	**envp;
	int		i;

	(void)minish;
	i = 0;
	envp = get_envp(minish);
	if (envp == NULL)
	{
		minish->error_kind = ERR_MALLOC;
		node->wait_status = 1;
		return (node->wait_status);
	}
	while (envp[i] != NULL)
	{
		ft_printf_fd(STDOUT_FILENO, "%s\n", envp[i]);
		i++;
	}
	free_array((void **)envp);
	node->wait_status = 0;
	return (node->wait_status);
}
