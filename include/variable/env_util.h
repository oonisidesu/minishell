/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:32 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/04/17 23:49:58 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_UTIL_H
# define ENV_UTIL_H

# include "libft.h"
# include <stdlib.h>

int		ft_strchr_int(const char *s, int c);
char	*get_key_from_env(const char *envp);
char	*get_val_from_env(const char *envp);
int		env_el_counter(t_minishell *minish, bool val_null_flag);
char	*get_key_from_minish(t_minishell *minish, t_var *current);
void	set_err_kind(t_minishell *minish, t_error_kind kind);
void	set_err_kind_free(t_minishell *minish, t_error_kind kind, char **s);
void	set_err_kind_status(t_minishell *minish, t_node *node,
			t_error_kind kind);
void	set_err_kind_status_free(t_minishell *minish, t_node *node,
			t_error_kind kind, char **s);
char	*check_malloc_and_set_err_kind(char *s, t_minishell *minish,
			t_error_kind kind);
bool	swap_if_greater(char **key_list, size_t i, size_t *cmp_len,
			bool *sort_flag);
char	*join_three_word(char *s1, char *s2, char *s3);
char	*join_key_val(t_var *current);
void	set_or_update_env_var(t_minishell *minish, char **key_value);
#endif
