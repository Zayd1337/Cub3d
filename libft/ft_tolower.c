/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:18:39 by jeazil            #+#    #+#             */
/*   Updated: 2025/05/07 15:17:49 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if ((c >= 65 && c <= 90))
		return (c + 32);
	else
		return (c);
}
/*
int	main(void)
{
	printf("%d\n", tolower('C'));
	printf("%d\n", tolower('c'));
	printf("%d\n", tolower('!'));
}*/