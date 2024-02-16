/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:32 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/02/17 16:19:44 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "cmd.h"
# include "env_val.h"
# include "parser/token.h"

# define TOO_MANY_ARGS "Error: too many arguments\n"

// シグナル用グローバル変数
int				g_signal;

typedef struct s_minishell
{
	// 入力文字列
	char		*line;

	// token構造体
	t_token		*token;

	// cmd構造体
	t_cmd		*cmd;

	// 環境変数構造体
	t_env_val	*env;

	// 返り値
	int			status_code;
}				t_minishell;

void			free_minishell(t_minishell *minish);

#endif
