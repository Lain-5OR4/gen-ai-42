/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

/* main */
int		main(int argc, char **argv);

/* パース関数 */
int		is_number(char *str);
int		is_duplicate(int num, int *numbers, int size);
int		*parse_args(int argc, char **argv, int *size);
int		ft_atoi(const char *str);

/* スタック操作 */
t_stack	*create_new_node(int value);
void	add_to_stack(t_stack **stack, t_stack *new_node);
void	free_stack(t_stack **stack);
int		get_stack_size(t_stack *stack);
int		is_stack_sorted(t_stack *stack);

/* ソートアルゴリズム */
void	sort_stack(t_stack **stack_a, t_stack **stack_b);
void	sort_three(t_stack **stack);
void	sort_small(t_stack **stack_a, t_stack **stack_b);
void	sort_large(t_stack **stack_a, t_stack **stack_b);
void	index_stack(t_stack **stack);

/* push_swap操作 */
void	sa(t_stack **stack_a);
void	sb(t_stack **stack_b);
void	ss(t_stack **stack_a, t_stack **stack_b);
void	pa(t_stack **stack_a, t_stack **stack_b);
void	pb(t_stack **stack_a, t_stack **stack_b);
void	ra(t_stack **stack_a);
void	rb(t_stack **stack_b);
void	rr(t_stack **stack_a, t_stack **stack_b);
void	rra(t_stack **stack_a);
void	rrb(t_stack **stack_b);
void	rrr(t_stack **stack_a, t_stack **stack_b);

/* ユーティリティ関数 */
int		find_min_index(t_stack *stack);
int		find_max_index(t_stack *stack);
int		get_position(t_stack *stack, int index);

#endif