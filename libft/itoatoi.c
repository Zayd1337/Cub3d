/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoatoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:11:06 by jeazil            #+#    #+#             */
/*   Updated: 2025/08/17 14:16:11 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static size_t	tnt_intlen(long int n)
{
	size_t	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n / 10 != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

int	ft_unsigned_itoa(unsigned int n)
{
	long int	nb;
	long int	len;
	char		*intochar;

	nb = n;
	len = tnt_intlen(nb);
	intochar = malloc(sizeof(char) * (len + 1));
	if (!intochar)
		return (0);
	intochar[len] = '\0';
	while (len - 1 >= 0)
	{
		intochar[len - 1] = nb % 10 + '0';
		nb = nb / 10;
		len--;
	}
	tnt_putstr_fd(intochar, 1);
	free(intochar);
	return (tnt_intlen(n));
}

int	tnt_itoa(long int n)
{
	long int	nb;
	int			len;
	char		*intochar;

	nb = n;
	len = tnt_intlen(nb);
	intochar = malloc(sizeof(char) * (len + 1));
	if (!intochar)
		return (0);
	if (nb < 0)
	{
		intochar[0] = '-';
		nb = -nb;
	}
	intochar[len] = '\0';
	while ((n >= 0 && len - 1 >= 0) || (n < 0 && len - 1 > 0))
	{
		intochar[len - 1] = nb % 10 + '0';
		nb = nb / 10;
		len--;
	}
	tnt_putstr_fd(intochar, 1);
	free(intochar);
	return (tnt_intlen(n));
}
/*
// int	ft_unsigned_itoa(unsigned int n)
// {
// 	long int	nb;
// 	long int	len;
// 	char		*intochar;

// 	nb = n;
// 	len = tnt_intlen(nb);
// 	intochar = malloc(sizeof(char) * (len + 1));
// 	if (!intochar)
// 		return (0);
// 	intochar[len] = '\0';
// 	while (len - 1 >= 0)
// 	{
// 		intochar[len - 1] = nb % 10 + '0';
// 		nb = nb / 10;
// 		len--;
// 	}
// 	tnt_putstr_fd(intochar, 1);
// 	return (ft_strlen(intochar));
// }

// int	tnt_itoa(int n)
// {
// 	long int	nb;
// 	long int	len;
// 	char		*intochar;

// 	nb = n;
// 	len = tnt_intlen(nb);
// 	intochar = malloc(sizeof(char) * (len + 1));
// 	if (!intochar)
// 		return (0);
// 	if (nb < 0)
// 	{
// 		intochar[0] = '-';
// 		nb = -nb;
// 	}
// 	intochar[len] = '\0';
// 	while (len - 1 >= 0)
// 	{
// 		if (len == 1 && n < 0)
// 			return (1);
// 		intochar[len - 1] = nb % 10 + '0';
// 		nb = nb / 10;
// 		len--;
// 	}
// 	tnt_putstr_fd(intochar, 1);
// 	return (tnt_intlen(n));
// }

size_t	tnt_intlen(long int n)
{
	size_t	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n / 10 != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

int	ft_unsigned_itoa(unsigned int n)
{
	long int	nb;
	long int	len;
	char		*intochar;

	nb = n;
	// if (n < 0)
	// 	nb += 4294967295;
	len = tnt_intlen(nb);
	intochar = malloc(sizeof(char) * (len + 1));
	if (!intochar)
		return (0);
	intochar[len] = '\0';
	while (len - 1 >= 0)
	{
		intochar[len - 1] = nb % 10 + '0';
		nb = nb / 10;
		len--;
	}
	tnt_putstr_fd(intochar, 1);
	free(intochar);
	return (tnt_intlen(n));
}

int	tnt_itoa(int n)
{
	long int	nb;
	long int	len;
	char		*intochar;

	nb = n;
	len = tnt_intlen(nb);
	//intochar = malloc(sizeof(char) * (len + 1));
	if (!(intochar = malloc(sizeof(char) * (len + 1)))) //ok norminette?
		return (0);
	if (nb < 0)
	{
		intochar[0] = '-';
		nb = -nb;
	}
	intochar[len] = '\0';
	while (len - 1 >= 0)
	{
		// if (len == 1 && n < 0)
		// 	return (1);
		intochar[len - 1] = nb % 10 + '0';
		nb = nb / 10;
		len--;
	}
	tnt_putstr_fd(intochar, 1);
	free(intochar);
	return (tnt_intlen(n));//tnt_putstr_fd(intochar, 1); plutots
}

int main(void)
{
	//char	data;
	printf("\n%d", tnt_itoa(12345));
}*/