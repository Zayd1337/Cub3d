/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:29:40 by jeazil            #+#    #+#             */
/*   Updated: 2025/07/02 14:22:01 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *s, ...);
int		tnt_putchar_fd(char c, int fd);
int		tnt_putstr_fd(char *s, int fd);
int		ft_putb16low_fd(unsigned long n, int fd);
int		ft_putb16up_fd(unsigned long n, int fd);
int		ft_unsigned_itoa(unsigned int n);
int		ft_putpointer_fd(long int data, int fd);
int		tnt_itoa(long int n);

#endif