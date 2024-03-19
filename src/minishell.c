/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:22:07 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/19 17:22:04 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "message/message.h"
#include "minishell.h"
#include "parser/heredoc.h"
#include "parser/lexer.h"
#include "variable/env.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>

void	init_minishell(t_minishell *minish)
{
	minish->line = NULL;
	minish->token = NULL;
	minish->cur_token = NULL;
	minish->node = NULL;
	minish->var = NULL;
	minish->status_code = 0;
	minish->pwd = getcwd(NULL, MAXPATHLEN);
	if (minish->pwd == NULL)
		ft_printf_fd(STDERR_FILENO, "shell-init: " GETCWD_ERROR);
	minish->error_kind = ERR_NONE;
	init_heredoc(&(minish->heredoc));
}

void	free_minishell(t_minishell *minish)
{
	free(minish->line);
	minish->line = NULL;
	free_tokens(minish->token);
	minish->token = NULL;
	free_nodes(minish->node);
	minish->node = NULL;
	free_heredoc(&minish->heredoc);
	init_heredoc(&minish->heredoc);
}

void	die_minishell(t_minishell *minish)
{
	free_minishell(minish);
	free_var(minish);
}
