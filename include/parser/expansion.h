/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:58:41 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/09 16:37:18 by susumuyagi       ###   ########.fr       */
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
int					done(t_expansion *exp);
bool				is_special_param(t_expansion *exp);

int					join_up_to_terminator(t_expansion *exp,
						t_inside_status in_status, char *terminator);

char				*expand(t_minishell *minish, t_token *tok);
char				*expand_redirect(t_minishell *minish, t_token *tok);
char				**expand_argv(t_minishell *minish, t_token *tok);
char				*expand_delimiter(t_minishell *minish, t_token *tok);
char				*expand_heredoc(t_minishell *minish, const char *str);

#endif
