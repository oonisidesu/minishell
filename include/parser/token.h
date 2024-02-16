/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:19:35 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/17 16:20:31 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stddef.h>

# define CANNOT_TOKENIZE "Error: Cannot tokenize\n"

typedef enum
{
	TK_RESERVED, // 予約語
	TK_WORD,     // 単語
	TK_EOF,      // 入力の終わりを示すトークン
}	e_token_kind;

typedef struct s_token
{
	e_token_kind kind;    // トークンの種類
	char *str;            // トークン文字列
	size_t len;           // トークンの長さ
	struct s_token *next; // 次のトークン
}	t_token;

#endif
