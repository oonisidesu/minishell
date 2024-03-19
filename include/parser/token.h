/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:19:35 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/19 16:57:12 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stddef.h>

typedef enum
{
	IN_NONE,
	IN_QUOTE,
	IN_D_QUOTE,
}	e_inside_status;

typedef enum
{
	TK_RESERVED, // 予約語
	TK_WORD,     // 単語
	TK_EOF,      // 入力の終わりを示すトークン
}	e_token_kind;

typedef struct s_token
{
	e_token_kind kind;    // トークンの種類
	const char *str;      // トークン文字列
	size_t len;           // トークンの長さ
	struct s_token *next; // 次のトークン
}	t_token;

#endif
