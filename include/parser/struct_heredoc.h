/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_heredoc.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:44:04 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/18 12:47:18 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_HEREDOC_H
# define STRUCT_HEREDOC_H

# include <stdbool.h>
# include <stddef.h>

// bashも全体で16個までしかヒアドキュメントを扱えない
# define MAX_HEREDOC 16
# define ERROR_MAX_HEREDOC "minishell: maximum here-document count exceeded"
# define HEREDOC_PROMPT "> "
typedef struct s_heredoc
{
	size_t	num;

	char	*delimiters[MAX_HEREDOC];
	bool	need_expansion[MAX_HEREDOC];
	char	*docs[MAX_HEREDOC];
}			t_heredoc;

#endif
