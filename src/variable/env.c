/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:23:06 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/30 11:23:39 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"
#include "variable/env.h"
#include "variable/var.h"

static int	ft_strchr_int(const char *s, int c)
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

static char	*get_key_from_env(const char *envp)
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

static char	*get_val_from_env(const char *envp)
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

static char	*join_three_word(char *s1, char *s2, char *s3)
{
	char	*s1_s2;
	char	*result;

	s1_s2 = ft_strjoin(s1, s2);
	if (s1_s2 == NULL)
		return (NULL);
	result = ft_strjoin(s1_s2, s3);
	if (result == NULL)
	{
		free(s1_s2);
		return (NULL);
	}
	free(s1_s2);
	return (result);
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
		}
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
			envp[i] = join_three_word(current->key, "=", current->val);
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

// keyの一覧をsortする関数
void	sort_key_list(char **key_list)
{
	size_t	i;
	size_t	com_len;
	bool	sort_flag;

	if (key_list == NULL | key_list[0] == NULL)
		return ;
	i = 0;
	sort_flag = true;
	while (sort_flag)
	{
		i = 0;
		sort_flag = false;
		com_len = 1;
		while (key_list[i + 1] != NULL)
		{
			if (ft_strncmp(key_list[i], key_list[i + 1], com_len) > 0)
			{
				ft_swap(&key_list[i], &key_list[i + 1]);
				sort_flag = true;
			}
			else if (ft_strncmp(key_list[i], key_list[i + 1], com_len) == 0)
			{
				com_len++;
				continue ;
			}
			i++;
		}
	}
}

// keyの一覧を返す関数
char	**get_key_list(t_minishell *minish)
{
	size_t	env_elements;
	t_var	*current;
	char	**key_list;
	size_t	i;

	env_elements = 0;
	current = minish->var;
	while (current)
	{
		env_elements++;
		current = current->next;
	}
	key_list = (char **)malloc((env_elements + 1) * sizeof(char *));
	if (key_list == NULL)
	{
		minish->error_kind = ERR_MALLOC;
		return (NULL);
	}
	current = minish->var;
	i = 0;
	while (current)
	{
		if (current->type == VAR_ENV)
		{
			key_list[i] = ft_strdup(current->key);
			if (key_list[i] == NULL)
			{
				minish->error_kind = ERR_MALLOC;
				free_array((void **)key_list);
				return (NULL);
			}
		}
		else
			key_list[i] = NULL;
		current = current->next;
		i++;
	}
	key_list[env_elements] = NULL;
	return (key_list);
}
