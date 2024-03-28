/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:52:23 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/28 17:04:42 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "message/message.h"
#include "minishell.h"
#include <unistd.h>

void	occurred_redirect_error(t_minishell *minish, t_token *tok)
{
	minish->status_code = 1;
	minish->error_kind = ERR_REDIRECT;
	ft_printf_fd(STDERR_FILENO, MINISHELL_NAME);
	write(STDERR_FILENO, tok->str, tok->len);
	ft_printf_fd(STDERR_FILENO, AMBIGUOUS_REDIRECT);
}
