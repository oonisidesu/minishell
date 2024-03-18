/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:32:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/18 17:50:29 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>

char	*ft_join_words(int n, ...)
{
	int		i;
	va_list	ap;
	char	*tmp;
	char	*ret;

	ret = ft_calloc(1, sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	va_start(ap, n);
	while (i < n)
	{
		tmp = ret;
		ret = ft_strjoin(ret, va_arg(ap, char *));
		free(tmp);
		if (!ret)
		{
			va_end(ap);
			return (NULL);
		}
		i++;
	}
	va_end(ap);
	return (ret);
}
