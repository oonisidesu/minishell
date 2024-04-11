/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:21:42 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/04/10 16:26:01 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>

static char	**malloc_ret(char const *s, const char *c)
{
	size_t	count;
	size_t	i;
	char	**ret;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (i == 0 && ft_strchr(c, s[i]) == NULL)
			count++;
		else if (ft_strchr(c, s[i - 1]) != NULL && ft_strchr(c, s[i]) == NULL)
			count++;
		i++;
	}
	ret = (char **)malloc(sizeof(char *) * (count + 1));
	if (!ret)
		return (NULL);
	ret[count] = NULL;
	return (ret);
}

static size_t	word_len(char const *s, const char *c, size_t i)
{
	size_t	count;

	count = 0;
	while (s[i] && ft_strchr(c, s[i]) == NULL)
	{
		count++;
		i++;
	}
	return (count);
}

int	free_ret(char **ret, size_t k)
{
	size_t	i;

	i = 0;
	while (i < k)
	{
		free(ret[i]);
		i++;
	}
	free(ret);
	return (1);
}

static int	split(char const *s, const char *c, char **ret)
{
	size_t	i;
	size_t	k;
	size_t	len;

	i = 0;
	k = 0;
	while (s[i])
	{
		len = 0;
		if ((i == 0 && ft_strchr(c, s[i]) == NULL) || (ft_strchr(c, s[i
						- 1]) != NULL && ft_strchr(c, s[i]) == NULL))
			len = word_len(s, c, i);
		if (len > 0)
		{
			ret[k] = ft_substr(s, i, len);
			if (!ret[k])
				return (free_ret(ret, k));
			k++;
		}
		i++;
	}
	return (0);
}

char	**ft_split2(char const *s, const char *c)
{
	char	**ret;

	if (!s)
		return (NULL);
	ret = malloc_ret(s, c);
	if (!ret)
		return (NULL);
	if (split(s, c, ret))
		return (NULL);
	return (ret);
}
