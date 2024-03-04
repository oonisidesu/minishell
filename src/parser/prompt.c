/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:13:54 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/04 13:52:41 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"
#include "history.h"
#include "libft.h"
#include "minishell.h"
#include "parser/lexer.h"
#include "parser/parser.h"
#include "parser/prompt.h"
#include "readline.h"
#include "signal/signal.h"
#include <stdlib.h>

void	prompt(t_minishell *minish)
{
	if (isatty(0))
		minish->line = readline(PROMPT);
	else
		minish->line = get_next_line(0);
	if (minish->line == NULL)
		ctrl_d_clean_handler(minish);
	if (g_signal == CTRL_C_TWO)
		ctrl_c_clean_handler(minish);
	// debug //////////////////////////////////////
	// TODO 後で消す
	// printf("minish->status_code: %d\n", minish->status_code);
	///////////////////////////////////////////////
	if (ft_strlen(minish->line) == 0)
	{
		return ;
	}
	add_history(minish->line);
	tokenize(minish);
	parse(minish);
	exec(minish);
	free_minishell(minish);
}
