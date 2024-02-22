/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:23:27 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/21 22:29:09 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/find_path.h"
#include "exec/pipe.h"
#include "exec/process.h"
#include "minishell.h"

void	exec(t_minishell *minish)
{
	set_cmd_path(minish);
	exec_pipe(minish);
	wait_prosesses(minish);
	set_status_code(minish);
}
