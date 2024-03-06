/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:11:25 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/06 19:16:33 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include <unistd.h>
# include <errno.h>
# include <string.h>

# define RUN_PARENT -2
# define IS_BUILTIN(node) (lookup_builtin_func((node)->argv[0]) != NULL)
# define IS_IN_PIPE(minish) ((minish)->node->next != NULL)
# define PATHNAME_MAX 10000
# define LINE_BREAK "\n"
# define COLON ": "
# define MINISHEEL "minishell"
# define CD "cd"
# define EXIT "exit"
# define HOME_NOT_SET "HOME not set"
# define B_TOO_MANY_ARGS "too many arguments"
# define NUM_ARG_REQUIRED "numeric argument required"

typedef int	(*t_builtin_func)(t_minishell *minish, t_node *node);

t_builtin_func	lookup_builtin_func(char *name);

int			builtin_echo(t_minishell *minish, t_node *node);
int			builtin_cd(t_minishell *minish, t_node *node);
int			builtin_pwd(t_minishell *minish, t_node *node);
int			builtin_export(t_minishell *minish, t_node *node);
int			builtin_unset(t_minishell *minish, t_node *node);
int			builtin_env(t_minishell *minish, t_node *node);
int			builtin_exit(t_minishell *minish, t_node *node);

#endif
