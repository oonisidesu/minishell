/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:58:41 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/29 12:01:49 by susumuyagi       ###   ########.fr       */
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

	e_inside_status	in_status;
}					t_expansion;

char				*expand(t_minishell *minish, t_token *tok);
char				*expand_redirect(t_minishell *minish, t_token *tok);
char				**expand_argv(t_minishell *minish, t_token *tok);
char				*expand_delimiter(t_minishell *minish, t_token *tok);
char				*expand_heredoc(t_minishell *minish, const char *str);

#endif
