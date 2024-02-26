/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:23:06 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/26 13:39:20 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variable/env.h"
#include "variable/var.h"

t_var	*create_var(e_var_type type, char *key, char *val)
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

void	add_var(t_var **head, t_var *new_var)
{
	t_var	*current;

	new_var->next = NULL;
	if (*head == NULL)
		*head = new_var;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_var;
	}
}

void	set_envp(t_minishell *minish, const char **envp, e_var_type type)
{
	size_t	i;
	char	*equal_sign;
	t_var	*new_var;

	i = 0;
	// envp をループして、各変数をリンクリストに追加する
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			// '='を'\0'に変えて、keyとvalを分ける
			*equal_sign = '\0';
			// keyとvalを使って新しいt_var型の変数を作成
			new_var = create_var(type, envp[i], equal_sign + 1);
			// 新しい変数をリンクリストに追加
			add_var(&(minish->var), new_var);
		}
		i++;
	}
	// minish->envpは後で消す。
	minish->envp = envp;
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
	while (current != NULL)
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
		envp[i] = join_key_val(current->key, "=", current->val);
		if (envp[i] == NULL)
		{
			minish->error_kind = ERR_MALLOC;
			// error_kindにERR_MALLOCを設定しているのでここでfreeしなくてもいい？
			while (j < i)
			{
				free(envp[j]);
				j++;
			}
			free(envp);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	envp[env_elements] = NULL;
	return (envp);
}
