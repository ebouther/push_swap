/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 21:19:51 by ebouther          #+#    #+#             */
/*   Updated: 2016/02/09 17:54:23 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include <stdio.h>

static void	ft_print_stack(t_list *lst)
{
	char	*ret;

	ret = ft_strnew(0);
	while (lst != NULL)
	{
		ret = ft_strjoin_free(ft_strdup(" "),
				ft_strjoin_free(ft_itoa(*((int *)(lst->content))), ret));
		lst = lst->next;
	}
	ft_putstr(ret);
	ft_strdel(&ret);
}

static void	ft_stacks_state(t_env *e)
{
	int	i;
	static int	color = 0;

	i = 0;
	ft_putchar('\n');
	if (e->flag_c == 1)
	{
		while (i < ft_strlen(e->op) - 2)
			ft_putchar(e->op[i++]);
		ft_putstr("\033[3");
		ft_putnbr((color % 6) + 1);
		ft_putstr("m");
		ft_putstr(e->op + i);
		ft_putstr("\033[0m");
		color++;
	}
	else
		ft_putstr(e->op);
	ft_putstr("\na: ");
	ft_print_stack(e->a);
	ft_putstr("\nb: ");
	ft_print_stack(e->b);
	ft_putchar('\n');
}

static void	ft_fill_stack(int argc, char **argv, t_env *e)
{
	int		tmp;
	int		i;
	int		nb[argc];

	i = 0;
	e->a = NULL;
	e->b = NULL;
	e->len_a = 0;
	e->len_b = 0;
	e->flag_v = 0;
	e->flag_c = 0;
	while (--argc > 0)
	{			
		if (ft_strcmp(argv[argc], "-c") == 0)
			e->flag_c = 1;
		else if (ft_strcmp(argv[argc], "-v") == 0)
			e->flag_v = 1;
		else if (ft_strcmp(argv[argc], "-cv") == 0
			|| ft_strcmp(argv[argc], "-vc") == 0)
		{
			e->flag_v = 1;
			e->flag_c = 1;
		}
		else
		{
			while (argv[argc][i])
			{
				if (ft_isdigit(argv[argc][i]) == 0
						&& argv[argc][i] != '-'
						&& argv[argc][i] != '+')
				{
					ft_putstr("Error\n");
					exit(-1);
				}
				i++;
			}
			tmp = ft_atoi(argv[argc]);
			e->len_a++;
			ft_lstadd(&(e->a), ft_lstnew((void *)(&tmp), sizeof(tmp)));
		}
	}
}

static int	ft_get_min_pos(t_env *e)
{
	int		min;
	int		min_pos;
	t_list	*lst;
	int		i;

	min = 2147483647;
	min_pos = -1;
	i = 0;
	lst = e->a;
	while (lst != NULL)
	{
		if (*((int *)lst->content) <= min)
		{
			min = *((int *)lst->content);
			min_pos = i;
		}
		i++;
		lst = lst->next;
	}
	if (min_pos != -1)
		return (min_pos);
	return (-1);
}

static int	ft_is_sort(t_list *lst, size_t len)
{
	int	tmp;
	int	i;

	i = 0;
	tmp = -2147483648;
	while (lst != NULL)
	{
		if (tmp > *((int *)lst->content))
		{
			if (i == len - 1)
				return (2);
			return (0);
		}
		tmp = *((int *)lst->content);
		i++;
		lst = lst->next;
	}
	return (1);
}

static void	ft_sort_stack(t_env *e)
{
	int		i;
	t_list	*lst;
	int		min_pos;
	int		ret;

	lst = e->a;
	ret = -1;
	while (e->len_a > 0 && (min_pos = ft_get_min_pos(e)) != -1)
	{
		if ((ret = ft_is_sort(e->a, e->len_a)) == 1)
		{
			while (e->len_b > 0)
			{
				if (*(e->op) != '\0')
					e->op = ft_strjoin_free(e->op, ft_strdup(" "));
				e->op = ft_strjoin_free(e->op, ft_strdup("pa"));
				ft_push_a(e);
				if (e->flag_v == 1)
					ft_stacks_state(e);
			}
			return ;
		}
		else if (ret == 2)
		{
			ft_rev_rot_stack('a', e);
				if (*(e->op) != '\0')
					e->op = ft_strjoin_free(e->op, ft_strdup(" "));
				e->op = ft_strjoin_free(e->op, ft_strdup("rra"));
				if (e->flag_v == 1)
					ft_stacks_state(e);
	
				ft_rev_rot_stack('a', e);
				if (*(e->op) != '\0')
					e->op = ft_strjoin_free(e->op, ft_strdup(" "));
				e->op = ft_strjoin_free(e->op, ft_strdup("rra"));
				if (e->flag_v == 1)
					ft_stacks_state(e);

			ft_swap_stack('a', e);
			if (*(e->op) != '\0')
				e->op = ft_strjoin_free(e->op, ft_strdup(" "));
			e->op = ft_strjoin_free(e->op, ft_strdup("sa"));
			if (e->flag_v == 1)
				ft_stacks_state(e);
				
			ft_rot_stack('a', e);
				if (*(e->op) != '\0')
					e->op = ft_strjoin_free(e->op, ft_strdup(" "));
				e->op = ft_strjoin_free(e->op, ft_strdup("ra"));
				if (e->flag_v == 1)
					ft_stacks_state(e);

				ft_rot_stack('a', e);
				if (*(e->op) != '\0')
					e->op = ft_strjoin_free(e->op, ft_strdup(" "));
				e->op = ft_strjoin_free(e->op, ft_strdup("ra"));
				if (e->flag_v == 1)
					ft_stacks_state(e);
			break ;
		}
		i = 0;
		if (min_pos == 1)
		{
			ft_swap_stack('a', e);
			if (*(e->op) != '\0')
				e->op = ft_strjoin_free(e->op, ft_strdup(" "));
			e->op = ft_strjoin_free(e->op, ft_strdup("sa"));
			if (e->flag_v == 1)
				ft_stacks_state(e);
			i++;
		}
		else if (min_pos <= e->len_a / 2)
		{
			while (i < min_pos)
			{
				ft_rot_stack('a', e);
				if (*(e->op) != '\0')
					e->op = ft_strjoin_free(e->op, ft_strdup(" "));
				e->op = ft_strjoin_free(e->op, ft_strdup("ra"));
				if (e->flag_v == 1)
					ft_stacks_state(e);
				i++;
			}
		}
		else
		{
			while (i < (e->len_a - min_pos))
			{
				ft_rev_rot_stack('a', e);
				if (*(e->op) != '\0')
					e->op = ft_strjoin_free(e->op, ft_strdup(" "));
				e->op = ft_strjoin_free(e->op, ft_strdup("rra"));
				if (e->flag_v == 1)
					ft_stacks_state(e);
				i++;
			}
		}
		if (ft_is_sort(e->a, e->len_a) != 1)
		{
			ft_push_b(e);
			if (*(e->op) != '\0')
				e->op = ft_strjoin_free(e->op, ft_strdup(" "));
			e->op = ft_strjoin_free(e->op, ft_strdup("pb"));
			if (e->flag_v == 1)
				ft_stacks_state(e);
		}
	}
	while (e->len_b > 0)
	{
		if (*(e->op) != '\0')
			e->op = ft_strjoin_free(e->op, ft_strdup(" "));
		e->op = ft_strjoin_free(e->op, ft_strdup("pa"));
		ft_push_a(e);
		if (e->flag_v == 1)
			ft_stacks_state(e);
	}
}

int			main(int argc, char **argv)
{
	t_env	env;
	int		i;

	i = 0;
	env.op = ft_strnew(0);
	ft_fill_stack(argc, argv, &env);
	ft_sort_stack(&env);
	if (env.flag_v == 0)
	{
		if (env.flag_c == 1)
		{
			while (i < ft_strlen(env.op) - 2)
				ft_putchar(env.op[i++]);
			ft_putstr("\033[33m");
			ft_putstr(env.op + i);
			ft_putstr("\033[0m");
		}
		else
			ft_putstr(env.op);
		ft_putchar('\n');
	}
	ft_strdel(&(env.op));
	ft_free_lst(&env);
}
