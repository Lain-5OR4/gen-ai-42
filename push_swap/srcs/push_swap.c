/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	init_stacks(t_stack **stack_a, int *numbers, int size)
{
	int		i;
	t_stack	*new_node;

	i = 0;
	while (i < size)
	{
		new_node = create_new_node(numbers[i]);
		if (!new_node)
		{
			free_stack(stack_a);
			return (0);
		}
		add_to_stack(stack_a, new_node);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int		*numbers;
	int		size;
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (argc < 2)
		return (0);
	stack_a = NULL;
	stack_b = NULL;
	numbers = parse_args(argc, argv, &size);
	if (!numbers)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (!init_stacks(&stack_a, numbers, size))
	{
		free(numbers);
		return (1);
	}
	free(numbers);
	if (!is_stack_sorted(stack_a))
	{
		index_stack(&stack_a);
		sort_stack(&stack_a, &stack_b);
	}
	free_stack(&stack_a);
	return (0);
}