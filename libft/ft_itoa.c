/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:56:36 by jeazil            #+#    #+#             */
/*   Updated: 2025/05/20 15:41:12 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*ft_itoa(int n)
{
	long int	nb;
	long int	len;
	char		*intochar;

	nb = n;
	len = tnt_intlen(nb);
	intochar = malloc(sizeof(char) * (len + 1));
	if (!intochar)
		return (NULL);
	if (nb < 0)
	{
		intochar[0] = '-';
		nb = -nb;
	}
	intochar[len] = '\0';
	while (len - 1 >= 0)
	{
		if (len == 1 && n < 0)
			return (intochar);
		intochar[len - 1] = nb % 10 + '0';
		nb = nb / 10;
		len--;
	}
	return (intochar);
}

/*int	main(void)
{
	printf("%s\n", ft_itoa(-0));
	// printf("%d\n", atoi("-"));
}*/