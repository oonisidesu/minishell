/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:20:20 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/08 14:55:25 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser/token.h"
#include <stdbool.h>
#include <stdlib.h>

bool	is_reserved(char p)
{
	return (p == '<' || p == '>' || p == '|' || p == ';');
}

bool	is_word_char(char p, t_inside_status in_status)
{
	if (in_status == IN_QUOTE)
	{
		return (true);
	}
	else if (in_status == IN_D_QUOTE)
	{
		return (true);
	}
	return (!ft_isspace(p) && !is_reserved(p));
}

t_inside_status	update_in_status(char p, t_inside_status in_status)
{
	if (p == '\'')
	{
		if (in_status == IN_QUOTE)
			return (IN_NONE);
		else if (in_status == IN_NONE)
			return (IN_QUOTE);
	}
	else if (p == '\"')
	{
		if (in_status == IN_D_QUOTE)
			return (IN_NONE);
		else if (in_status == IN_NONE)
			return (IN_D_QUOTE);
	}
	return (in_status);
}

void	free_tokens(t_token *cur)
{
	t_token	*next;

	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
}
