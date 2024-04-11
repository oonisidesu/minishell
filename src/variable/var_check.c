/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:35:43 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/04/11 17:37:00 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"
#include "variable/env.h"
#include "variable/var.h"

bool	is_var_declaration(const char *str, size_t n)
{
	size_t	i;

	if (n == 0)
		return (false);
	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (false);
	i++;
	while (str[i] && str[i] != '=' && i < n)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	if (i < n && str[i] == '=')
	{
		return (true);
	}
	return (false);
}

bool	has_key(t_minishell *minish, const char *key)
{
	t_var	*current;

	if (key == NULL)
		return (false);
	current = minish->var;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (true);
		current = current->next;
	}
	return (false);
}

bool	is_var_dec_exclude_equal(const char *str, size_t n)
{
	size_t	i;

	if (n == 0)
		return (false);
	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (false);
	i++;
	while (str[i] && i < n)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
