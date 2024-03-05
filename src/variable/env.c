/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:23:06 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/05 16:28:30 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	set_envp(t_minishell *minish, const char **envp)
{
	int		i;
	char	*key;
	char	*val;

	i = 0;
	while (envp[i])
	{
		key = get_key_from_env(envp[i]);
		if (key == NULL)
		{
			minish->error_kind = ERR_MALLOC;
			return ;
		};
		val = get_val_from_env(envp[i]);
		if (val == NULL)
		{
			minish->error_kind = ERR_MALLOC;
			return ;
		}
		add_or_update_var(minish, key, val, VAR_ENV);
		free(key);
		free(val);
		i++;
	}
}

char	*join_key_val(char *key, char *separator, char *val)
{
	char	*key_separator;
	char	*result;

	key_separator = ft_strjoin(key, separator);
	if (key_separator == NULL)
		return (NULL);
	result = ft_strjoin(key_separator, val);
	if (result == NULL)
	{
		free(key_separator);
		return (NULL);
	}
	return (result);
}

char	**get_envp(t_minishell *minish)
{
	size_t	env_elements;
	t_var	*current;
	char	**envp;
	size_t	i;
	size_t	j;

	env_elements = 0;
	current = minish->var;
	while (current)
	{
		env_elements++;
		current = current->next;
	}
	envp = (char **)malloc((env_elements + 1) * sizeof(char *));
	if (envp == NULL)
	{
		minish->error_kind = ERR_MALLOC;
		return (NULL);
	}
	current = minish->var;
	i = 0;
	j = 0;
	while (current)
	{
		if (current->type == VAR_ENV)
		{
			envp[i] = join_key_val(current->key, "=", current->val);
			if (envp[i] == NULL)
			{
				minish->error_kind = ERR_MALLOC;
				while (j < i)
				{
					free(envp[j]);
					j++;
				}
				free(envp);
				return (NULL);
			}
		}
		else
			envp[i] = NULL;
		current = current->next;
		i++;
	}
	envp[env_elements] = NULL;
	return (envp);
}
