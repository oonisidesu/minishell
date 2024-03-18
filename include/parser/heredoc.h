/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:44:04 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/18 12:44:07 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "minishell.h"
# include "parser/struct_heredoc.h"
# include "parser/token.h"

void	init_heredoc(t_heredoc *heredoc);
void	free_heredoc(t_heredoc *heredoc);
int		set_heredoc(t_minishell *minish, t_token *tok);

// void	read_heredoc(t_minishell *minish, int idx);
void	input_heredoc(t_minishell *minish);

// void	write_heredoc(t_minishell *minish, int idx);
void	write_heredoc(t_minishell *minish, int idx);
// void	heredoc_test(void);

#endif
