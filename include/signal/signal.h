/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:16:18 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/03/18 16:31:52 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "../minishell.h"
# include "readline.h"
# include <signal.h>

# define CTRL_C 1

void	ctrl_c_handler(int sig);
void	ctrl_c_clean_handler(t_minishell *minish);
void    ctrl_d_clean_handler(t_minishell *minish);

#endif