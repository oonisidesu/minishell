/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:32 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/02/14 17:32:57 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "buildin.h"
# include "cmd.h"
# include "env_val.h"
# include "history.h"

// シグナル用グローバル変数
int				g_signal;

typedef struct s_minishell
{
	// cmd構造体
	t_cmd		*cmd;

	// history構造体
	t_history	*hist;

	// 環境変数構造体
	t_env_val	*env_val;

	// 返り値
	int			status_code;
}				t_minishell;

#endif
