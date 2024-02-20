/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:25:22 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/02/19 12:51:03 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

typedef enum
{
	ND_REDIRECT_OUT,    // >
	ND_REDIRECT_APPEND, // >>
	ND_REDIRECT_IN,     // <
	ND_HEREDOC,         // <<
	ND_PIPE,            // |
	ND_COMMAND,         // command
}					e_node_kind;

typedef struct s_node
{
	e_node_kind		kind;
	int				argc;
	char			**argv;
	int				status;
	int				pid;
	char			*path;
	struct s_node	*redirect;
	struct s_node	*next;
}					t_node;

#endif
