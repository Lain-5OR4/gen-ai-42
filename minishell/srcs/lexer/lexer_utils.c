/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}