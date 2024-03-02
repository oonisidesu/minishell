/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:25:22 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/03/02 14:29:12 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

# include <stdbool.h>

# define BUILTIN_PID -2
// # define IS_BUILTIN(node) ((node)->pid == BUILTIN_PID)
# define IS_BUILTIN(node) (lookup_builtin_func((node)->argv[0]) != NULL)

typedef enum
{
	ND_REDIRECT_OUT,    // >
	ND_REDIRECT_APPEND, // >>
	ND_REDIRECT_IN,     // <
	ND_HEREDOC,         // <<
	// ND_PIPE,            // |
	ND_COMMAND, // command
}					e_node_kind;

typedef struct s_node
{
	e_node_kind		kind;
	int				argc;
	char			**argv;

	int				wait_status;
	int				pid;

	char			*path;
	bool			has_x;
	bool			exist_cmd;
	bool			in_pipe;

	struct s_node	*redirect;
	struct s_node	*next;
}					t_node;

#endif
