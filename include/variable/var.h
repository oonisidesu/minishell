/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:32 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/03/13 13:15:03 by susumuyagi       ###   ########.fr       */
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

#endif
