/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:52:23 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/29 16:25:17 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "message/message.h"
#include "minishell.h"
#include "utils/exit_status.h"
#include <errno.h>
#include <unistd.h>

void	occurred_redirect_error(t_minishell *minish, t_token *tok)
{
	minish->status_code = 1;
	minish->error_kind = ERR_REDIRECT;
	ft_printf_fd(STDERR_FILENO, MINISHELL_NAME);
	write(STDERR_FILENO, tok->str, tok->len);
	ft_printf_fd(STDERR_FILENO, AMBIGUOUS_REDIRECT);
}

void	occurred_syntax_error(t_minishell *minish)
{
	minish->status_code = 258;
	minish->error_kind = ERR_SYNTAX;
	ft_printf_fd(STDERR_FILENO, SYNTAX_ERROR);
	write(STDERR_FILENO, "`", 1);
	write(STDERR_FILENO, minish->cur_token->str, minish->cur_token->len);
	write(STDERR_FILENO, "'\n", 2);
}

void	*occurred_malloc_error_return_null(t_minishell *minish)
{
	minish->status_code = EXIT_FAILURE;
	minish->error_kind = ERR_MALLOC;
	ft_printf_fd(STDERR_FILENO, MINISHELL_ERROR, "malloc", MALLOC_ERROR);
	return (NULL);
}
