/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:21:42 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/03/29 14:14:10 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>

static bool	is_delimiter(char c, const char *delimiters)
{
	while (*delimiters)
	{
		if (c == *delimiters)
			return (true);
		delimiters++;
	}
	return (false);
}

static char	**malloc_ret(char const *s, const char *c)
{
	size_t	count;
	size_t	i;
	char	**ret;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (i == 0 && !is_delimiter(s[0], c))
			count++;
		else if (is_delimiter(s[i - 1], c) && !is_delimiter(s[i], c))
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
	while (s[i] && !is_delimiter(s[i], c))
	{
		count++;
		i++;
	}
	return (count);
}

static void	free_ret(char **ret, size_t k)
{
	size_t	i;

	i = 0;
	while (i < k)
	{
		free(ret[i]);
		i++;
	}
	free(ret);
}

static int	split(char const *s, const char *c, char **ret)
{
	size_t	i;
	size_t	k;
	size_t	len;
	char	*word;

	i = 0;
	k = 0;
	while (s[i])
	{
		len = 0;
		if ((i == 0 && !is_delimiter(s[i], c)) || (is_delimiter(s[i - 1], c)
				&& !is_delimiter(s[i], c)))
			len = word_len(s, c, i);
		if (len > 0)
		{
			word = ft_substr(s, i, len);
			if (!word)
			{
				free_ret(ret, k);
				return (0);
			}
			ret[k++] = word;
		}
		i++;
	}
	return (1);
}

char	**ft_split2(char const *s, const char *c)
{
	char	**ret;

	if (!s)
		return (NULL);
	ret = malloc_ret(s, c);
	if (!ret)
		return (NULL);
	if (!split(s, c, ret))
		return (NULL);
	return (ret);
}
