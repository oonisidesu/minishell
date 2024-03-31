/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:53:52 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/31 12:11:23 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ERROR_H
# define MINISHELL_ERROR_H

# include "minishell.h"

void	occurred_redirect_error(t_minishell *minish, t_token *tok);
void	occurred_syntax_error(t_minishell *minish);
void	*occurred_malloc_error_return_null(t_minishell *minish);
void	occurred_resource_error(t_minishell *minish, char *resource);

#endif
