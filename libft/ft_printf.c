/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:32:01 by susumuyagi        #+#    #+#             */
/*   Updated: 2023/09/30 16:07:17 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <unistd.h>

static ssize_t	write_format(int fd, va_list *ap, const char *fmt)
{
	ssize_t	len;

	if (*fmt == 'c')
		len = ft_putchar(fd, va_arg(*ap, int));
	else if (*fmt == 's')
		len = ft_putstr(fd, va_arg(*ap, char *));
	else if (*fmt == 'p')
		len = ft_putaddr(fd, va_arg(*ap, void *));
	else if (*fmt == 'd')
		len = ft_putnbr(fd, va_arg(*ap, int));
	else if (*fmt == 'i')
		len = ft_putnbr(fd, va_arg(*ap, int));
	else if (*fmt == 'u')
		len = ft_putunbr(fd, va_arg(*ap, unsigned int));
	else if (*fmt == 'x')
		len = ft_puthex(fd, va_arg(*ap, unsigned int), 0);
	else if (*fmt == 'X')
		len = ft_puthex(fd, va_arg(*ap, unsigned int), 1);
	else if (*fmt == '%')
		len = ft_putchar(fd, '%');
	else
		len = 0;
	return (len);
}

static int	ft_vprintf_fd(int fd, const char *fmt, va_list *ap)
{
	ssize_t	len;

	len = 0;
	while (*fmt)
	{
		if (*fmt == '%')
			len += write_format(fd, ap, ++fmt);
		else
			len += write(fd, fmt, 1);
		fmt++;
	}
	return (len);
}

int	ft_printf_fd(int fd, const char *fmt, ...)
{
	va_list	ap;
	ssize_t	len;

	va_start(ap, fmt);
	len = ft_vprintf_fd(fd, fmt, &ap);
	va_end(ap);
	return (len);
}

int	ft_printf(const char *fmt, ...)
{
	ssize_t	len;
	va_list	ap;

	va_start(ap, fmt);
	len = ft_vprintf_fd(STDOUT_FILENO, fmt, &ap);
	va_end(ap);
	return (len);
}
