/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertb16.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:08:03 by jeazil            #+#    #+#             */
/*   Updated: 2025/08/17 14:13:42 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_putb16low_fd(unsigned long n, int fd)
{
	int		count;
	char	*letters;

	count = 0;
	letters = "abcdef";
	if (n < 16)
	{
		count++;
		if (n < 10)
			tnt_putchar_fd(n + '0', fd);
		else
			tnt_putchar_fd(letters[n - 10], fd);
	}
	else
	{
		count += ft_putb16low_fd(n / 16, fd);
		count += ft_putb16low_fd(n % 16, fd);
	}
	return (count);
}

int	ft_putb16up_fd(unsigned long n, int fd)
{
	int		count;
	char	*letters;

	count = 0;
	letters = "ABCDEF";
	if (n < 16)
	{
		count++;
		if (n < 10)
			tnt_putchar_fd(n + '0', fd);
		else
			tnt_putchar_fd(letters[n - 10], fd);
	}
	else
	{
		count += ft_putb16up_fd(n / 16, fd);
		count += ft_putb16up_fd(n % 16, fd);
	}
	return (count);
}
