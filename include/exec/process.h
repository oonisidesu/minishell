/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:19:35 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/02 17:00:38 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "minishell.h"
# include "parser/node.h"

void	exec_cmd(t_minishell *minish, t_node *node);
t_node	*parent_process(t_node *node, int prev_fds[]);
void	wait_prosesses(t_minishell *minish);
void	set_status_code(t_minishell *minish);

#endif
