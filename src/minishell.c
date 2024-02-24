/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:22:07 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/24 19:55:59 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/lexer.h"
#include <stdlib.h>

void	init_minishell(t_minishell *minish)
{
	minish->line = NULL;
	minish->token = NULL;
	minish->cur_token = NULL;
	minish->node = NULL;
	minish->var = NULL;
	minish->envp = NULL;
	minish->status_code = 0;
	minish->error_kind = ERR_NONE;
}

void	free_minishell(t_minishell *minish)
{
	free(minish->line);
	free_tokens(minish->token);
	// TODO free_nodesを作る
	// free_nodes(minish->node);
}
