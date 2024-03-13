/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:26:12 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/13 00:00:40 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "variable/env.h"
#include "utils/utils.h"
#include <stdio.h>
#include <stdlib.h>

static char	**split_path(char *var_path)
{
	char	**ret;

	ret = ft_split(var_path, ':');
	if (!ret)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
		// TODO エラー処理
	}
	return (ret);
}

static char	*join_path(char *path, char *cmd)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin("/", cmd);
	if (!tmp)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
		// TODO エラー処理
	}
	ret = ft_strjoin(path, tmp);
	if (!ret)
	{
		perror("malloc");
		free(tmp);
		exit(EXIT_FAILURE);
		// エラー処理
	}
	free(tmp);
	return (ret);
}

static void	find_path(t_node *node, char **path_array)
{
	size_t	i;

	if (!path_array)
		return ;
	i = 0;
	while (path_array[i])
	{
		node->path = join_path(path_array[i], node->argv[0]);
		node->has_x = (access(node->path, X_OK) == 0);
		node->exist_cmd |= (access(node->path, F_OK) == 0);
		if (node->has_x)
			return ;
		free(node->path);
		node->path = NULL;
		i++;
	}
}

// void	set_cmd_path(char *cmd_str, char *envp[], t_cmd *cmd)
// {
// 	if (ft_strchr(cmd_str, '/'))
// 	{
// 		cmd->path = ft_strdup(cmd_str);
// 		cmd->has_x = (access(cmd->path, X_OK) == 0);
// 		cmd->exist_cmd |= (access(cmd->path, F_OK) == 0);
// 		return ;
// 	}
// 	else
// 		find_path(cmd_str, envp, cmd);
// }

void	set_cmd_path(t_minishell *minish)
{
	t_node	*cur;
	char	**path_array;
	char	*var_path;

	var_path = get_var(minish, "PATH");
	path_array = split_path(var_path);
	// TODO エラー処理
	cur = minish->node;
	while (cur)
	{
		if (cur->kind == ND_COMMAND && cur->argc > 0)
		{
			if (ft_strchr(cur->argv[0], '/'))
			{
				cur->path = ft_strdup(cur->argv[0]);
				// TODO エラー処理
				cur->has_x = (access(cur->path, X_OK) == 0);
				cur->exist_cmd |= (access(cur->path, F_OK) == 0);
			}
			else
			{
				find_path(cur, path_array);
			}
		}
		cur = cur->next;
	}
	free_array((void **)path_array);
}
