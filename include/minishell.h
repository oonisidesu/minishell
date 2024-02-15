/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:32 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/02/15 16:30:30 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "cmd.h"
# include "env_val.h"
# include "history.h"

# define TOO_MANY_ARGS "Error: too many arguments\n"

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
