/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:32 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/02/26 13:39:01 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
#define ENV_H

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

t_var* create_var(e_var_type type, char* key, char* val);
void add_var(t_var** head, t_var* new_var);
void set_envp(t_minishell* minish, const char** envp, e_var_type type);
char* join_key_val(char* key, char* separator, char* val);
char** get_envp(t_minishell* minish);

#endif
