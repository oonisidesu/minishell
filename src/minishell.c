/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:22:07 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/06 19:13:06 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/lexer.h"
#include "variable/env.h"
#include <stdlib.h>

void	init_minishell(t_minishell *minish)
{
	minish->line = NULL;
	minish->token = NULL;
	minish->cur_token = NULL;
	minish->node = NULL;
	minish->var = NULL;
	minish->status_code = 0;
	minish->pwd = NULL;
	minish->error_kind = ERR_NONE;
}

void	free_minishell(t_minishell *minish)
{
	free(minish->line);
	minish->line = NULL;
	free_tokens(minish->token);
	minish->token = NULL;
	free_nodes(minish->node);
	minish->node = NULL;
}

void	die_minishell(t_minishell *minish)
{
	free_minishell(minish);
	free_var(minish);
}
