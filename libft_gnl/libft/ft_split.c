/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:31:32 by pdosso-d          #+#    #+#             */
/*   Updated: 2022/11/20 19:54:17 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	clearmemory(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static size_t	wordcount(char const *s, char c)
{
	size_t	i;
	size_t	j;

	j = 1;
	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] == '\0')
			break ;
		while (s[i] != c && s[i])
			i++;
		j++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	str = malloc(sizeof(char *) * wordcount(s, c));
	if (!str || !s)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] == '\0')
			break ;
		start = i;
		while (s[i] != c && s[i])
			i++;
		str[j] = ft_substr(s, start, i - start);
		if (!str[j++])
			clearmemory(str);
	}
	str[j] = 0;
	return (str);
}

// #include <stdio.h>

// int	main()
// {
// 	char **ret = ft_split("", 'z');
// 	(void)ret;
// 	printf("---> (%s)", ret[0]);
// }
