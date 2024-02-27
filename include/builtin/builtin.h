/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:11:25 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/27 16:05:54 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

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
