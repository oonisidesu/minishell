/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susumuyagi <susumuyagi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:49:00 by susumuyagi        #+#    #+#             */
/*   Updated: 2024/02/27 15:50:16 by susumuyagi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <unistd.h>

# define HEX_BASE "0123456789abcdef"

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_ispunct(int c);
int		ft_isspace(int c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
ssize_t	ft_putchar(int fd, char c);
ssize_t	ft_putstr(int fd, char *str);
ssize_t	ft_puthex(int fd, unsigned int n, int is_upper);
ssize_t	ft_putaddr(int fd, void *p);
ssize_t	ft_putnbr(int fd, int n);
ssize_t	ft_putunbr(int fd, unsigned int n);
int		ft_printf_fd(int fd, const char *fmt, ...);
int		ft_printf(const char *fmt, ...);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_toupper(int c);
int		ft_strcmp(const char *s1, const char *s2);

#endif
