/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:43:31 by pdosso-d          #+#    #+#             */
/*   Updated: 2022/11/11 18:09:41 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	j = 0;
	l = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		l = l * 10 + str[i] - '0';
		i++;
	}
	if (j == 1)
		return (-l);
	return (l);
}

// int main(int argc, char *argv[])
// {
// 	if (argc == 2)
// 	{
// 		printf("%d\n", ft_atoi(argv[1]));
// 		printf("%d", atoi(argv[1]));
// 		return(0);
// 	}
// }
