/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:32:19 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/04/11 18:22:45 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"
#include "variable/env.h"
#include "variable/var.h"

static t_var	*create_var(t_var_type type, const char *key, const char *val)
{
	t_var	*new_var;

	new_var = (t_var *)malloc(sizeof(t_var));
	if (new_var == NULL)
		return (NULL);
	new_var->type = type;
	new_var->key = ft_strdup(key);
	if (new_var->key == NULL)
		return (free(new_var), NULL);
	if (val == NULL)
		new_var->val = NULL;
	else
	{
		new_var->val = ft_strdup(val);
		if (new_var->val == NULL)
			return (free(new_var->key), free(new_var), NULL);
	}
	new_var->next = NULL;
	return (new_var);
}

static void	add_var(t_minishell *minish, const char *key, const char *val,
		t_var_type type)
{
	t_var	*new_var;
	t_var	*current;

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

void	add_or_update_var(t_minishell *minish, const char *key, const char *val,
		t_var_type type)
{
	t_var	*current;

	current = minish->var;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (val == NULL)
				return ;
			free(current->val);
			current->val = ft_strdup(val);
			if (current->type == VAR_SHELL)
				current->type = type;
			return ;
		}
		current = current->next;
	}
	add_var(minish, key, val, type);
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
