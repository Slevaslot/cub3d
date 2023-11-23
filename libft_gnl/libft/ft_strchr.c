/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:47:16 by pdosso-d          #+#    #+#             */
/*   Updated: 2022/11/16 13:58:41 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *stradd, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)stradd;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (&str[i]);
		i++;
	}
	if ((char)c == 0)
		return (&str[i]);
	return (NULL);
}

// int main()
// {
//     char str[] = "Koiol";
//     char c = 0;

//     printf("---> %s\n", ft_strchr(str, c));
//     printf("%s", strchr(str, c));
//     return(0);
// }
