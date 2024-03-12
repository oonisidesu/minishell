/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:23:27 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/12 17:01:33 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/find_path.h"
#include "exec/pipe.h"
#include "exec/process.h"
#include "minishell.h"
#include <unistd.h>

static void	save_orig_io(int orig_io[2])
{
	orig_io[0] = dup(0);
	orig_io[1] = dup(1);
}

static void	restore_orig_io(int orig_io[2])
{
	close(0);
	dup2(orig_io[0], 0);
	close(orig_io[0]);
	close(1);
	dup2(orig_io[1], 1);
	close(orig_io[1]);
}

void	exec(t_minishell *minish)
{
	int	orig_io[2];

	if (minish->node == NULL)
		return ;
	set_cmd_path(minish);
	save_orig_io(orig_io);
	exec_pipe(minish);
	wait_prosesses(minish);
	restore_orig_io(orig_io);
	set_status_code(minish);
}
