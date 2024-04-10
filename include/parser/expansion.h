/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:58:41 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/10 12:19:33 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"
# include <stddef.h>

typedef struct s_expansion
{
	char			*ret;

	const char		*str;
	size_t			len;

	size_t			i;
	size_t			n;

	t_inside_status	in_status;
}					t_expansion;

int					init_expansion(t_expansion *exp, t_token *tok);
int					expansion_done(t_expansion *exp);
bool				is_special_param(t_expansion *exp);
bool				has_quotes(t_token *tok);
void				update_inside_status(t_expansion *exp);

int					join_up_to_terminator(t_expansion *exp,
						t_inside_status in_status, char *terminator);
int					join_var(t_expansion *exp, const char *var, size_t var_len);

int					expand_variable(t_minishell *minish, t_expansion *exp);
int					consume_and_join_dollar(t_expansion *exp);

int					expand_special_param(t_minishell *minish, t_expansion *exp);

char				*expand(t_minishell *minish, t_token *tok);
char				*expand_redirect(t_minishell *minish, t_token *tok);
char				**expand_argv(t_minishell *minish, t_token *tok);
char				*expand_delimiter(t_minishell *minish, t_token *tok);
char				*expand_heredoc(t_minishell *minish, const char *str);

#endif
