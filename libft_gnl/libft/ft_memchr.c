/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:08:27 by pdosso-d          #+#    #+#             */
/*   Updated: 2022/11/14 17:08:27 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size)
{
	size_t			i;
	unsigned char	*mb;

	i = 0;
	mb = (unsigned char *)memoryBlock;
	while (i < size)
	{
		if (mb[i] == (unsigned char)searchedChar)
		{
			return (&mb[i]);
		}
		i++;
	}
	return (NULL);
}

// int main()
// {

//     char tab[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
//     const unsigned int size = 10;
// 	int num = 60;
//     void *found = ft_memchr(tab, num, size);
//     printf("%d is %s\n", num, (found != NULL ? "found" : "not found"));
// }
