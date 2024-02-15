/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:13:54 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/15 17:56:22 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "paser/prompt.h"
#include <readline/readline.h>
#include <stdlib.h>

void	prompt(t_minishell *minish)
{
	char	*buf;

	(void)minish;
	ft_putstr_fd(PROMPT, STDOUT_FILENO);
	buf = readline(NULL);
	if (buf == NULL)
	{
		ft_putstr_fd(READ_ERR, STDERR_FILENO);
		return ;
	}
	add_history(buf);
	printf("readline: [%s]\n", buf);
	// parse(buf);
	// 実行
	free(buf);
}
