/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:32 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/03/13 16:53:17 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_H
# define VAR_H

typedef enum
{
	VAR_SHELL,
	VAR_ENV,
}					e_var_type;

typedef struct s_var
{
	e_var_type		type;
	char			*key;
	char			*val;
	struct s_var	*next;
}					t_var;

bool				is_var_declaration(const char *str, size_t n);
char				**divide_key_val(const char *key_val);

#endif
