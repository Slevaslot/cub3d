/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:10:06 by pdosso-d          #+#    #+#             */
/*   Updated: 2022/11/14 15:09:19 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*l;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	l = ft_lstlast(*lst);
	l->next = new;
}

// void printlist(t_list *l)
// {
// 	while(l)
// 	{
// 		printf("%s", (char *)l->content);
// 		l = l->next;
// 	}
// }

// int main()
// {
//     t_list *l1;
//     t_list *l2 = ft_lstnew("2");
//     t_list *l3 = ft_lstnew("3");
//     void *p = &l1;
//     ft_lstadd_back(p, l2);
//     ft_lstadd_back(p, l3);
//     printlist(l1);
//     return 0;
// }
