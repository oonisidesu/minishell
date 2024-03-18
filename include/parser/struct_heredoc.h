/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_heredoc.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:44:04 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/18 10:19:15 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_HEREDOC_H
# define STRUCT_HEREDOC_H

# include <stdbool.h>
# include <stddef.h>

// bashも全体で16個までしかヒアドキュメントを扱えない
typedef struct s_heredoc
{
	size_t	num;

	char	*delimiters[16];
	bool	need_expansion[16];
	char	*docs[16];
}			t_heredoc;

#endif
