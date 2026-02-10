/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:16:31 by jeazil            #+#    #+#             */
/*   Updated: 2025/05/19 11:53:51 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nb)
{
	int	len;
	int	sign;
	int	rtnb;

	rtnb = 0;
	sign = 1;
	len = 0;
	while ((nb[len] >= 9 && nb[len] <= 13) || nb[len] == 32)
		len++;
	if (nb[len] == '-' || nb[len] == '+')
	{
		if (nb[len] == '-')
			sign = -1;
		len++;
	}
	while (nb[len] >= 48 && nb[len] <= 57)
	{
		rtnb = rtnb * 10 + (nb[len] - '0');
		len++;
	}
	return (rtnb * sign);
}

/*
int	main(void)
{
	//printf("%d\n", ft_atoi("-"));
	printf("%d\n", atoi("-"));
}*/