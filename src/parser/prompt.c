/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:13:54 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/18 17:00:37 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_putstr_fd(READ_ERR, STDERR_FILENO);
		return ;
	}
	add_history(minish->line);
	tokenize(minish);
	parse(minish);
	// 実行
	free_minishell(minish);
}
