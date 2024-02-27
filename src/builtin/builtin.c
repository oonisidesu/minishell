/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:11:18 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/27 17:14:17 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin/builtin.h"
#include "libft.h"

t_builtin_func	lookup_builtin_func(char *name)
{
	if (ft_strcmp("echo", name) == 0)
		return (builtin_echo);
	if (ft_strcmp("cd", name) == 0)
		return (builtin_cd);
	if (ft_strcmp("pwd", name) == 0)
		return (builtin_pwd);
	if (ft_strcmp("export", name) == 0)
		return (builtin_export);
	if (ft_strcmp("unset", name) == 0)
		return (builtin_unset);
	if (ft_strcmp("env", name) == 0)
		return (builtin_env);
	if (ft_strcmp("exit", name) == 0)
		return (builtin_exit);
	return (NULL);
}
