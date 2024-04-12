/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ootsuboyoshiyuki <ootsuboyoshiyuki@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:32 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/04/11 18:21:09 by ootsuboyosh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_H
# define VAR_H

typedef enum e_var_type
{
	VAR_SHELL,
	VAR_ENV,
}					t_var_type;

typedef struct s_var
{
	t_var_type		type;
	char			*key;
	char			*val;
	struct s_var	*next;
}					t_var;

bool				is_var_declaration(const char *str, size_t n);
bool				is_var_dec_exclude_equal(const char *str, size_t n);
char				**divide_key_val(const char *key_val);

#endif
