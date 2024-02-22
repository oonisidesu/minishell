/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:13:54 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/22 11:15:50 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec/exec.h"
#include "libft.h"
#include "minishell.h"
#include "parser/lexer.h"
#include "parser/parser.h"
#include "parser/prompt.h"
#include <readline/readline.h>
#include <stdlib.h>

void	prompt(t_minishell *minish)
{
	minish->line = readline(PROMPT);
	if (minish->line == NULL)
	{
		ft_printf_fd(STDERR_FILENO, READ_ERR);
		return ;
	}
	if (ft_strlen(minish->line) == 0)
	{
		return ;
	}
	add_history(minish->line);
	tokenize(minish);
	parse(minish);
	exec(minish);
	free_minishell(minish);
	// debug //////////////////////////////////////
	// TODO 後で消す
	printf("minish->status_code: %d\n", minish->status_code);
	///////////////////////////////////////////////
}
