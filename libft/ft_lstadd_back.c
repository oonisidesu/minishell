/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:01:02 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/05 12:31:45 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_lst)
{
	t_list	*last;

	if (!lst || !new_lst)
		return ;
	last = ft_lstlast(*lst);
	if (!last)
	{
		*lst = new_lst;
		return ;
	}
	last->next = new_lst;
	return ;
}
