/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	find_min_index(t_stack *stack)
{
	int		min;
	int		min_pos;
	int		i;
	t_stack	*current;

	if (!stack)
		return (-1);
	min = INT_MAX;
	min_pos = -1;
	i = 0;
	current = stack;
	while (current)
	{
		if (current->value < min)
		{
			min = current->value;
			min_pos = i;
		}
		i++;
		current = current->next;
	}
	return (min_pos);
}

int	find_max_index(t_stack *stack)
{
	int		max;
	int		max_pos;
	int		i;
	t_stack	*current;

	if (!stack)
		return (-1);
	max = INT_MIN;
	max_pos = -1;
	i = 0;
	current = stack;
	while (current)
	{
		if (current->value > max)
		{
			max = current->value;
			max_pos = i;
		}
		i++;
		current = current->next;
	}
	return (max_pos);
}

int	get_position(t_stack *stack, int index)
{
	int		pos;
	t_stack	*current;

	pos = 0;
	current = stack;
	while (current)
	{
		if (current->index == index)
			return (pos);
		pos++;
		current = current->next;
	}
	return (-1);
}