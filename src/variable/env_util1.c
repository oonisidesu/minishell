/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:09:48 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/04/09 15:20:01 by ootsuboyosh      ###   ########.fr       */
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

char	*join_three_word(char *s1, char *s2, char *s3)
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
