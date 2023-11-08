/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:29:07 by pdosso-d          #+#    #+#             */
/*   Updated: 2022/11/17 18:34:54 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	(*del)(lst->content);
	free(lst);
}

// int	main()
// {
// 	t_list *l2 = ft_lstnew("DOSSO");
// 	printf("%s\n", (char *)l2->content);
// 	ft_lstdelone(l2, delete);
// 	printf("---> %s", (char *)l2->content);
// }
