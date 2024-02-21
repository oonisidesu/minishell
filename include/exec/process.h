/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:19:35 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/21 22:31:17 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "minishell.h"
# include "parser/node.h"

# define COMMAND_NOT_FOUND "command not found"
# define PERMISSION_DENIED "permission denied"
# define NO_SUCH_FILE_OR_DIR "No such file or directory"

void	exec_cmd(t_node *node, char **envp);
t_node	*parent_process(t_node *node, int prev_fds[]);
void	wait_prosesses(t_minishell *minish);
void	set_status_code(t_minishell *minish);

#endif
