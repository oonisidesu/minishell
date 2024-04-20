/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:23:27 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/20 13:22:35 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/find_path.h"
#include "exec/pipe.h"
#include "exec/process.h"
#include "minishell.h"
#include <termios.h>
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
	int				orig_io[2];
	struct termios	term;

	if (minish->node == NULL)
		return ;
	if (set_cmd_path(minish))
		return ;
	save_orig_io(orig_io);
	tcgetattr(STDIN_FILENO, &term);
	exec_pipe(minish);
	wait_prosesses(minish);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	restore_orig_io(orig_io);
	set_status_code(minish);
}
