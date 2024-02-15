/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:13:54 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/15 16:46:22 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "prompt.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

void	prompt(t_minishell *minish)
{
	char	*buf;

	(void)minish;
	ft_putstr_fd(PROMPT, STDOUT_FILENO);
	buf = readline(NULL);
	printf("readline: [%s]\n", buf);
	free(buf);
}
