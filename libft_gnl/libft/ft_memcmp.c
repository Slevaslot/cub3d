/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:13:33 by pdosso-d          #+#    #+#             */
/*   Updated: 2022/11/14 17:14:25 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *pointer1, const void *pointer2, size_t size)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)pointer1;
	p2 = (unsigned char *)pointer2;
	if (size == 0)
		return (0);
	i = 0;
	while (p1[i] == p2[i] && i < size - 1)
		i++;
	return (p1[i] - p2[i]);
}

// int main() {

//     int tab1 [] = { 54, 85, 18, 63, 21 };
//     int tab2 [] = { 54, 85, 19, 63, 21 };
//     size_t size = sizeof( int ) * 5;

//     printf("%d\n", ft_memcmp( tab1, tab2, size));
// 	printf("%d", memcmp( tab1, tab2, size));
//     return 0;
// }
