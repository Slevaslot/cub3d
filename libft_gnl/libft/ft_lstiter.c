/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:10:10 by pdosso-d          #+#    #+#             */
/*   Updated: 2022/11/14 19:31:27 by pdosso-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void f(void *c)
// {
//     ((char *)c)[0] = '\n';
// }

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst->next)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
	(*f)(lst->content);
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
//     char *a2;
//     char *a1;
//     a1 = malloc(sizeof(char) * 8);
//     ft_strlcpy(a1,"0word1", 8);
//     a2 = malloc(sizeof(char) * 8);
//     ft_strlcpy(a2,"0word2", 8);
//     t_list    *l1 = ft_lstnew(a1);
//     l1->next = ft_lstnew(a2);
//     ft_lstiter(l1, &f);
//     printlist(l1);
// }
