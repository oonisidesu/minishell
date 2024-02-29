/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:32 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/02/29 16:14:59 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
#define ENV_H

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

void set_envp(t_minishell *minish, const char **envp);
char** get_envp(t_minishell* minish);
char *get_var(t_minishell *minish, const char *key);
void add_or_update_var(t_minishell *minish, const char *key, const char *val, e_var_type type);
void del_var(t_minishell *minish, const char *key);
void free_var(t_minishell *minish);

#endif
