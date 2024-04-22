/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:15:09 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/04 15:12:13 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	if (size > 0 && SIZE_MAX / size < count)
		return (NULL);
	ret = malloc(size * count);
	if (!ret)
		return (NULL);
	return (ft_memset(ret, '\0', size * count));
}
