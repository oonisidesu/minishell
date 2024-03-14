/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:23:06 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/13 17:30:13 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"
#include "variable/env.h"
#include "variable/var.h"

t_var	*create_var(e_var_type type, const char *key, const char *val)
{
	t_var	*new_var;

	new_var = (t_var *)malloc(sizeof(t_var));
	if (new_var == NULL)
		return (NULL);
	new_var->type = type;
	new_var->key = ft_strdup(key);
	if (new_var->key == NULL)
		return (free(new_var), NULL);
	new_var->val = ft_strdup(val);
	if (new_var->val == NULL)
		return (free(new_var->key), free(new_var), NULL);
	new_var->next = NULL;
	return (new_var);
}

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

void	add_or_update_var(t_minishell *minish, const char *key, const char *val,
		e_var_type type)
{
	t_var	*new_var;
	t_var	*current;

	// update
	current = minish->var;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->val);
			current->val = ft_strdup(val);
			if (current->type == VAR_SHELL)
				current->type = type;
			return ;
		}
		current = current->next;
	}
	// add
	new_var = create_var(type, key, val);
	if (minish->var == NULL)
		minish->var = new_var;
	else
	{
		current = minish->var;
		while (current->next)
			current = current->next;
		current->next = new_var;
	}
}

void	del_var(t_minishell *minish, const char *key)
{
	t_var	*current;
	t_var	*prev;

	current = minish->var;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				minish->var = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->val);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
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
