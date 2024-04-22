/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:19:35 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/09 15:16:05 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdbool.h>
# include <sys/types.h>

typedef enum e_inside_status
{
	IN_ANY,
	IN_NONE,
	IN_QUOTE,
	IN_D_QUOTE,
}					t_inside_status;

typedef enum e_token_kind
{
	TK_RESERVED,
	TK_WORD,
	TK_EOF,
}					t_token_kind;

typedef struct s_token
{
	t_token_kind	kind;
	const char		*str;
	size_t			len;
	struct s_token	*next;
}					t_token;

bool				is_reserved(char p);
bool				is_word_char(char p, t_inside_status in_status);
t_inside_status		update_in_status(char p, t_inside_status in_status);
ssize_t				count_token_word_len(char *p);
void				free_tokens(t_token *cur);

#endif
