/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:32 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/02/19 13:34:59 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "env_val.h"
# include "parser/node.h"
# include "parser/token.h"
# include <stdbool.h>

# define TOO_MANY_ARGS "Error: too many arguments\n"

// シグナル用グローバル変数
int					g_signal;

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
	t_env_val		*env;

	// 返り値
	int				status_code;

	//
	e_error_kind	error_kind;
}					t_minishell;

void				free_minishell(t_minishell *minish);

#endif
