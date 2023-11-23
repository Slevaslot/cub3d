/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:25:56 by pdosso-d          #+#    #+#             */
/*   Updated: 2022/11/14 17:31:00 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *pointer, int value, size_t count)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)pointer;
	i = 0;
	while (i < count)
	{
		str[i] = value;
		i++;
	}
	return (pointer);
}

// int	main(void)
// {
// 	char	str[] = "Bpnknk";

// 	printf("%s\n", str);
// 	ft_memset(str, '0', 4);
// 	printf("%s", str);
// }
