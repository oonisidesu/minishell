/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_heredoc.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:44:04 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/19 17:20:55 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_HEREDOC_H
# define STRUCT_HEREDOC_H

# include <stdbool.h>
# include <stddef.h>

# define MAX_HEREDOC 16
typedef struct s_heredoc
{
	size_t	num;

	char	*delimiters[MAX_HEREDOC];
	bool	need_expansion[MAX_HEREDOC];
	char	*docs[MAX_HEREDOC];
}			t_heredoc;

#endif
