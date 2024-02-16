/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:22:07 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/17 16:23:17 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser/lexer.h"
#include "parser/prompt.h"
#include <stdlib.h>
#include <unistd.h>

void	free_minishell(t_minishell *minish)
{
	free(minish->line);
	free_tokens(minish->token);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minish;

	(void)argv;
	if (argc > 1)
	{
		ft_putstr_fd(TOO_MANY_ARGS, STDERR_FILENO);
		return (1);
	}
	// 環境変数をminishell構造体に設定する
	// TODO
	(void)envp;
	while (1)
	{
		prompt(&minish);
	}
	return (0);
}
