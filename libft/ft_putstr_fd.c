/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:52:34 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/15 16:23:06 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

ssize_t	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return (0);
	return (write(fd, s, ft_strlen(s)));
}
