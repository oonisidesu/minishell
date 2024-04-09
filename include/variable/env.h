/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:32 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/04/10 01:01:05 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"
# include "minishell.h"
# include <stdlib.h>

char		*get_var(t_minishell *minish, const char *key);
void		add_or_update_var(t_minishell *minish, const char *key,
				const char *val, e_var_type type);
void		del_var(t_minishell *minish, const char *key);
void		free_var(t_minishell *minish);
bool		has_key(t_minishell *minish, const char *key);
void		set_type(t_minishell *minish, const char *key, e_var_type type);
void		set_envp(t_minishell *minish, const char **envp);
char		**get_envp(t_minishell *minish);
void		sort_key_list(char **key_list);
char		**get_key_list(t_minishell *minish);
e_var_type	get_type_from_key(t_minishell *minish, char *key);

#endif
