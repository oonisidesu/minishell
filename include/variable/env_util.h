/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:32 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/04/10 15:28:39 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_UTIL_H
# define ENV_UTIL_H

# include "libft.h"
# include <stdlib.h>

int		ft_strchr_int(const char *s, int c);
char	*get_key_from_env(const char *envp);
char	*get_val_from_env(const char *envp);
char	*join_three_word(char *s1, char *s2, char *s3);
int		env_el_counter(t_minishell *minish);
void	set_err_kind(t_minishell *minish, t_error_kind kind);
void	set_err_kind_free(t_minishell *minish, t_error_kind kind, char **s);
bool	swap_if_greater(char **key_list, size_t i, size_t *cmp_len,
			bool *sort_flag);
char	*get_key_from_minish(t_minishell *minish, t_var *current);

#endif
