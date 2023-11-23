/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:29:00 by pdosso-d          #+#    #+#             */
/*   Updated: 2022/11/14 19:36:03 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
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
//     void *p = &l1;
//     ft_lstadd_front(p, l2);
//     printlist(l1);
//     return 0;
// }
