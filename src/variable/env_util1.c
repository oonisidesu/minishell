/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:09:48 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/04/10 18:12:17 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"
#include "variable/env.h"
#include "variable/var.h"

int	ft_strchr_int(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_key_from_env(const char *envp)
{
	char	*key;
	int		equal_sign_index;

	equal_sign_index = ft_strchr_int(envp, '=');
	if (equal_sign_index == -1)
		return (NULL);
	key = ft_substr(envp, 0, equal_sign_index);
	if (key == NULL)
		return (NULL);
	return (key);
}

char	*get_val_from_env(const char *envp)
{
	char	*val;
	int		equal_sign_index;

	equal_sign_index = ft_strchr_int(envp, '=');
	if (equal_sign_index == -1)
		return (NULL);
	val = ft_strdup(envp + equal_sign_index + 1);
	if (val == NULL)
		return (NULL);
	return (val);
}

int	env_el_counter(t_minishell *minish)
{
	size_t	env_elements;
	t_var	*current;

	env_elements = 0;
	current = minish->var;
	while (current)
	{
		env_elements++;
		current = current->next;
	}
	return (env_elements);
}

char	*get_key_from_minish(t_minishell *minish, t_var *current)
{
	char	*key;

	if (current->type == VAR_ENV)
	{
		key = ft_strdup(current->key);
		if (key == NULL)
		{
			minish->error_kind = ERR_MALLOC;
			return (NULL);
		}
	}
	else
		key = NULL;
	return (key);
}
