/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:19:35 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/12 17:23:16 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

int		parse(t_minishell *minish);

bool	consume(t_minishell *minish, char *op);
bool	expect_word(t_minishell *minish);
bool	at_eof(t_token *tok);
bool	at_pipe(t_token *tok);

int		redirection(t_minishell *minish, t_node **redirect_cur);
void	declaration(t_minishell *minish, t_node **declare_cur);
t_node	*command(t_minishell *minish);

#endif
