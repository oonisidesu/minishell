/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:23:06 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/11 18:17:56 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"
#include "variable/env.h"
#include "variable/var.h"

char	*get_var(t_minishell *minish, const char *key)
{
	t_var	*current;

	current = minish->var;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->val);
		current = current->next;
	}
	return (NULL);
}

void	free_var(t_minishell *minish)
{
	t_var	*current;
	t_var	*next;

	current = minish->var;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->val);
		free(current);
		current = next;
	}
	minish->var = NULL;
}

void	set_type(t_minishell *minish, const char *key, t_var_type type)
{
	t_var	*current;

	if (key == NULL)
		return ;
	current = minish->var;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			current->type = type;
			return ;
		}
		current = current->next;
	}
}

char	**divide_key_val(const char *key_val)
{
	char	**ret;
	char	*p;

	ret = (char **)ft_calloc(3, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	p = ft_strchr(key_val, '=');
	if (p == NULL)
	{
		free(ret);
		return (NULL);
	}
	ret[0] = ft_substr(key_val, 0, p - key_val);
	if (!ret[0])
	{
		free_array((void **)ret);
		return (NULL);
	}
	ret[1] = ft_strdup(p + 1);
	if (!ret[1])
	{
		free_array((void **)ret);
		return (NULL);
	}
	return (ret);
}
