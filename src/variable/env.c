/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:23:06 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/20 16:43:12 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_envp(t_minishell *minish, char **envp)
{
	// TODO envpをt_var型のリストに変換して格納する
	// minish->envpは後で消す。
	minish->envp = envp;
}

char	**get_envp(t_minishell *minish)
{
	// TODO t_var型のリストをchar**型のenvpに変換して返す
	return (minish->envp);
}
