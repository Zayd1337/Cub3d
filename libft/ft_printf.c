/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:09:21 by jeazil            #+#    #+#             */
/*   Updated: 2025/09/04 10:17:27 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// int	tnt_putchar_fd(char c, int fd)
// {
// 	write(fd, &c, 1);
// 	return (1);
// }

// int	tnt_putstr_fd(char *s, int fd)
// {
// 	size_t	len;
// 	size_t	i;

// 	if (!s)
// 		return(tnt_putstr_fd("(null)", 1));
// 	len = ft_strlen(s);
// 	i = 0;
// 	while (i < len)
// 	{
// 		tnt_putchar_fd(s[i], fd);
// 		i++;
// 	}
// 	return (len);
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

// int	ft_unsigned_itoa(unsigned int n)
// {
// 	long int	nb;
// 	long int	len;
// 	char		*intochar;

// 	nb = n;
// 	// if (n < 0)
// 	// 	nb += 4294967295;
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
// 	free(intochar);
// 	return (tnt_intlen(n));
// }

// int	tnt_itoa(long int n)
// {
// 	long int	nb;
// 	int			len;
// 	char		*intochar;

// 	nb = n;
// 	len = tnt_intlen(nb);
// 	//intochar = malloc(sizeof(char) * (len + 1));
// 	if (!(intochar = malloc(sizeof(char) * (len + 1)))) //ok norminette?
// 		return (0);
// 	if (nb < 0)
// 	{
// 		intochar[0] = '-';
// 		nb = -nb;
// 	}
// 	intochar[len] = '\0';
// 	while ((n >= 0 && len - 1 >= 0) || (n < 0 && len - 1 > 0))
// 	{
// 		// if (len == 1 && n < 0)
// 		// 	return (1);
// 		intochar[len - 1] = nb % 10 + '0';
// 		nb = nb / 10;
// 		len--;
// 	}
// 	tnt_putstr_fd(intochar, 1);
// 	free(intochar);
// 	return (tnt_intlen(n));//tnt_putstr_fd(intochar, 1); plutots
// }

// int	ft_putb16low_fd(unsigned long n, int fd)
// {
// 	char	*letters;
// 	int		count;

// 	count = 0;
// 	letters = "abcdef";
// 	if (n < 16)
// 	{
// 		count++;
// 		if (n < 10)
// 			tnt_putchar_fd(n + '0', fd);
// 		else
// 			tnt_putchar_fd(letters[n - 10], fd);
// 	}
// 	else
// 	{
// 		count += ft_putb16low_fd(n / 16, fd);
// 		count += ft_putb16low_fd(n % 16, fd);
// 	}
// 	return (count);
// }

// int	ft_putb16up_fd(unsigned long n, int fd)
// {
// 	char	*letters;
// 	int		count;

// 	count = 0;
// 	letters = "ABCDEF";
// 	if (n < 16)
// 	{
// 		count++;
// 		if (n < 10)
// 			tnt_putchar_fd(n + '0', fd);
// 		else
// 			tnt_putchar_fd(letters[n - 10], fd);
// 	}
// 	else
// 	{
// 		count += ft_putb16up_fd(n / 16, fd);
// 		count += ft_putb16up_fd(n % 16, fd);
// 	}
// 	return (count);
// }
// if (data == -2147483648)
// 		adress = 0xffffffff80000000;

// int	ft_putadress_fd(long int n, int fd)
// {
//     char    *letters;
//     int    count;

//     count = 0;
//     letters = "abcdef";
// 	//if (n < 0)
//     if (n < 16)
//     {
//         count++;
//         if (n < 10)
//             tnt_putchar_fd(n + '0', fd);
//         else
//             tnt_putchar_fd(letters[n - 10], fd);
//     }
//     else
//     {
//         count += ft_putb16low_fd(n / 16, fd);
//         count += ft_putb16low_fd(n % 16, fd);
//     }
//     return (count);
// // }
// int	ft_putpointer_fd(int data, int fd) //unsigned?
// {
// 	int				hexa;

// 	if (!data)
// 	{
// 		tnt_putstr_fd("(nil)", fd);
// 		return (0);
// 	}
// 	if (data == 0)
// 	{
// 		tnt_putchar_fd(0, fd);
// 		return (1);
// 	}
// 	write(1, "0x", 2);
// 	// if (data < 0)
// 	// {
// 	// 	write (1, "ffffffff", 8);
// 	// 	hexa = ft_putb16low_fd((unsigned int)data, fd) + 10;
// 	// }
// 	//else
// 		hexa = ft_putb16low_fd((unsigned long)data, fd) + 2;
// 	return (hexa);
// }

// int	ft_putpointer_fd(long int data, int fd) //unsigned?
// {
// 	int				hexa;

// 	if (!data)
// 	{
// 		tnt_putstr_fd("(nil)", fd);
// 		return (5);//heuuuuu pq??
// 	}
// 	if (data == 0)
// 	{
// 		tnt_putchar_fd(0, fd);
// 		return (1);
// 	}
// 	write(1, "0x", 2);
// 	// if (data < 0)
// 	// {
// 	// 	write (1, "ffffffff", 8);
// 	// 	hexa = ft_putb16low_fd((unsigned int)data, fd) + 10;
// 	// }
// 	//else
// 		hexa = ft_putb16low_fd((unsigned long)data, fd) + 2;
// 	return (hexa);
// }

static int	checkset(char s1)
{
	size_t	i;
	char	*set;

	set = "cspdiuxX%";
	i = 0;
	while (set[i])
	{
		if (set[i] == s1)
			return (1);
		i++;
	}
	return (0);
}

static int	whichtype(char c, va_list args)
{
	int	count;

	count = 0;
	if (checkset(c) == 0)
		return (0);
	else if (c == 'c')
		count += tnt_putchar_fd(va_arg(args, int), 1);
	else if (c == 's')
		count += tnt_putstr_fd(va_arg(args, char *), 1);
	else if (c == 'd' || c == 'i')
		count += tnt_itoa(va_arg(args, int));
	else if (c == 'u')
		count += ft_unsigned_itoa(va_arg(args, unsigned int));
	else if (c == '%')
		count += tnt_putchar_fd('%', 1);
	else if (c == 'p')
		count += ft_putpointer_fd(va_arg(args, long int), 1);
	else if (c == 'x')
		count += ft_putb16low_fd(va_arg(args, unsigned int), 1);
	else if (c == 'X')
		count += ft_putb16up_fd(va_arg(args, unsigned int), 1);
	return (count);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		count;
	va_list	args;
	int		len;

	len = ft_strlen(s);
	va_start(args, s);
	count = 0;
	i = 0;
	while (i < len)
	{
		while (s[i] && s[i] != '%')
		{
			count += tnt_putchar_fd(s[i], 1);
			i++;
		}
		if (s[i] && s[i + 1])
		{
			count += whichtype(s[i + 1], args);
			i++;
		}
		i++;
	}
	va_end(args);
	return (count);
}

// int	main(void)
// {
// 	// char *str = "pouet";
// 	// char c = 'c';
// 	// //int *p = str;
// 	// int n = -42;
// 	// unsigned int i = 42;
// 	//va_list str;
// 	int nb;
// 	//char	*pouet = "hoho";

// 	//nb = ft_printf(NULL);
// 	nb = printf(NULL);
// 	printf("\n%d", nb);
// }