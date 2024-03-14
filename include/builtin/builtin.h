/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:11:25 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/14 14:31:48 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

# define RUN_PARENT -2
# define IS_BUILTIN(node) (lookup_builtin_func(node) != NULL)
# define IS_IN_PIPE(minish) ((minish)->node->next != NULL)
# define BUILTIN_ERROR "minishell: %s: %s: %s\n"
# define BUILTIN_ERROR_NOT_ARGS "minishell: %s: %s\n"
# define HOME_NOT_SET "minishell: cd: HOME not set\n"
# define B_TOO_MANY_ARGS "too many arguments"
# define NUM_ARG_REQUIRED "numeric argument required"
# define DECLARE "declare -x %s\n"
# define EXPORT_ERROR "minishell: export: `%s': not a valid identifier\n"

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
