/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:09:33 by jeazil            #+#    #+#             */
/*   Updated: 2025/05/24 14:57:43 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
/*
int	ft_putpointer_fd(int data, int fd)
{
    int hexa;

	if (!data)
	{
		tnt_putstr_fd("(nil)", fd);
		return (0);
	}
	if (data == 0)
	{
		tnt_putchar_fd(0, fd);
		return (1);
	}
	write(1, "0x", 2);
	// if (data  < 0)
	// {
	// 	write (1, "ffffffff", 8);
	// 	hexa = ft_putb16low_fd((unsigned long)data, fd) + 10;
	// }
	// else
		hexa = ft_putb16low_fd((unsigned long)data, fd) + 2;
	return (hexa);
}

int	ft_putpointer_fd(int data, int fd)
{
	unsigned long   adress;
    int hexa;

    adress = (unsigned long)data;
	if (!adress)
	{
		tnt_putstr_fd("(nil)", fd);
		return (0);
	}
	if (adress == 0)
	{
		tnt_putchar_fd(0, fd);
		return (1);
	}
	write(1, "0x", 2);
	hexa = ft_putb16low_fd(adress, fd) + 2;
	return (hexa);
}

int	ft_putpointer_fd(int data, int fd) //unsigned?
{
	long int	adress;
	int				hexa;

	if (!data)
	{
		tnt_putstr_fd("(nil)", fd);
		return (0);
	}
	adress = (unsigned long)data;
	if (adress == 0)
	{
		tnt_putchar_fd(0, fd);
		return (1);
	}
	write(1, "0x", 2);
	if (adress == -2147483648)
	{
		write (1, "ffffffff", 8);
		hexa = ft_putb16low_fd(adress, fd) + 10;
	}
	else
		hexa = ft_putb16low_fd(adress, fd) + 2;
	return (hexa);
}*/

int	ft_putpointer_fd(long int data, int fd)
{
	int	hexa;

	if (!data)
	{
		tnt_putstr_fd("(nil)", fd);
		return (5);
	}
	if (data == 0)
	{
		tnt_putchar_fd('0', fd);
		return (1);
	}
	write(1, "0x", 2);
	hexa = ft_putb16low_fd((unsigned long)data, fd) + 2;
	return (hexa);
}
