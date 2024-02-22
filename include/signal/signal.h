/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:16:18 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/02/22 16:32:48 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "../minishell.h"
# include "readline.h"
# include <signal.h>

# define CTRL_C_ONE 1
# define CTRL_C_TWO 2

void	ctrl_c_handler(int sig);
void	ctrl_c_clean_handler(t_minishell *minish);
void    ctrl_d_clean_handler(t_minishell *minish);
int	    signal_monitor(void);

#endif