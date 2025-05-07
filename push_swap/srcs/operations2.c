/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ra(t_stack **stack_a)
{
	t_stack	*tmp;
	t_stack	*last;

	if (!*stack_a || !(*stack_a)->next)
		return ;
	tmp = *stack_a;
	*stack_a = (*stack_a)->next;
	last = *stack_a;
	while (last->next)
		last = last->next;
	last->next = tmp;
	tmp->next = NULL;
	write(1, "ra\n", 3);
}

void	rb(t_stack **stack_b)
{
	t_stack	*tmp;
	t_stack	*last;

	if (!*stack_b || !(*stack_b)->next)
		return ;
	tmp = *stack_b;
	*stack_b = (*stack_b)->next;
	last = *stack_b;
	while (last->next)
		last = last->next;
	last->next = tmp;
	tmp->next = NULL;
	write(1, "rb\n", 3);
}

void	rr(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp;
	t_stack	*last;

	if (*stack_a && (*stack_a)->next)
	{
		tmp = *stack_a;
		*stack_a = (*stack_a)->next;
		last = *stack_a;
		while (last->next)
			last = last->next;
		last->next = tmp;
		tmp->next = NULL;
	}
	if (*stack_b && (*stack_b)->next)
	{
		tmp = *stack_b;
		*stack_b = (*stack_b)->next;
		last = *stack_b;
		while (last->next)
			last = last->next;
		last->next = tmp;
		tmp->next = NULL;
	}
	write(1, "rr\n", 3);
}