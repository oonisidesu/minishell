/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:11:25 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/02 15:24:10 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

# define RUN_PARENT -2
# define IS_BUILTIN(node) (lookup_builtin_func((node)->argv[0]) != NULL)
# define IS_IN_PIPE(minish) ((minish)->node->next != NULL)

typedef void	(*t_builtin_func)(t_minishell *minish, t_node *node);

t_builtin_func	lookup_builtin_func(char *name);

void			builtin_echo(t_minishell *minish, t_node *node);
void			builtin_cd(t_minishell *minish, t_node *node);
void			builtin_pwd(t_minishell *minish, t_node *node);
void			builtin_export(t_minishell *minish, t_node *node);
void			builtin_unset(t_minishell *minish, t_node *node);
void			builtin_env(t_minishell *minish, t_node *node);
void			builtin_exit(t_minishell *minish, t_node *node);

#endif
