/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 16:02:56 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/08 16:05:52 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*join;

	join = NULL;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	if ((join = (char *)malloc(sizeof(char) * (ft_strlen(s1)
						+ ft_strlen(s2) + 1))) == NULL)
		return (NULL);
	ft_strcpy(join, s1);
	ft_strcat(join, s2);
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (join);
}

void	ft_free_lst(t_env *e)
{
	t_list	*tmp;

	tmp = NULL;
	while (e->a != NULL)
	{
		tmp = e->a;
		e->a = e->a->next;
		ft_memdel((void **)&(tmp->content));
		ft_memdel((void **)&(tmp));
	}
	while (e->b != NULL)
	{
		tmp = e->b;
		e->b = e->b->next;
		ft_memdel((void **)&(tmp->content));
		ft_memdel((void **)&(tmp));
	}
}