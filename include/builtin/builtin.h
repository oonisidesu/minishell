/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:11:25 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/31 16:34:35 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

# define RUN_PARENT -2

typedef int		(*t_builtin_func)(t_minishell *minish, t_node *node);

t_builtin_func	lookup_builtin_func(t_node *node);

int				builtin_echo(t_minishell *minish, t_node *node);
int				builtin_cd(t_minishell *minish, t_node *node);
int				builtin_pwd(t_minishell *minish, t_node *node);
int				builtin_export(t_minishell *minish, t_node *node);
int				builtin_unset(t_minishell *minish, t_node *node);
int				builtin_env(t_minishell *minish, t_node *node);
int				builtin_exit(t_minishell *minish, t_node *node);
int				builtin_var(t_minishell *minish, t_node *node);
bool			is_builtin(t_node *node);
bool			is_in_pipe(t_minishell *minish);

#endif
