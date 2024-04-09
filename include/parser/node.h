/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:25:22 by ootsuboyosh       #+#    #+#             */
/*   Updated: 2024/04/09 11:40:56 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

# include <stdbool.h>

typedef enum e_node_kind
{
	ND_REDIRECT_OUT,
	ND_REDIRECT_APPEND,
	ND_REDIRECT_IN,
	ND_HEREDOC,
	ND_DECLARE,
	ND_COMMAND,
}					t_node_kind;

typedef struct s_node
{
	t_node_kind		kind;
	int				argc;
	char			**argv;

	int				wait_status;
	int				pid;

	char			*path;
	bool			has_x;
	bool			exist_cmd;
	bool			in_pipe;

	int				heredoc_idx;

	struct s_node	*redirect;
	struct s_node	*declare;
	struct s_node	*next;
}					t_node;

void				free_nodes(t_node *node);

#endif
