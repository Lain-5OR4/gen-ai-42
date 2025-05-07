/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rra(t_stack **stack_a)
{
	t_stack	*last;
	t_stack	*prev;

	if (!*stack_a || !(*stack_a)->next)
		return ;
	last = *stack_a;
	prev = NULL;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = *stack_a;
	*stack_a = last;
	write(1, "rra\n", 4);
}

void	rrb(t_stack **stack_b)
{
	t_stack	*last;
	t_stack	*prev;

	if (!*stack_b || !(*stack_b)->next)
		return ;
	last = *stack_b;
	prev = NULL;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = *stack_b;
	*stack_b = last;
	write(1, "rrb\n", 4);
}

void	rrr(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*last;
	t_stack	*prev;

	if (*stack_a && (*stack_a)->next)
	{
		last = *stack_a;
		prev = NULL;
		while (last->next)
		{
			prev = last;
			last = last->next;
		}
		prev->next = NULL;
		last->next = *stack_a;
		*stack_a = last;
	}
	if (*stack_b && (*stack_b)->next)
	{
		last = *stack_b;
		prev = NULL;
		while (last->next)
		{
			prev = last;
			last = last->next;
		}
		prev->next = NULL;
		last->next = *stack_b;
		*stack_b = last;
	}
	write(1, "rrr\n", 4);
}