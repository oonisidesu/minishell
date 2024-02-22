/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:13:54 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/22 12:47:03 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser/lexer.h"
#include "parser/parser.h"
#include "parser/prompt.h"
#include "signal/signal.h"
#include <readline/readline.h>
#include <stdlib.h>

void	prompt(t_minishell *minish)
{
	minish->line = readline(PROMPT);
	if (minish->line == NULL)
		ctrl_d_clean_handler(minish);
	if (g_signal == 1)
		ctrl_c_clean_handler(minish);
	if (minish->line == NULL)
	{
		ft_putstr_fd(READ_ERR, STDERR_FILENO);
		return ;
	}
	add_history(minish->line);
	tokenize(minish);
	parse(minish);
	// 実行
	free_minishell(minish);
}
