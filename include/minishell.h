/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:32 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/02/22 16:34:30 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser/node.h"
# include "parser/token.h"
# include "variable/var.h"
# include <stdbool.h>
# include <stdio.h>
# include <signal.h>

# define TOO_MANY_ARGS "Error: too many arguments\n"

// シグナル用グローバル変数
static	volatile	sig_atomic_t	g_signal;

typedef enum
{
	ERR_NONE,
	ERR_SYNTAX,
	ERR_MALLOC,
}					e_error_kind;

typedef struct s_minishell
{
	// 入力文字列
	char			*line;

	// token構造体
	t_token			*token;
	t_token			*cur_token;

	// node構造体
	t_node			*node;

	// 環境変数構造体
	t_var			*var;
	// TODO 後で消す（envpをt_varに変換して保持予定）
	// pipe作成時にenvpが必要なため、仮で作成
	char			**envp;

	// 返り値
	int				status_code;

	//
	e_error_kind	error_kind;
}					t_minishell;

void				init_minishell(t_minishell *minish);
void				free_minishell(t_minishell *minish);

#endif
