/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:58:41 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/17 13:26:31 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"
# include <stddef.h>

# define EXP_INIT_SIZE 1024

typedef struct s_expansion
{
	char			**arr_ret;
	size_t			arr_size;
	size_t			arr_capa;

	char			*ret;
	size_t			size;
	size_t			capa;

	const char		*str;
	size_t			len;

	size_t			i;
	size_t			n;

	t_inside_status	in_status;
}					t_expansion;

int					init_expansion(t_expansion *exp, const char *str,
						size_t len);
int					free_expansion_and_return_error(t_expansion *exp);
int					done_expansion(t_expansion *exp);
int					update_inside_status(t_expansion *exp, bool push_quote);

int					push_exp_string(t_expansion *exp, const char *str,
						size_t len);
int					add_exp_array(t_expansion *exp);

int					push_up_to_terminator(t_expansion *exp,
						t_inside_status in_status, char *terminator);
int					join_var(t_expansion *exp, const char *var, size_t var_len);

bool				is_special_param(t_expansion *exp);
int					expand_special_param(t_minishell *minish, t_expansion *exp);
int					expand_variable(t_minishell *minish, t_expansion *exp);

char				*expand(t_minishell *minish, t_token *tok);
char				*expand_redirect(t_minishell *minish, t_token *tok);
char				**expand_argv(t_minishell *minish, t_token *tok);
char				*expand_delimiter(t_minishell *minish, t_token *tok);
char				*expand_heredoc(t_minishell *minish, const char *str);

#endif
