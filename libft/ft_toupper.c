/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:25:32 by jeazil            #+#    #+#             */
/*   Updated: 2025/05/19 12:00:25 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if ((c >= 97 && c <= 122))
		return (c - 32);
	else
		return (c);
}
/*
int	main(void)
{
	printf("%d\n", ft_toupper('C'));
	printf("%d\n", ft_toupper('c'));
	printf("%d\n", ft_toupper('!'));
}*/