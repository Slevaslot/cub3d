/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:54:17 by pdosso-d          #+#    #+#             */
/*   Updated: 2022/11/18 19:21:52 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// int main() {

//     const char * original = "Blip bloup.";
//     char * copy = ft_strdup(original);
//     char * ptr = copy;
//     while( *ptr != '\0' ) {
//         *ptr = toupper( *ptr );
//         ptr++;
//     }
//     printf("%s\n", copy);
//     free(copy);
// }
