/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:44:59 by susumuyagi        #+#    #+#             */
/*   Updated: 2023/09/30 15:22:29 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_nbr(int fd, int n, int sign, ssize_t *len)
{
	char	c;

	if (n / 10 != 0)
		write_nbr(fd, n / 10, sign, len);
	c = (n % 10) * sign + '0';
	*len += write(fd, &c, 1);
}

ssize_t	ft_putnbr(int fd, int n)
{
	ssize_t	len;
	int		sign;

	len = 0;
	sign = 1;
	if (n < 0)
	{
		len += write(fd, "-", 1);
		sign = -1;
	}
	write_nbr(fd, n, sign, &len);
	return (len);
}

static void	write_unbr(int fd, unsigned n, ssize_t *len)
{
	char	c;

	if (n / 10 != 0)
		write_unbr(fd, n / 10, len);
	c = (n % 10) + '0';
	*len += write(fd, &c, 1);
}

ssize_t	ft_putunbr(int fd, unsigned int n)
{
	ssize_t	len;

	len = 0;
	write_unbr(fd, n, &len);
	return (len);
}
