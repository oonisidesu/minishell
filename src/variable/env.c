/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:23:06 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/10 18:09:41 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"
#include "variable/env.h"
#include "variable/env_util.h"
#include "variable/var.h"

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

	env_elements = env_el_counter(minish);
	envp = (char **)ft_calloc(env_elements + 1, sizeof(char *));
	if (envp == NULL)
		return (set_err_kind(minish, ERR_MALLOC), NULL);
	current = minish->var;
	i = 0;
	while (current)
	{
		if (current->type == VAR_ENV)
		{
			envp[i] = join_key_val(current);
			if (envp[i] == NULL)
				return (set_err_kind_free(minish, ERR_MALLOC, envp), NULL);
		}
		else
			envp[i] = NULL;
		current = current->next;
		i++;
	}
	return (envp);
}

void	sort_key_list(char **key_list)
{
	size_t	i;
	size_t	cmp_len;
	bool	sort_flag;

	if (key_list == NULL || key_list[0] == NULL)
		return ;
	i = 0;
	sort_flag = true;
	while (sort_flag)
	{
		i = 0;
		sort_flag = false;
		cmp_len = 1;
		while (key_list[i + 1] != NULL)
		{
			if (!swap_if_greater(key_list, i, &cmp_len, &sort_flag))
				continue ;
			i++;
		}
	}
}

char	**get_key_list(t_minishell *minish)
{
	size_t	env_elements;
	t_var	*current;
	char	**key_list;
	size_t	i;

	env_elements = env_el_counter(minish);
	key_list = (char **)ft_calloc(env_elements + 1, sizeof(char *));
	if (key_list == NULL)
		return (set_err_kind(minish, ERR_MALLOC), NULL);
	current = minish->var;
	i = 0;
	while (current)
	{
		key_list[i] = get_key_from_minish(minish, current);
		if (minish->error_kind == ERR_MALLOC)
			return (free_array((void **)key_list), NULL);
		current = current->next;
		i++;
	}
	return (key_list);
}
