/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	index_stack(t_stack **stack)
{
	t_stack	*current;
	t_stack	*tmp;
	int		min;
	int		index;

	index = 0;
	while (index < get_stack_size(*stack))
	{
		min = INT_MAX;
		current = *stack;
		while (current)
		{
			if (current->value < min && current->index == 0)
				min = current->value;
			current = current->next;
		}
		tmp = *stack;
		while (tmp)
		{
			if (tmp->value == min && tmp->index == 0)
			{
				tmp->index = index + 1;
				break ;
			}
			tmp = tmp->next;
		}
		index++;
	}
}

void	sort_three(t_stack **stack)
{
	int	first;
	int	second;
	int	third;

	if (get_stack_size(*stack) <= 1)
		return ;
	if (get_stack_size(*stack) == 2)
	{
		if ((*stack)->value > (*stack)->next->value)
			sa(stack);
		return ;
	}
	first = (*stack)->value;
	second = (*stack)->next->value;
	third = (*stack)->next->next->value;
	if (first > second && second < third && first < third)
		sa(stack);
	else if (first > second && second > third)
	{
		sa(stack);
		rra(stack);
	}
	else if (first > second && second < third && first > third)
		ra(stack);
	else if (first < second && second > third && first < third)
	{
		sa(stack);
		ra(stack);
	}
	else if (first < second && second > third && first > third)
		rra(stack);
}

void	sort_small(t_stack **stack_a, t_stack **stack_b)
{
	int	size;
	int	min_pos;

	size = get_stack_size(*stack_a);
	while (size > 3)
	{
		min_pos = find_min_index(*stack_a);
		if (min_pos <= size / 2)
		{
			while (min_pos-- > 0)
				ra(stack_a);
		}
		else
		{
			while (min_pos++ < size)
				rra(stack_a);
		}
		pb(stack_a, stack_b);
		size--;
	}
	sort_three(stack_a);
	while (*stack_b)
		pa(stack_a, stack_b);
}

void	sort_large(t_stack **stack_a, t_stack **stack_b)
{
	int	size;
	int	i;
	int	j;
	int	max_bits;
	int	num;

	size = get_stack_size(*stack_a);
	max_bits = 0;
	while ((size - 1) >> max_bits)
		max_bits++;
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j++ < size)
		{
			num = (*stack_a)->index;
			if ((num >> i) & 1)
				ra(stack_a);
			else
				pb(stack_a, stack_b);
		}
		while (*stack_b)
			pa(stack_a, stack_b);
		i++;
	}
}

void	sort_stack(t_stack **stack_a, t_stack **stack_b)
{
	int	size;

	size = get_stack_size(*stack_a);
	if (size <= 1)
		return ;
	else if (size <= 3)
		sort_three(stack_a);
	else if (size <= 5)
		sort_small(stack_a, stack_b);
	else
		sort_large(stack_a, stack_b);
}