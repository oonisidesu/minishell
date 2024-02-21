/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:44:59 by susumuyagi        #+#    #+#             */
/*   Updated: 2023/09/30 15:36:11 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_hex(int fd, unsigned int n, ssize_t *len, int is_upper)
{
	char	c;

	if (n / 16 != 0)
		write_hex(fd, n / 16, len, is_upper);
	c = HEX_BASE[n % 16];
	if (is_upper)
		c = ft_toupper(c);
	*len += write(fd, &c, 1);
}

ssize_t	ft_puthex(int fd, unsigned int n, int is_upper)
{
	ssize_t	len;

	len = 0;
	write_hex(fd, n, &len, is_upper);
	return (len);
}

static void	write_addr(int fd, unsigned long n, ssize_t *len)
{
	char	c;

	if (n / 16 != 0)
		write_addr(fd, n / 16, len);
	c = HEX_BASE[n % 16];
	*len += write(fd, &c, 1);
}

ssize_t	ft_putaddr(int fd, void *p)
{
	ssize_t			len;
	unsigned long	n;

	n = (unsigned long)p;
	len = 0;
	len += write(fd, "0x", 2);
	write_addr(fd, n, &len);
	return (len);
}
