/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:13:54 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/26 21:28:56 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"
#include "history.h"
#include "libft.h"
#include "message/message.h"
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
	else if (ft_strcmp(minish->line, "") == 0)
		ctrl_c_clean_handler(minish);
	if (ft_strlen(minish->line) == 0)
		return (free_minishell(minish));
	add_history(minish->line);
	if (tokenize(minish))
		return (free_minishell(minish));
	if (parse(minish))
		return (free_minishell(minish));
	exec(minish);
	free_minishell(minish);
}
