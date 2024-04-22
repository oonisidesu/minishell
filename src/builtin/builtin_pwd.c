/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootsubo <yootsubo@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:23:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/21 17:57:52 by yootsubo         ###   ########.fr       */
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
			ft_printf_fd(STDERR_FILENO,
				"pwd: " ERROR_DIRECTORY ERROR_GETCWD PERMIT_DENY_BREAK_LINE);
			node->wait_status = 1;
			return (node->wait_status);
		}
		minish->pwd = pathname;
	}
	ft_printf_fd(STDOUT_FILENO, "%s\n", minish->pwd);
	return (node->wait_status);
}
