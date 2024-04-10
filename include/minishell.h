/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:32 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/04/10 16:35:46 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser/node.h"
# include "parser/struct_heredoc.h"
# include "parser/token.h"
# include "variable/var.h"
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>

extern volatile sig_atomic_t	g_signal;

typedef enum e_error_kind
{
	ERR_NONE,
	ERR_SYNTAX,
	ERR_MALLOC,
	ERR_REDIRECT,
	ERR_RESOURCE,
	INTERRUPT,
}								t_error_kind;

typedef struct s_minishell
{
	char						*line;

	t_token						*token;
	t_token						*cur_token;

	t_node						*node;

	t_var						*var;

	int							status_code;

	char						*pwd;

	int							argc;
	const char					**argv;

	t_heredoc					heredoc;

	t_error_kind				error_kind;
}								t_minishell;

void							init_minishell(t_minishell *minish);
void							free_minishell(t_minishell *minish);
void							die_minishell_and_exit(t_minishell *minish,
									int exit_code);
bool							no_error(t_minishell *minish);

#endif
