/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_syntax(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (!current)
		return (SUCCESS);
	if (current->type == TOKEN_PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'",
			STDERR_FILENO);
		return (SYNTAX_ERROR);
	}
	while (current && current->next)
	{
		if ((current->type == TOKEN_REDIRECT_IN
				|| current->type == TOKEN_REDIRECT_OUT
				|| current->type == TOKEN_REDIRECT_APPEND
				|| current->type == TOKEN_HEREDOC)
			&& current->next->type != TOKEN_WORD)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token",
				STDERR_FILENO);
			return (SYNTAX_ERROR);
		}
		current = current->next;
	}
	if (current && (current->type == TOKEN_REDIRECT_IN
			|| current->type == TOKEN_REDIRECT_OUT
			|| current->type == TOKEN_REDIRECT_APPEND
			|| current->type == TOKEN_HEREDOC
			|| current->type == TOKEN_PIPE))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			STDERR_FILENO);
		return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}

int	process_input(char *input)
{
	int	lexer_status;
	int	parser_status;

	lexer_status = lexer(input, &g_shell.tokens);
	if (lexer_status != SUCCESS)
		return (lexer_status);
	if (check_syntax(g_shell.tokens) != SUCCESS)
	{
		g_shell.exit_status = 258;
		return (SYNTAX_ERROR);
	}
	parser_status = parser(g_shell.tokens, &g_shell.commands);
	return (parser_status);
}