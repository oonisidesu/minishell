/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:11:25 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/19 17:07:00 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

# define RUN_PARENT -2
# define IS_BUILTIN(node) (lookup_builtin_func(node) != NULL)
# define IS_IN_PIPE(minish) ((minish)->node->next != NULL)

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

#endif
