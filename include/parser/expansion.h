/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:58:41 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/11 11:34:13 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <stddef.h>

typedef enum
{
	IN_NONE,
	IN_QUOTE,
	IN_D_QUOTE,
}					e_inside_status;

typedef struct s_expansion
{
	char			*ret;

	char			*str;
	size_t			len;

	size_t			i;
	size_t			n;

	e_inside_status	in_status;
}					t_expansion;

char				*expand(t_minishell *minish, t_token *tok);

#endif
