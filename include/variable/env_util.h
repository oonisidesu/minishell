/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:32 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/04/09 13:15:33 by ootsuboyosh      ###   ########.fr       */
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
void	set_err_kind(t_minishell *minish, e_error_kind kind);
void	set_err_kind_free(t_minishell *minish, e_error_kind kind, char **s);
void	swap_if_greater(char **key_list, int i, int cmp_len, bool *sort_flag);

#endif
