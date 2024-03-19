/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:23:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/19 17:18:50 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"
#include "libft.h"
#include "message/message.h"
#include "minishell.h"
#include <stdlib.h>
#include <sys/param.h>

int	builtin_pwd(t_minishell *minish, t_node *node)
{
	char	*pathname;

	(void)node;
	if (minish->pwd == NULL)
	{
		pathname = getcwd(NULL, MAXPATHLEN);
		if (pathname == NULL)
		{
			ft_printf_fd(STDERR_FILENO, "pwd: " GETCWD_ERROR);
			node->wait_status = 1;
			return (node->wait_status);
		}
		minish->pwd = pathname;
	}
	printf("%s\n", minish->pwd);
	return (node->wait_status);
}
