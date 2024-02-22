/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:16:18 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/02/22 12:54:16 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "../minishell.h"
# include "readline.h"
# include <signal.h>

# define SYNTAX_ERROR "minishell: syntax error near unexpected token "

void	ctrl_c_handler(int sig);
void	ctrl_c_clean_handler(t_minishell *minish);
void    ctrl_d_clean_handler(t_minishell *minish);
int	    signal_monitor(void);

#endif