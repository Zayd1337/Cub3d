/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:50:17 by jeazil            #+#    #+#             */
/*   Updated: 2025/05/23 13:32:04 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

/*size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}*/

int	tnt_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	tnt_putstr_fd(char *s, int fd)
{
	size_t	len;
	size_t	i;

	if (!s)
		return (tnt_putstr_fd("(null)", 1));
	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		tnt_putchar_fd(s[i], fd);
		i++;
	}
	return (len);
}

// int	main(void)
// {
// 	int	hehe = 154641;

// 	int pouet = ft_putb16up_fd(hehe, 1);
// 	printf("\n%d", pouet);
// 	//printf("%p", hehe);
// }