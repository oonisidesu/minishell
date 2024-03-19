/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:32 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/03/19 16:58:38 by ootsuboyosh      ###   ########.fr       */
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

// シグナル用グローバル変数
static volatile sig_atomic_t	g_signal;

typedef enum
{
	ERR_NONE,
	ERR_SYNTAX,
	ERR_MALLOC,
}								e_error_kind;

typedef struct s_minishell
{
	// 入力文字列
	char						*line;

	// token構造体
	t_token						*token;
	t_token						*cur_token;

	// node構造体
	t_node						*node;

	// 環境変数構造体
	t_var						*var;

	// 返り値
	int							status_code;

	char						*pwd;

	// 起動時の引数
	int							argc;
	const char					**argv;

	// heredoc
	t_heredoc					heredoc;

	e_error_kind				error_kind;
}								t_minishell;

void							init_minishell(t_minishell *minish);
void							free_minishell(t_minishell *minish);
void							die_minishell(t_minishell *minish);

#endif
