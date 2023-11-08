/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:28:54 by pdosso-d          #+#    #+#             */
/*   Updated: 2022/11/20 14:24:22 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*itoa_opti(int nb, int a, int i, char *str)
{
	if (nb < 0)
	{
		nb = -nb;
		str[i] = '-';
		i = a - 1;
		while (i >= 1)
		{
			str[i] = nb % 10 + '0';
			nb = nb / 10;
			i--;
		}
	}
	else
	{
		i = a - 1;
		while (i >= 0)
		{
			str[i] = nb % 10 + '0';
			nb = nb / 10;
			i--;
		}
	}
	str[a] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		a;
	int		nb;

	nb = n;
	i = 0;
	a = 1;
	if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	if (nb < 0)
	{
		nb = -nb;
		a++;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		a++;
	}
	nb = n;
	str = malloc(sizeof(char) * (a + 1));
	if (!str)
		return (NULL);
	return (itoa_opti(nb, a, i, str));
}

// int main(void)
// {
//     printf("%s\n", ft_itoa(-2147483648));
// }
