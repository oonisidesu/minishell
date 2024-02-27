/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:13:54 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/27 14:45:05 by susumuyagi       ###   ########.fr       */
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
	minish->line = readline(PROMPT);
	if (minish->line == NULL)
		ctrl_d_clean_handler(minish);
	if (g_signal == CTRL_C_TWO)
		ctrl_c_clean_handler(minish);
	// debug //////////////////////////////////////
	// ft_strlen(minish->line) == 0の時も確認したいのでとりあえず
	// TODO 後で消す
	printf("minish->status_code: %d\n", minish->status_code);
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
